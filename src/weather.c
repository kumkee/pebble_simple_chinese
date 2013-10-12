#include "weather.h"

#define LOC_MAG	1000000
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
   if(!htl->located)	http_location_request();

   // Build the HTTP request
   DictionaryIterator *body;
   HTTPResult result = http_out_get(SERVER_URL, WEATHER_HTTP_COOKIE, &body);
   if(result != HTTP_OK) {
	return;
   }
   dict_write_int32(body, WEATHER_KEY_LATITUDE, htl->lat);
   dict_write_int32(body, WEATHER_KEY_LONGITUDE, htl->lng);
   dict_write_cstring(body, WEATHER_KEY_UNIT_SYSTEM, UNIT_SYSTEM);
   // Send it.
   if(http_out_send() != HTTP_OK) {
	return;
   }
}


void _weather_upd(DynTextLayer* dtl, PebbleTickEvent* evt, HttpTextLayer* htl)
{
   request_weather(htl);
}


bool _weather_upd_cri(PebbleTickEvent* evt)
{
   return evt->units_changed & MINUTE_UNIT && evt->tick_time->tm_min % 15 == 0;
}


void handle_success(int32_t cookie, int http_status, DictionaryIterator* received, void* htl)
{
   if(cookie != WEATHER_HTTP_COOKIE) return;

   static int16_t idx, temp;

   Tuple* idx_tuple = dict_find(received, WEATHER_CODE);
   if(idx_tuple) {
   	idx = idx_tuple->value->int16;
   	if(idx >= 0 && idx <= 48) {
   	    //weather_layer_set_idx(&weather_layer, idx);
   	} else {
   	    //weather_layer_set_error(&weather_layer, http_status);
   	}
   }

   Tuple* temperature_tuple = dict_find(received, WEATHER_KEY_TEMPERATURE);
   if(temperature_tuple) {
	temp = temperature_tuple->value->int16;
   	//weather_layer_set_highlow(&weather_layer, high, low);
   	//weather_layer_set_temperature(&weather_layer, temperature_tuple->value->int16);
   }

   snprintf(this_htl->mydtl.content, TXTBUFFERSIZE, "%s%d℃ ", WEATHER_CONDITION[idx], temp);

   return;
}


void handle_failed(int32_t cookie, int http_status, void* htl)
{
   snprintf(this_htl->mydtl.content, TXTBUFFERSIZE, "離線 ");

   return;
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
