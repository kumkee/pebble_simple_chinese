#ifndef HTL_H
#define HTL_H

#include "pebble_os.h"
#include "http.h"
#include "DynTextLayer.h"

typedef struct{
   DynTextLayer mydtl;
   char** context;
   int16_t lat;
   int16_t lng;
   bool located;
   PblTm init_time;
   bool* is_first_update;
   void (*update)();
   void (*_upd_method)();
   bool (*upd_criteria)();
} HttpTextLayer;

#endif
