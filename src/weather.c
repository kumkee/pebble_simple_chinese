#include "weather.h"

#define LOC_MAG	1000000
#define this_htl ((HttpTextLayer*)htl)


void _weather_upd(HttpTextLayer* self)
{
   if(!self->located)	http_location_request();

   // Build the HTTP request
   DictionaryIterator *body;
   HTTPResult result = http_out_get(SERVER_URL, WEATHER_HTTP_COOKIE, &body);
   if(result != HTTP_OK) {
	return;
   }
   dict_write_int32(body, WEATHER_KEY_LATITUDE, self->lat);
   dict_write_int32(body, WEATHER_KEY_LONGITUDE, self->lng);
   dict_write_cstring(body, WEATHER_KEY_UNIT_SYSTEM, UNIT_SYSTEM);
   // Send it.
   if(http_out_send() != HTTP_OK) {
	return;
   }

}


bool _weather_upd_cri()
{
   return true;
}


void handle_success(int32_t cookie, int http_status, DictionaryIterator* received, void* htl)
{
   if(cookie != WEATHER_HTTP_COOKIE) return;

   static int16_t icon, temp;

   Tuple* icon_tuple = dict_find(received, WEATHER_CODE);
   if(icon_tuple) {
   	icon = icon_tuple->value->int16;
   	if(icon >= 0 && icon <= 48) {
   	    //weather_layer_set_icon(&weather_layer, icon);
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

   char s[10];

   snprintf(s, 10, "%d %d", temp, icon);

   text_layer_set_text(&this_htl->mydtl.text_layer, s);

   return;
}


void handle_failed(int32_t cookie, int http_status, void* context)
{
   return;
}

void handle_location(float latitude, float longitude, float altitude, float accuracy, void* htl)
{
   this_htl->lat = latitude * LOC_MAG;
   this_htl->lng = longitude * LOC_MAG;
   this_htl->located = true;
}


void handle_reconnect(void* context)
{
}
