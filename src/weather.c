#include "pebble_os.h"
#include "DynTextLayer.h"
void _weather_upd(DynTextLayer* self, PebbleTickEvent* evt) 
{
   PblTm time_now;
   
   get_time(&time_now);

   string_format_time(self->content, TXTBUFFERSIZE, "%R", &time_now);
}

bool _weather_upd_cri(PebbleTickEvent* evt)
{
   //return 1;
   return evt->units_changed & MINUTE_UNIT
			&& evt->tick_time->tm_min % 3 == 0;
}
