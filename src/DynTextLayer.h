#ifndef DTL_H
#define DTL_H

#include "pebble_os.h"
#include "config.h"

typedef struct{
    char content[TXTBUFFERSIZE];
    TextLayer text_layer;
    void (*update)();
    void (*upd_criteria)();
    bool is_first_update;
} DynTextLayer;

void DTL_mv_horz(DynTextLayer*, int16_t);

void DTL_init(DynTextLayer* dtl, Layer* parent, GRect frame, GFont font, void* u_method, void* u_criteria);
#endif

