
#ifndef LYLUNAR_H
#define LYLUNAR_H

typedef char byte;

typedef struct {
	int year, month, day, hour, weekday;
	int leap;	/* the lunar month is a leap month */
} Date;

void Solar2Lunar(Date*);

void CDateDisplayZh(Date*, char*);

#endif
