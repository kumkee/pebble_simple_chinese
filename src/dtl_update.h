#ifndef DTL_UPD_H
#define DTL_UPD_H

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

#endif
