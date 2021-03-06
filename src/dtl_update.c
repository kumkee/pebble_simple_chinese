#include "config.h"
#include "lylunar.h"
#include "utils.h"
#include "DynTextLayer.h"
#include "pebble_app.h" //for resource-font


//------------------------------------------------------


#if INCLUDE_CCD
#define zhLen 3
#define MvChar(zhi) memcpy(text + place*zhLen, zhi, zhLen)
void CDateDisplayZh(Date *d, char* text)
{
  char ZhDigit[10][zhLen+1] = { "正", "一", "二", "三", "四", "五", "六", "七", "八", "九" };
  char ZhDigit2[3][zhLen+1] = { "初", "十", "廿" }; //digit in ten's place
  #if ZH_TRADITIONAL
  char ZhLeap[] =  "閏";
  #else
  char ZhLeap[] = "闰";
  #endif
  char ZhMonth[] = "月";
  char* ZhTen[3] = { ZhDigit2[0], ZhDigit[2], ZhDigit[3] }; //初, 二, 三

  int i,j;
  int place = 0;
  i = d->leap?1:0;
  j = (d->month-1)/10==0 ? 0 : 1;

  if(i)	MvChar(ZhLeap);	//閏

  place += i;
  if(j) MvChar(ZhDigit2[1]);		//十 of 十某月

  place += j;
  if(d->month==1)	MvChar(ZhDigit[0]);		//正 of 正月
  else if(d->month==10)	MvChar(ZhDigit2[1]);		//十 of 十月
  else 			MvChar(ZhDigit[d->month%10]);	//某 of 十某月 or 某月

  place++;

  MvChar(ZhMonth);	//月
  place++;

  if(d->day%10==0){
	MvChar(ZhTen[d->day/10 - 1]);	//某 of 某十日
	place++;
	MvChar(ZhDigit2[1]);		//十 of 某十日
	place++;
  }
  else{
	MvChar(ZhDigit2[d->day/10]);	//某 of 某甲日
	place++;
	MvChar(ZhDigit[d->day%10]);	//甲 of 某甲日
	place++;
  }

  text[place*zhLen] = 0;
  
}

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


//------------------------------------------------------------------


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


//------------------------------------------------------


void _time_upd(DynTextLayer* self, PebbleTickEvent* evt) 
{
    if(!clock_is_24h_style())
    {
	string_format_time(self->content, 6, "%I:%M", evt->tick_time);
	//string_format_time(self->content, 6, "%R", evt->tick_time);

	//#if INCLUDE_SEC
	rm_leading_0(self->content);
	static const int dx = INCLUDE_SEC ? 3 : 9;
	static const int dy = INCLUDE_SEC ? -5: -3;
	#define FSMALL	INCLUDE_SEC ? time_FONT_S: time_FONT_M

	if(self->is_first_update && evt->tick_time->tm_hour%12 > 0 
				&& evt->tick_time->tm_hour%12 < 10)
	{
	    text_layer_set_font(&self->text_layer, time_FONT_L);
	    DTL_mv_horz(self, dx);
	    DTL_mv_vert(self, dy);
	}
	else if(evt->units_changed & HOUR_UNIT)
	{
	    if(evt->tick_time->tm_hour%12 == 10)
	    {
		text_layer_set_font(&self->text_layer, FSMALL);
	        DTL_mv_horz(self, -dx);
	    	DTL_mv_vert(self, -dy);
	    }
	    else if(evt->tick_time->tm_hour%12 == 1)
	    {
		text_layer_set_font(&self->text_layer, time_FONT_L);
	        DTL_mv_horz(self, dx);
	    	DTL_mv_vert(self, dy);
	    }
	}
	//#else
	//rp_leading_0(self->content);
	//#endif
    }
    else
	string_format_time(self->content, 6, "%R", evt->tick_time);
	
}


bool _time_upd_cri(PebbleTickEvent* evt)
{
    return evt->units_changed & MINUTE_UNIT;
}



//------------------------------------------------------


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
    return evt->units_changed & HOUR_UNIT;
}


//------------------------------------------------------


#if INCLUDE_SEC
void _sec_upd(DynTextLayer *self, PebbleTickEvent* evt)
{
    string_format_time(self->content, 3, "%S", evt->tick_time);

}

bool _sec_upd_cri(PebbleTickEvent* evt)
{
    return true;
}
#endif
