#ifndef GEO_H
#define GEO_H

  #define no_ccd		false	//whether to include Chinese Calendar date

  #define include_sec		true	//whether to include second

  #define white_background	false
  //These are default configurations

  #define include_ccd		!no_ccd	//whether to include Chinese Calendar date

  #define white_on_black	!white_background

  #define TxtBufferSize	25

  #define tot_length	144
  #define tot_height	168
  #define left_margin	7
  #define top_margin	left_margin

  #define line_pos_x	left_margin
  #define line_pos_y	97

  #define period_length	15
  #define period_height	40
  #define period_pos_x	left_margin
  #define period_pos_y	line_pos_y + 9

  #define sec_length	13
  #define sec_height	20
  #define sec_pos_x	tot_length - left_margin - sec_length
  #define sec_pos_y	period_pos_y + 19 + (clock_is_24h_style()?4:0)

  #define time_pos_x_o	left_margin + period_length
  #define time_pos_x_r	left_margin
  #define time_pos_x	clock_is_24h_style() ? time_pos_x_r : time_pos_x_o
  #define time_pos_y	line_pos_y + (!clock_is_24h_style() && include_sec? 1:0)
//#define time_length_o	tot_length - left_margin +1 - time_pos_x - period_length 
  #define time_length	tot_length //- 2*left_margin
  #define time_height	tot_height - top_margin - period_pos_y

  #define date_length	tot_length - 2*left_margin
  #define date_height	29
  #define date_pos_x	left_margin
  #define date_pos_y	line_pos_y - date_height

  #define cdate_length	date_length
  #define cdate_height	date_height/3*2
  #define cdate_pos_x	left_margin
  #define cdate_pos_y	date_pos_y - cdate_height

  #define time_font_o_rs	fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_BOLD_45))
  #define time_font_s	fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_BOLD_40))
  #define time_font_r	fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_BOLD_49))
  #define time_font	clock_is_24h_style() && !include_sec ? time_font_r : \
				( !clock_is_24h_style() && include_sec ? time_font_s : \
									time_font_o_rs ) \

  #define period_font	fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_IPAG_16))
  #define date_font	fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_IPAG_21))
  #define cdate_font	fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_IPAG_17))
  #define sec_font	fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_CONDENSED_13))


  #define my_tick_unit	include_sec ? SECOND_UNIT : MINUTE_UNIT


  #if white_on_black
    #define backgroundcolor	GColorBlack
    #define contentcolor	GColorWhite
  #else
    #define backgroundcolor	GColorWhite
    #define contentcolor	GColorBlack
  #endif


  //#define NumTextLayers	3	//minimum number of textlayers
  #define COUNTER	3	//minimum number of textlayers

  #define time_uid	0
  #define date_uid	1
  #define peri_uid	2
  #if	include_ccd
    #define cdat_uid	peri_uid + 1
    #if	include_sec
	#define secd_uid	cdat_uid + 1
	#define NumTextLayers	COUNTER + 2
    #else
	#define NumTextLayers	COUNTER + 1
    #endif
  #else
    #if	include_sec
	#define secd_uid	peri_uid + 1
	#define NumTextLayers	COUNTER + 1
    #else
	#define NumTextLayers	COUNTER
    #endif
  #endif


#endif
