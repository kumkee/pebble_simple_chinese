#include "main.h"
#include "config.h"
#include "lylunar.h"
#include "utils.h"




#if INCLUDE_CCD
void _cdate_upd(DynTextLayer* self, PebbleTickEvent* evt) 
{
  Date today;

  today.year  = evt->tick_time->tm_year + 1900;
  today.month = evt->tick_time->tm_mon + 1;
  today.day   = evt->tick_time->tm_mday;
  today.hour  = evt->tick_time->tm_hour;

  Solar2Lunar(&today);

  CDateDisplayZh(&today, self->content);
}

bool _cdate_upd_cri(PebbleTickEvent* evt)
{
    return evt->units_changed & HOUR_UNIT
			&& evt->tick_time->tm_hour==23;
}
#endif


void _date_upd(DynTextLayer* self, PebbleTickEvent* evt) 
{
	char mon_zh[] = "月";
	char day_zh[] = "日";
	char wday_zh[] = "日一二三四五六";
	char par[] = "()";

	char mon_n[] = "00";
	int m = sizeof(mon_n)-1;
	char day_n[] = "00";
	int d = sizeof(day_n)-1;
	const int zhl = 3;

	int place = 0;

	string_format_time(mon_n, m+1, "%m", evt->tick_time);
	string_format_time(day_n, d+1, "%d", evt->tick_time);
	if ( rm_leading_0(mon_n) ) 
		m -= 1;
	if ( rm_leading_0(day_n) )
		d -= 1;

	memcpy(self->content+place, mon_n, m);
	place += m;
	memcpy(self->content+place, mon_zh, zhl);
	place += zhl;
	memcpy(self->content+place, day_n, d);
	place += d;
	memcpy(self->content+place, day_zh, zhl);
	place += zhl;
	memcpy(self->content+place, par, 1);
	place += 1;
	memcpy(self->content+place, wday_zh+evt->tick_time->tm_wday*zhl, zhl);
	place += zhl;
	memcpy(self->content+place, par+1, 1);
	place += 1;
	memcpy(self->content+place, "\0", 1);
}

bool _date_upd_cri(PebbleTickEvent* evt)
{
    return evt->units_changed & DAY_UNIT;
}



void _time_upd(DynTextLayer* self, PebbleTickEvent* evt) 
{
    if(!clock_is_24h_style())
    {
	string_format_time(self->content, 6, "%I:%M", evt->tick_time);
	rp_leading_0(self->content);
    }
    else
	string_format_time(self->content, 6, "%R", evt->tick_time);
	
}


bool _time_upd_cri(PebbleTickEvent* evt)
{
    return evt->units_changed & MINUTE_UNIT;
}


void _period_upd(DynTextLayer* self, PebbleTickEvent* evt) 
{
    if(evt->tick_time->tm_hour<5)
	memcpy(self->content, "凌\n晨", 8);
    else if(evt->tick_time->tm_hour>=5 && evt->tick_time->tm_hour<7)
	memcpy(self->content, "清\n晨", 8);
    else if(evt->tick_time->tm_hour>=7 && evt->tick_time->tm_hour<11)
	memcpy(self->content, "上\n午", 8);
    else if(evt->tick_time->tm_hour>=11 && evt->tick_time->tm_hour<13)
	memcpy(self->content, "中\n午", 8);
    else if(evt->tick_time->tm_hour>=13 && evt->tick_time->tm_hour<18)
	memcpy(self->content, "下\n午", 8);
    else if(evt->tick_time->tm_hour==18)
	memcpy(self->content, "傍\n晚", 8);
    else
	memcpy(self->content, "晚\n上", 8);
}

bool _period_upd_cri(PebbleTickEvent* evt)
{
    return evt->units_changed & HOUR_UNIT
			&& !clock_is_24h_style();
}

#if INCLUDE_SEC
void _sec_upd(DynTextLayer *self, PebbleTickEvent* evt)
{
    string_format_time(self->content, 3, "%S", evt->tick_time);

    if(self->is_first_update && evt->tick_time->tm_hour%12>1 
				&& evt->tick_time->tm_hour%12<10)
	DTL_mv_horz(self, -11);
    else if(evt->tick_time->tm_hour%12 == 10 && evt->units_changed & HOUR_UNIT)
	DTL_mv_horz(self, 11);
    else if(evt->tick_time->tm_hour%12 == 1 && evt->units_changed & HOUR_UNIT)
	DTL_mv_horz(self, -11);
}

bool _sec_upd_cri(PebbleTickEvent* evt)
{
    return true;
}
#endif
