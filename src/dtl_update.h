#include "pebble_os.h"
#ifndef DTL_U_H
#define DTL_U_H
void _cdate_upd(DynTextLayer*, PebbleTickEvent*, void*); 
bool _cdate_upd_cri(PebbleTickEvent*);

void _date_upd(DynTextLayer*, PebbleTickEvent*, void*); 
bool _date_upd_cri(PebbleTickEvent*);

void _time_upd(DynTextLayer*, PebbleTickEvent*, void*); 
bool _time_upd_cri(PebbleTickEvent*);

void _period_upd(DynTextLayer*, PebbleTickEvent*, void*); 
bool _period_upd_cri(PebbleTickEvent*);

void _sec_upd(DynTextLayer*, PebbleTickEvent*, void*);
bool _sec_upd_cri();
#endif
