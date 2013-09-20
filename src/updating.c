#include "main.h"
#include "geometry.h"

bool rm_leading_0(char* str)
{
   if(str[0] == '0')
   {
	memmove(str, &str[1], strlen(str));
	return true;
   }
   else
	return false;
}


void update_textlayer(PblTm *t, TextLayer* l, uint8_t (*upmethod)(PblTm*, char*))
{
	static char txt[NumTextLayers][TxtBufferSize];
	char buf[TxtBufferSize];
	uint8_t uid;
        
        uid = upmethod(t, buf);
	memmove(txt[uid], buf, TxtBufferSize);
	text_layer_set_text(l,txt[uid]);
}



uint8_t GenerateCDateText(PblTm *t, char* cdtext)
{

  Date today;

  today.year  = t->tm_year + 1900;
  today.month = t->tm_mon + 1;
  today.day   = t->tm_mday;
  today.hour  = t->tm_hour;

  Solar2Lunar(&today);

  CDateDisplayZh(&today,cdtext);
  
  return 0;
}


#define zhLen 3
#define MvChar(zhi) memcpy(text + place*zhLen, zhi, zhLen)
void CDateDisplayZh(Date *d, char* text)
{
  char ZhDigit[10][zhLen+1] = { "正", "一", "二", "三", "四", "五", "六", "七", "八", "九" };
  char ZhDigit2[3][zhLen+1] = { "初", "十", "廿" }; //digit in ten's place
  char ZhLeap[] = "閏";
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


uint8_t DateinZh(PblTm *t, char* txt)
{
	char mon_zh[] = "月";
	char day_zh[] = "日";
	char wday_zh[] = "一二三四五六日";
	char par[] = "()";

	char mon_n[] = "00";
	int m = sizeof(mon_n)-1;
	char day_n[] = "00";
	int d = sizeof(day_n)-1;
	const int zhl = 3;

	int place = 0;

	string_format_time(mon_n, m+1, "%m", t);
	string_format_time(day_n, d+1, "%d", t);
	if ( rm_leading_0(mon_n) ) 
		m -= 1;
	if ( rm_leading_0(day_n) )
		d -= 1;

	memcpy(txt+place, mon_n, m);
	place += m;
	memcpy(txt+place, mon_zh, zhl);
	place += zhl;
	memcpy(txt+place, day_n, d);
	place += d;
	memcpy(txt+place, day_zh, zhl);
	place += zhl;
	memcpy(txt+place, par, 1);
	place += 1;
	memcpy(txt+place, wday_zh+t->tm_wday*zhl, zhl);
	place += zhl;
	memcpy(txt+place, par+1, 1);
	place += 1;
	memcpy(txt+place, "\0", 1);

	return 1;
}


uint8_t TimeText(PblTm *t, char* timetxt) 
{
	string_format_time(timetxt, 6, "%I:%M", t);
	rm_leading_0(timetxt);
	return 2;
}


uint8_t PeriodZh(PblTm *t, char* p) 
{
    if(t->tm_hour<5)
	memcpy(p, "凌\n晨", 8);
    else if(t->tm_hour>=5 && t->tm_hour<7)
	memcpy(p, "清\n晨", 8);
    else if(t->tm_hour>=7 && t->tm_hour<11)
	memcpy(p, "上\n午", 8);
    else if(t->tm_hour>=11 && t->tm_hour<13)
	memcpy(p, "中\n午", 8);
    else if(t->tm_hour>=13 && t->tm_hour<18)
	memcpy(p, "下\n午", 8);
    else if(t->tm_hour==18)
	memcpy(p, "傍\n晚", 8);
    else
	memcpy(p, "晚\n上", 8);

    return 3;
}







