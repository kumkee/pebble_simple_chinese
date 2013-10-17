#include "weather.h"

#define LOC_MAG	1000000
#define UPD_FREQ 3	//weather update frequency in minute

extern DynTextLayer weather_layer, debug_layer;

int w = 0, s = 0;/////////////////
static int count = 0;/////////////

static int lat, lng;

static bool located = false;

const char* WEATHER_CONDITION[] = {
	"龍捲風",
	"熱帶風暴",
	"颶風",
	"強雷暴",
	"雷暴",
	"雨雪",
	"雨夾雪",
	"雨夾雪",
	"凍結小雨",
	"小雨",
	"凍雨",
	"陣雨",
	"陣雨",
	"陣雪",
	"光陣雪",
	"吹雪",
	"雪",
	"冰雹",
	"雨夾雪",
	"灰塵",
	"霧",
	"陰霾",
	"煙熏",
	"勁風",
	"多風",
	"冷",
	"多雲",
	"晴間多雲",
	"晴間多雲",
	"晴間多雲",
	"晴間多雲",
	"晴",
	"陽光明媚",
	"晴朗",
	"晴朗",
	"雨夾冰雹",
	"熱",
	"雷暴",
	"雷暴",
	"雷暴",
	"零星陣雨",
	"大雪",
	"零星陣雪",
	"大雪",
	"晴間多雲",
	"雷陣雨",
	"陣雪",
	"雷陣雨",
	"無法使用"
    };


void request_weather()
{
   DTL_printf(&debug_layer, "%d %d %d", ++w, s, count);/////////////

   if(!located)	http_location_request();

   // Build the HTTP request
   DictionaryIterator *body;
   //HTTPResult result = http_out_get(SERVER_URL, WEATHER_HTTP_COOKIE, &body);
   http_out_get(SERVER_URL, WEATHER_HTTP_COOKIE, &body);
   /*
   if(result != HTTP_OK) {
	return;
   }
   */
   dict_write_int32(body, WEATHER_KEY_LATITUDE, lat);
   dict_write_int32(body, WEATHER_KEY_LONGITUDE, lng);
   dict_write_cstring(body, WEATHER_KEY_UNIT_SYSTEM, UNIT_SYSTEM);
   // Send it.
   http_out_send();
   /*
   if(http_out_send() != HTTP_OK) {
	return;
   }
   */
}


void _weather_upd(DynTextLayer* dtl, PebbleTickEvent* evt)
{
   request_weather();
}


bool _weather_upd_cri(PebbleTickEvent* evt)
{
   //static int count = 0;

   if(evt->units_changed & MINUTE_UNIT)
   {
	count++;
	DTL_printf(&debug_layer, "%d %d %d", w, s, count);/////////////
   
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
   DTL_printf(&debug_layer, "%d %d %d", w, ++s, count);/////////////

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
	snprintf(weather_layer.content, TXTBUFFERSIZE, "(%s)%s%d%s ",
		   str_now, WEATHER_CONDITION[idx], temp, *UNIT_SYSTEM=='c'?"℃":"℉");
   }
   else
   {
	temp = 999;
	snprintf(weather_layer.content, TXTBUFFERSIZE, "(%s)%s∞%s ",
		   str_now, WEATHER_CONDITION[idx], *UNIT_SYSTEM=='c'?"℃":"℉");
   }

   text_layer_set_text(&weather_layer.text_layer, weather_layer.content);
}


void handle_failed(int32_t cookie, int http_status, void* htl)
{
   snprintf(weather_layer.content, TXTBUFFERSIZE, "離線 ");
   text_layer_set_text(&weather_layer.text_layer, weather_layer.content);
}


void handle_location(float latitude, float longitude, float altitude, float accuracy, void* htl)
{
   lat = latitude * LOC_MAG;
   lng = longitude * LOC_MAG;
   located = true;
}


void handle_reconnect(void* context)
{
   request_weather();
}



