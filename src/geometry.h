#ifndef GEO_H
#define GEO_H

#define include_ccd	true		//whether include Chinese Calendar date

#define white_on_black	true

#define TxtBufferSize	25

#define NumTextLayers	4

#define tot_length	144
#define tot_height	168
#define left_margin	7
#define top_margin	left_margin

#define line_pos_x	left_margin
#define line_pos_y	97

#define period_length	20
#define period_height	40
#define period_pos_x	left_margin
#define period_pos_y	line_pos_y + 10

#define time_pos_x	left_margin + period_length - 5
#define time_pos_y	line_pos_y 
#define time_length	tot_length - left_margin +1 - time_pos_x - period_length 
#define time_height	tot_height - top_margin - period_pos_y

#define date_length	tot_length - 2*left_margin
#define date_height	29
#define date_pos_x	left_margin
#define date_pos_y	line_pos_y - date_height

#define cdate_length	date_length
#define cdate_height	date_height/3*2
#define cdate_pos_x	left_margin
#define cdate_pos_y	date_pos_y - cdate_height

#define time_font	fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_BOLD_45))
#define period_font	fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_IPAG_16))
#define date_font	fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_IPAG_21))
#define cdate_font	fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_IPAG_17))


#if white_on_black
#define backgroundcolor	GColorBlack
#define contentcolor	GColorWhite
#else
#define backgroundcolor	GColorWhite
#define contentcolor	GColorBlack
#endif


#endif
