#include "weather.h"
//#include "utils.h"

#define LOC_MAG	1000000
#define UPD_FREQ 2	//weather update frequency in minute
#define this_htl ((HttpTextLayer*)htl)

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

void request_weather(HttpTextLayer* htl)
{
   // Build the HTTP request
   DictionaryIterator *body;
   HTTPResult result = http_out_get(SERVER_URL, WEATHER_HTTP_COOKIE, &body);
   if(result != HTTP_OK) {
   	snprintf(htl->mydtl.content, TXTBUFFERSIZE, "0:%X ", result);
   	text_layer_set_text(&htl->mydtl.text_layer, htl->mydtl.content);
	return;
   }
   dict_write_int32(body, WEATHER_KEY_LATITUDE, htl->lat);
   dict_write_int32(body, WEATHER_KEY_LONGITUDE, htl->lng);
   dict_write_cstring(body, WEATHER_KEY_UNIT_SYSTEM, UNIT_SYSTEM);
   // Send it.
   if(http_out_send() != HTTP_OK) {
   	snprintf(htl->mydtl.content, TXTBUFFERSIZE, "1:%X ", result);
   	text_layer_set_text(&htl->mydtl.text_layer, htl->mydtl.content);
	return;
   }
/*
   static uint16_t c = 0;
   char tmp[] = "00:00";
   string_format_time(tmp, 6, "%R", &htl->init_time);
   string_format_time(htl->_buf, TXTBUFFERSIZE, "%R", evt->tick_time);
   snprintf(htl->mydtl.content, TXTBUFFERSIZE, "%s %u %s ", tmp,  c++, htl->_buf);
   text_layer_set_text(&htl->mydtl.text_layer, htl->mydtl.content);
*/
}


void _weather_upd(HttpTextLayer* htl, PebbleTickEvent* evt)
{
   if(!htl->located)	http_location_request();

   request_weather(htl);
}


bool _weather_upd_cri(PebbleTickEvent* evt, HttpTextLayer* htl)
{
   return evt->units_changed & MINUTE_UNIT && (evt->tick_time->tm_min - htl->init_time.tm_min)% UPD_FREQ == 0;
   //return evt->units_changed & MINUTE_UNIT;
}


void handle_success(int32_t cookie, int http_status, DictionaryIterator* received, void* htl)
{
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
	snprintf(this_htl->_buf, TXTBUFFERSIZE, "%s%d%s",
		   WEATHER_CONDITION[idx], temp, *UNIT_SYSTEM=='c'?"℃":"℉");
   }
   else
   {
	temp = 999;
	snprintf(this_htl->_buf, TXTBUFFERSIZE, "%s∞%s",
		   WEATHER_CONDITION[idx], *UNIT_SYSTEM=='c'?"℃":"℉");
   }
 
   snprintf(this_htl->mydtl.content, TXTBUFFERSIZE, "(%s)%s ",
		str_now, this_htl->_buf);
   text_layer_set_text(&this_htl->mydtl.text_layer, this_htl->mydtl.content);
}


void handle_failed(int32_t cookie, int http_status, void* htl)
{
   if(!this_htl->mydtl.is_first_update)
	snprintf(this_htl->mydtl.content, TXTBUFFERSIZE, "離線 ");
   else
   {
   	snprintf(this_htl->mydtl.content, TXTBUFFERSIZE, "(%s)%s ",
		"離線", this_htl->_buf);
   }
   text_layer_set_text(&this_htl->mydtl.text_layer, this_htl->mydtl.content);
}

void handle_location(float latitude, float longitude, float altitude, float accuracy, void* htl)
{
   this_htl->lat = latitude * LOC_MAG;
   this_htl->lng = longitude * LOC_MAG;
   this_htl->located = true;
}


void handle_reconnect(void* htl)
{
   request_weather(this_htl);
}
