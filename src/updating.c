#include "main.h"

void GenerateCDateText(PblTm *t, char* cdtext)
{

  Date today;

  today.year  = t->tm_year + 1900;
  today.month = t->tm_mon + 1;
  today.day   = t->tm_mday;
  today.hour  = t->tm_hour;

  Solar2Lunar(&today);

  CDateDisplayZh(&today,cdtext);
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


void update_textlayer(PblTm *t, TextLayer* l, void (*upmethod)(PblTm*, char*))
{
	char *txt = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
        
        upmethod(t, txt);
	text_layer_set_text(l,txt);
}


void DateinZh(PblTm *t, char* txt)
{
	char mon_zh[] = "月";
	char day_zh[] = "日";
	char wday_zh[] = "一二三四五六日";
	char par[] = "()";

	char mon_n[] = "00";
	int m = sizeof(mon_n);
	char day_n[] = "00";
	char *nu = "\0";
	int d = sizeof(day_n)-1;
	const int zhl = 3;

	int place = 0;

	string_format_time(mon_n, m, "%m", t);
	string_format_time(day_n, d, "%d", t);
	if (mon_n[0] == '0') {
		m -= 1;
		memcpy(mon_n, &mon_n[1], m);
	}
	if (day_n[0] == '0') {
		d -= 1;
		memcpy(day_n, &day_n[1], d);
	}

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
	memcpy(txt+place, nu, 1);

}






