#ifndef GEO_H
#define GEO_H

  #define NO_CCD		false	//whether to include Chinese Calendar date

  #define INCLUDE_SEC		false	//whether to include second

  #define WHITE_BACKGROUND	false

//Celsius / Fahrenheit
  #define UNIT_SYSTEM "c" // c or f

  #define SERVER_URL "http://freeshell.de/~kumkee/weather.php" 
  //These are default configurations

//-------------------------------------------------------------------------
  #define INCLUDE_CCD		!NO_CCD	//whether to include Chinese Calendar date

  #define WHITE_ON_BLACK	!WHITE_BACKGROUND

  #define TXTBUFFERSIZE	25

  #define TOT_LENGTH	144
  #define TOT_HEIGHT	168
  #define LEFT_MARGIN	7
  #define TOP_MARGIN	LEFT_MARGIN

  #define weather_POS_X	LEFT_MARGIN
  #define weather_POS_Y	TOP_MARGIN
  #define weather_LENGTH	TOT_LENGTH - 2*LEFT_MARGIN
  #define weather_HEIGHT	20
  #define weather_GRECT	GRect(weather_POS_X, weather_POS_Y, weather_LENGTH, weather_HEIGHT)
  
  #define LINE_POS_X	LEFT_MARGIN
  #define LINE_POS_Y	97

  #define period_LENGTH	15
  #define period_HEIGHT	40
  #define period_POS_X	LEFT_MARGIN
  #define period_POS_Y	LINE_POS_Y + 9
  #define period_GRECT	GRect(period_POS_X, period_POS_Y, period_LENGTH, period_HEIGHT)

  #define sec_LENGTH	13
  #define sec_HEIGHT	20
  #define sec_POS_X	TOT_LENGTH - LEFT_MARGIN - sec_LENGTH
  //#define sec_POS_Y	period_POS_Y + 19 + (clock_is_24h_style()?4:0)
  #define sec_POS_Y	period_POS_Y + 23// + (clock_is_24h_style()?4:0)
  #define sec_GRECT	GRect(sec_POS_X, sec_POS_Y, sec_LENGTH, sec_HEIGHT)

  #define time_POS_X_O	LEFT_MARGIN + period_LENGTH
  #define time_POS_X_R	LEFT_MARGIN
  #define time_POS_X	clock_is_24h_style() ? time_POS_X_R : time_POS_X_O
  #define time_POS_Y	LINE_POS_Y + (!clock_is_24h_style() && INCLUDE_SEC? 2:0)
//#define time_length_o	tot_length - left_margin +1 - time_pos_x - period_length 
  #define time_LENGTH	TOT_LENGTH //- 2*LEFT_MARGIN
  #define time_HEIGHT	TOT_HEIGHT - TOP_MARGIN - period_POS_Y
  #define time_GRECT	GRect(time_POS_X, time_POS_Y, time_LENGTH, time_HEIGHT)

  #define date_LENGTH	TOT_LENGTH - 2*LEFT_MARGIN
  #define date_HEIGHT	29
  #define date_POS_X	LEFT_MARGIN
  #define date_POS_Y	LINE_POS_Y - date_HEIGHT
  #define date_GRECT	GRect(date_POS_X, date_POS_Y, date_LENGTH, date_HEIGHT)

  #define cdate_LENGTH	date_LENGTH
  #define cdate_HEIGHT	date_HEIGHT/3*2
  #define cdate_POS_X	LEFT_MARGIN
  #define cdate_POS_Y	date_POS_Y - cdate_HEIGHT
  #define cdate_GRECT	GRect(cdate_POS_X, cdate_POS_Y, cdate_LENGTH, cdate_HEIGHT)

  #define time_FONT_M	fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_BOLD_45))
  #define time_FONT_S	fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_BOLD_40))
  #define time_FONT_L	fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_BOLD_49))
  #define time_FONT	clock_is_24h_style() && !INCLUDE_SEC ? time_FONT_L : \
				( !clock_is_24h_style() && INCLUDE_SEC ? time_FONT_S : \
									time_FONT_M ) \

  #define period_FONT	fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_IPAG_16))
  #define date_FONT	fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_IPAG_21))
  #define cdate_FONT	fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_IPAG_17))
  #define sec_FONT	fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_CONDENSED_13))
  #define weather_FONT	period_FONT


  #define MY_TICK_UNIT	INCLUDE_SEC ? SECOND_UNIT : MINUTE_UNIT


  #if WHITE_ON_BLACK
    #define BACKGROUNDCOLOR	GColorBlack
    #define CONTENTCOLOR	GColorWhite
  #else
    #define BACKGROUNDCOLOR	GColorWhite
    #define CONTENTCOLOR	GColorBlack
  #endif

// POST variables
  #define WEATHER_KEY_LATITUDE 1
  #define WEATHER_KEY_LONGITUDE 2
  #define WEATHER_KEY_UNIT_SYSTEM 3
	
// Received variables
  #define WEATHER_KEY_TEMPERATURE 1
  #define WEATHER_CODE 4

//mmm cookie
  #define WEATHER_HTTP_COOKIE 1949999771

#endif
