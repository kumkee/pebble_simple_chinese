#ifndef WEATHER_ZH_H
#define WEATHER_ZH_H

const char* MSG_OFFLINE = ZH_TRADITIONAL ? "離線" : "离线";

const char MSG_UPDATE[] = "更新";

const char MSG_WAIT[] = "稍候…";

const char* MSG_SEND_TIMEOUT = "連接手機超時";

const char* MSG_NOT_CONNECTED = "藍牙離線";

const char* MSG_BRIDGE_NOT_RUNNING = "手機端未運行";

const char* MSG_INVALID_ARGS = "錯誤參數";

const char* MSG_BUSY = "連接中";

const char* MSG_BUFFER_OVERFLOW = "緩存溢出";

const char* MSG_NOT_ENOUGH_STORAGE = "空間不足";

const char* MSG_INTERNAL_INCONSISTENCY = "內部錯誤";

const char* MSG_INVALID_BRIDGE_RESPONSE = "手機端錯誤";

const char* MSG_OTHER = "離線";

const char* MSG_OK = "";

const char* error_msg(int r)
{
   switch(r)
   {
    case HTTP_OK:
	return MSG_OK;
    case HTTP_SEND_TIMEOUT:
	return MSG_SEND_TIMEOUT;
    case HTTP_NOT_CONNECTED:
	return MSG_NOT_CONNECTED;
    case HTTP_BRIDGE_NOT_RUNNING:
	return MSG_BRIDGE_NOT_RUNNING;
    case HTTP_INVALID_ARGS:
	return MSG_INVALID_ARGS;
    case HTTP_BUSY:
	return MSG_BUSY;
    case HTTP_BUFFER_OVERFLOW:
	return MSG_BUFFER_OVERFLOW;
    case HTTP_NOT_ENOUGH_STORAGE:
	return MSG_NOT_ENOUGH_STORAGE;
    case HTTP_INTERNAL_INCONSISTENCY:
	return MSG_INTERNAL_INCONSISTENCY;
    case HTTP_INVALID_BRIDGE_RESPONSE:
	return MSG_INVALID_BRIDGE_RESPONSE;
    default:
	return MSG_OTHER;
   }
}



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
