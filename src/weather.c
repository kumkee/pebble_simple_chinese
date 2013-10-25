#include "weather.h"
#include "weather_zh.h"

#define LOC_MAG	1000000
#define UPD_FREQ 15	//weather update frequency in minute

extern DynTextLayer weather_layer, debug_layer, info_layer;
#if DEBUG
extern DynTextLayer debug_layer;
int w = 0, f = 0;/////////////////
#endif

static int count_min = -1;	//Number of whole minute passed
static uint8_t n_success = 0;	//Number of successful weather_request() calls
static uint8_t n_retrial = 0;	//Number of connection retrials
static const uint8_t MAX_N_RETRY = 5;

static int lat, lng;

static bool located = false;


void request_weather()
{
   if(!located)	http_location_request();

   #if DEBUG
   DTL_printf(&debug_layer, "%d %d %d %d", ++w, n_success, f, count_min);/////////////
   #endif

   // Build the HTTP request
   DictionaryIterator *body;
   HTTPResult result = http_out_get(SERVER_URL, WEATHER_HTTP_COOKIE, &body);
   //http_out_get(SERVER_URL, WEATHER_HTTP_COOKIE, &body);
   if(result != HTTP_OK) {
	#if DEBUG
	DTL_printf(&debug_layer, "0:%d", result);/////////////
	#endif
	DTL_printf(&info_layer, "%s  ", error_msg(result));
	return;
   }

   dict_write_int32(body, WEATHER_KEY_LATITUDE, lat);
   dict_write_int32(body, WEATHER_KEY_LONGITUDE, lng);
   dict_write_cstring(body, WEATHER_KEY_UNIT_SYSTEM, UNIT_SYSTEM);
   // Send it.
   result = http_out_send();
   if(result != HTTP_OK) {
	#if DEBUG
	DTL_printf(&debug_layer, "0:%d", result);/////////////
	#endif
	DTL_printf(&info_layer, "%s  ", error_msg(result));
	return;
   }
}


void _weather_upd(DynTextLayer* self, PebbleTickEvent* evt)
{
   if(self->is_first_update) DTL_printf(self, "%s ", MSG_WAIT);

   request_weather();
}


bool _weather_upd_cri(PebbleTickEvent* evt)
{
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
	count_min++;
        #if DEBUG
	DTL_printf(&debug_layer, "%d %d %d %d", w, n_success, f, count_min);/////////////
	#endif
   
	if(count_min % UPD_FREQ == 0)
	{
	   count_min = 0;
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
   n_success++;
   DTL_printf(&debug_layer, "%d %d %d %d", w, n_success, f, count_min);/////////////
   #else
   if(n_success<5) n_success++;
   #endif

   n_retrial = 0;

   if(cookie != WEATHER_HTTP_COOKIE) return;

   static int16_t idx, temp, upd_hr, upd_min;
   //uint16_t upd_time_len;
   //PblTm time_now;

   //get_time(&time_now);
   //string_format_time(str_now, sizeof(str_now), "%R", &time_now);

   Tuple* idx_tuple = dict_find(received, WEATHER_CODE);
   if(idx_tuple) {
   	idx = idx_tuple->value->int16;
   	if(idx < 0 && idx > 47) 
	   idx = 48;
   }

   Tuple* temperature_tuple = dict_find(received, WEATHER_KEY_TEMPERATURE);
   if(temperature_tuple || temperature_tuple->value->int16!=999)
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

   Tuple* updhr_tuple = dict_find(received, UPDATE_HOUR);
   if(updhr_tuple)
	upd_hr = updhr_tuple->value->int16;

   Tuple* updmin_tuple = dict_find(received, UPDATE_MIN);
   if(updmin_tuple)
	upd_min = updmin_tuple->value->int16;

   DTL_printf(&info_layer, "%d:%02d%s  ", upd_hr, upd_min, MSG_UPDATE);


}


void handle_failed(int32_t cookie, int http_status, void* evt)
{
   #if DEBUG
   DTL_printf(&debug_layer, "%d %d %d %d", w, n_success, ++f, count_min);/////////////
   #endif

   const char* errmsg = error_msg(http_status - 1000);
   
   if(n_success<2)
   {
	DTL_printf(&weather_layer, "%s ", errmsg);
   }
   else	
   {
	char str_now[6];
	PblTm time_now;
	get_time(&time_now);
	string_format_time(str_now, sizeof(str_now), "%R", &time_now);
	DTL_printf(&info_layer, "%s%s  ", str_now, errmsg);
   }

   if(n_retrial < MAX_N_RETRY)
   {
	count_min = UPD_FREQ - 1;
	n_retrial++;
   }
   else
   {
	n_retrial = 0;
   }
}


void handle_location(float latitude, float longitude, float altitude, float accuracy, void* htl)
{
   n_success++;

   lat = latitude * LOC_MAG;
   lng = longitude * LOC_MAG;
   located = true;
   //request_weather();
}


void handle_reconnect(void* context)
{
   request_weather();
}



