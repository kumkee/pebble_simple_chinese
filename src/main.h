#include "pebble_os.h"
#include "DynTextLayer.h"
#ifndef MAIN_H
#define MAIN_H

void _cdate_upd(DynTextLayer*, PebbleTickEvent*); 
bool _cdate_upd_cri(PebbleTickEvent*);

void _date_upd(DynTextLayer*, PebbleTickEvent*); 
bool _date_upd_cri(PebbleTickEvent*);

void _time_upd(DynTextLayer*, PebbleTickEvent*); 
bool _time_upd_cri(PebbleTickEvent*);

void _period_upd(DynTextLayer*, PebbleTickEvent*); 
bool _period_upd_cri(PebbleTickEvent*);

void _sec_upd(DynTextLayer*, PebbleTickEvent*);
bool _sec_upd_cri();


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
