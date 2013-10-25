#ifndef WEATHER_ZH_H
#define WEATHER_ZH_H

const char* MSG_OFFLINE = ZH_TRADITIONAL ? "離線" : "离线";

const char MSG_UPDATE[] = "更新";

const char MSG_WAIT[] = "稍候…";

const char* WEATHER_CONDITION_T[] = {
	"龍捲風",	//0	tornado
	"熱帶風暴",	//1	tropical storm
	"颶風",		//2	hurricane
	"強雷暴",	//3	severe thunderstorms
	"雷暴",		//4	thunderstorms
	"雨雪",		//5	mixed rain and snow
	"雨夾雪",	//6	mixed rain and sleet
	"雨夾雪",	//7	mixed snow and sleet
	"凍結小雨",	//8	freezing drizzle
	"小雨",		//9	drizzle
	"凍雨",		//10	freezing rain
	"陣雨",		//11	showers
	"陣雨",		//12	showers
	"陣雪",		//13	snow flurries
	"光陣雪",	//14	light snow showers
	"吹雪",		//15	blowing snow
	"雪",		//16	snow
	"冰雹",		//17	hail
	"雨夾雪",	//18	sleet
	"灰塵",		//19	dust
	"霧",		//20	foggy
	"陰霾",		//21	haze
	"煙熏",		//22	smoky
	"勁風",		//23	blustery
	"多風",		//24	windy
	"冷",		//25	cold
	"多雲",		//26	cloudy
	"多雲",		//27	mostly cloudy (night)
	"多雲",		//28	mostly cloudy (day)
	"晴間多雲",	//29	partly cloudy (night)
	"晴間多雲",	//30	partly cloudy (day)
	"晴",		//31	clear (night)
	"陽光明媚",	//32	sunny
	"晴朗",		//33	fair (night)
	"晴朗",		//34	fair (day)
	"雨夾冰雹",	//35	mixed rain and hail
	"熱",		//36	hot
	"雷暴",		//37	isolated thunderstorms
	"雷暴",		//38	scattered thunderstorms
	"雷暴",  	//39	scattered thunderstorms
	"零星陣雨",	//40	scattered showers
	"大雪",		//41	heavy snow
	"零星陣雪",	//42	scattered snow showers
	"大雪",		//43	heavy snow
	"晴間多雲",	//44	partly cloudy
	"雷陣雨",	//45	thundershowers
	"陣雪",		//46	snow showers
	"雷陣雨",	//47	isolated thundershowers
	"無法使用"	//3200	not available
    };


const char* WEATHER_CONDITION_S[] = {
	"龙卷风",	//0	tornado
	"热带风暴",	//1	tropical storm
	"飓风",		//2	hurricane
	"强雷暴",	//3	severe thunderstorms
	"雷暴",		//4	thunderstorms
	"雨雪",		//5	mixed rain and snow
	"雨夹雪",	//6	mixed rain and sleet
	"雨夹雪",	//7	mixed snow and sleet
	"冻结小雨",	//8	freezing drizzle
	"小雨",		//9	drizzle
	"冻雨",		//10	freezing rain
	"阵雨",		//11	showers
	"阵雨",		//12	showers
	"阵雪",		//13	snow flurries
	"光阵雪",	//14	light snow showers
	"吹雪",		//15	blowing snow
	"雪",		//16	snow
	"冰雹",		//17	hail
	"雨夹雪",	//18	sleet
	"灰尘",		//19	dust
	"雾",		//20	foggy
	"阴霾",		//21	haze
	"烟熏",		//22	smoky
	"劲风",		//23	blustery
	"多风",		//24	windy
	"冷",		//25	cold
	"多云",		//26	cloudy
	"多云",		//27	mostly cloudy (night)
	"多云",		//28	mostly cloudy (day)
	"晴间多云",	//29	partly cloudy (night)
	"晴间多云",	//30	partly cloudy (day)
	"晴",		//31	clear (night)
	"阳光明媚",	//32	sunny
	"晴朗",		//33	fair (night)
	"晴朗",		//34	fair (day)
	"雨夹冰雹",	//35	mixed rain and hail
	"热",		//36	hot
	"雷暴",		//37	isolated thunderstorms
	"雷暴",		//38	scattered thunderstorms
	"雷暴",  	//39	scattered thunderstorms
	"零星阵雨",	//40	scattered showers
	"大雪",		//41	heavy snow
	"零星阵雪",	//42	scattered snow showers
	"大雪",		//43	heavy snow
	"晴间多云",	//44	partly cloudy
	"雷阵雨",	//45	thundershowers
	"阵雪",		//46	snow showers
	"雷阵雨",	//47	isolated thundershowers
	"无法使用"	//3200	not available
    };

#if ZH_TRADITIONAL
  #define WEATHER_CONDITION	WEATHER_CONDITION_T
#else
  #define WEATHER_CONDITION	WEATHER_CONDITION_S
#endif

#endif
