#include "weather.h"

#define LOC_MAG	1000000
#define UPD_FREQ 30	//weather update frequency in minute

extern DynTextLayer weather_layer, debug_layer, info_layer;
#if DEBUG
extern DynTextLayer debug_layer;
int w = 0, s = 0;/////////////////
#endif

static int count = 0;/////////////

static int lat, lng;

static bool located = false;

const char* WEATHER_CONDITION[] = {
	"龍捲風",	//0	tornado
	"熱帶風暴",	//1	tropical storm
	"颶風",		//2	hurricane
	"強雷暴",	//3	severe thunderstorms
	"雷暴",		//4	thunderstorms
	"雨雪",		//5	mixed rain and snow
	"雨夾雪",	//6	mixed rain and sleet
	"雨夾雪",	//7	mixed snow and sleet
	"凍結小雨",	//8	freezing drizzle
	"小雨",		//9	drizzle
	"凍雨",		//10	freezing rain
	"陣雨",		//11	showers
	"陣雨",		//12	showers
	"陣雪",		//13	snow flurries
	"光陣雪",	//14	light snow showers
	"吹雪",		//15	blowing snow
	"雪",		//16	snow
	"冰雹",		//17	hail
	"雨夾雪",	//18	sleet
	"灰塵",		//19	dust
	"霧",		//20	foggy
	"陰霾",		//21	haze
	"煙熏",		//22	smoky
	"勁風",		//23	blustery
	"多風",		//24	windy
	"冷",		//25	cold
	"多雲",		//26	cloudy
	"多雲",		//27	mostly cloudy (night)
	"多雲",		//28	mostly cloudy (day)
	"晴間多雲",	//29	partly cloudy (night)
	"晴間多雲",	//30	partly cloudy (day)
	"晴",		//31	clear (night)
	"陽光明媚",	//32	sunny
	"晴朗",		//33	fair (night)
	"晴朗",		//34	fair (day)
	"雨夾冰雹",	//35	mixed rain and hail
	"熱",		//36	hot
	"雷暴",		//37	isolated thunderstorms
	"雷暴",		//38	scattered thunderstorms
	"雷暴",  	//39	scattered thunderstorms
	"零星陣雨",	//40	scattered showers
	"大雪",		//41	heavy snow
	"零星陣雪",	//42	scattered snow showers
	"大雪",		//43	heavy snow
	"晴間多雲",	//44	partly cloudy
	"雷陣雨",	//45	thundershowers
	"陣雪",		//46	snow showers
	"雷陣雨",	//47	isolated thundershowers
	"無法使用"	//3200	not available
    };


void request_weather()
{
   #if DEBUG
   DTL_printf(&debug_layer, "%d %d %d", ++w, s, count);/////////////
   #endif

   if(!located)	http_location_request();

   // Build the HTTP request
   DictionaryIterator *body;
   HTTPResult result = http_out_get(SERVER_URL, WEATHER_HTTP_COOKIE, &body);
   //http_out_get(SERVER_URL, WEATHER_HTTP_COOKIE, &body);
   if(result != HTTP_OK) {
	return;
   }

   dict_write_int32(body, WEATHER_KEY_LATITUDE, lat);
   dict_write_int32(body, WEATHER_KEY_LONGITUDE, lng);
   dict_write_cstring(body, WEATHER_KEY_UNIT_SYSTEM, UNIT_SYSTEM);
   // Send it.
   if(http_out_send() != HTTP_OK) {
	return;
   }
}


void _weather_upd(DynTextLayer* dtl, PebbleTickEvent* evt)
{
   //if(dtl->is_first_update) psleep(1000);
   request_weather();
}


bool _weather_upd_cri(PebbleTickEvent* evt)
{
   //static int count = 0;
   #if INCLUDE_SEC
   static int init_sec;
   static bool firstcall = true;
   if(firstcall){
	init_sec = evt->tick_time->tm_sec;
	firstcall = false;
   }
   #endif

   #if INCLUDE_SEC
   if(evt->tick_time->tm_sec == init_sec)
   #else
   if(evt->units_changed & MINUTE_UNIT)
   #endif
   {
	count++;
        #if DEBUG
	DTL_printf(&debug_layer, "%d %d %d", w, s, count);/////////////
	#endif
   
	if(count % UPD_FREQ == 0)
	{
	   count = 0;
	   return true;
	}
	else
	   return false;
   }
   else
	return false;

}


void handle_success(int32_t cookie, int http_status, DictionaryIterator* received, void* context)
{
   #if DEBUG
   DTL_printf(&debug_layer, "%d %d %d", w, ++s, count);/////////////
   #endif

   if(cookie != WEATHER_HTTP_COOKIE) return;

   static int16_t idx, temp;
   char str_now[6];
   PblTm time_now;

   get_time(&time_now);
   string_format_time(str_now, sizeof(str_now), "%R", &time_now);

   Tuple* idx_tuple = dict_find(received, WEATHER_CODE);
   if(idx_tuple) {
   	idx = idx_tuple->value->int16;
   	if(idx < 0 && idx > 47) 
	   idx = 48;
   }

   Tuple* temperature_tuple = dict_find(received, WEATHER_KEY_TEMPERATURE);
   if(temperature_tuple)
   {
	temp = temperature_tuple->value->int16;
	DTL_printf(&weather_layer, "%s%d%s ",
		    WEATHER_CONDITION[idx], temp, *UNIT_SYSTEM=='c'?"℃":"℉");
   }
   else
   {
	temp = 999;
	DTL_printf(&weather_layer, "%s∞%s ",
		   WEATHER_CONDITION[idx], *UNIT_SYSTEM=='c'?"℃":"℉");
   }
   DTL_printf(&info_layer, "%s更新 ", str_now);
}


void handle_failed(int32_t cookie, int http_status, void* htl)
{

   DTL_printf(&info_layer, "離線 ");
   //snprintf(weather_layer.content, TXTBUFFERSIZE, "離線 ");
   //text_layer_set_text(&weather_layer.text_layer, weather_layer.content);
}


void handle_location(float latitude, float longitude, float altitude, float accuracy, void* htl)
{
   lat = latitude * LOC_MAG;
   lng = longitude * LOC_MAG;
   located = true;
   request_weather();
}


void handle_reconnect(void* context)
{
   request_weather();
}



