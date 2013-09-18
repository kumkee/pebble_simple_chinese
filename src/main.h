#include "pebble_os.h"
#ifndef MAIN_H
#define MAIN_H

void update_textlayer(PblTm* t, TextLayer* l, void (*upmethod)(PblTm*,char*));

void GenerateCDateText(PblTm *t, char* cdtext);

void DateinZh(PblTm *t, char* cdtext);


typedef char byte;

typedef struct {
	int year, month, day, hour, weekday;
	int leap;	/* the lunar month is a leap month */
} Date;

void Solar2Lunar(Date*);

void CDateDisplayZh(Date*, char*);

#endif
