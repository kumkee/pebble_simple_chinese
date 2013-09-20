#include "pebble_os.h"
#ifndef MAIN_H
#define MAIN_H

void update_textlayer(PblTm* t, TextLayer* l, uint8_t (*upmethod)(PblTm*,char*));

uint8_t GenerateCDateText(PblTm *, char*);

uint8_t DateinZh(PblTm *, char*);

uint8_t TimeText(PblTm *, char*); 

uint8_t PeriodZh(PblTm *, char*); 


typedef char byte;

typedef struct {
	int year, month, day, hour, weekday;
	int leap;	/* the lunar month is a leap month */
} Date;

void Solar2Lunar(Date*);

void CDateDisplayZh(Date*, char*);

typedef enum 
{
   TIME_DRAWN = 1<<0,
   DATE_DRAWN = 1<<1,
   PERIOD_DRAWN = 1<<2,
   CDATE_DRAWN = 1<<3
} TextDrawn;

#endif
