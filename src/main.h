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

#endif
