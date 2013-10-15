#ifndef HTL_H
#define HTL_H

#include "pebble_os.h"
#include "http.h"
#include "DynTextLayer.h"

typedef struct{
   DynTextLayer mydtl;
   int16_t lat;
   int16_t lng;
   char _buf[TXTBUFFERSIZE];
   bool located;
   PblTm init_time;
   void (*update)();
   void (*_upd_method)();
   bool (*_upd_criteria)();
} HttpTextLayer;

#endif
