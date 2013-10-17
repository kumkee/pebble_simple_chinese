#ifndef DTL_H
#define DTL_H

#include "pebble_os.h"
#include "config.h"

typedef struct{
    char content[TXTBUFFERSIZE];
    TextLayer text_layer;
    void (*update)();
    void (*_upd_method)();
    bool (*_upd_criteria)();
    bool is_first_update;
} DynTextLayer;

void DTL_init(DynTextLayer* dtl, Layer* parent, GRect frame, GFont font, void* u_method, void* u_criteria);

void DTL_mv_horz(DynTextLayer*, int16_t);
void DTL_mv_vert(DynTextLayer*, int16_t);

#define DTL_printf(dtl, ...) \
	   snprintf((dtl)->content, TXTBUFFERSIZE, __VA_ARGS__); \
	   text_layer_set_text(&(dtl)->text_layer, (dtl)->content)

#define DTL_set_alignment(dtl, ta)\
	   text_layer_set_text_alignment(&(dtl)->text_layer, ta)
#endif

