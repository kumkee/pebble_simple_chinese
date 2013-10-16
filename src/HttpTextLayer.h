#ifndef HTL_H
#define HTL_H
#include "pebble_os.h"
#include "config.h"
#include "http.h"

typedef struct{
    char content[TXTBUFFERSIZE];
    TextLayer text_layer;
    void (*update)();
    void (*_upd_method)();
    bool (*upd_criteria)();
    bool is_first_update;
   char _buf[TXTBUFFERSIZE];
   int lat;
   int lng;
   bool located;
   PblTm init_time;
} HttpTextLayer;

void HTL_init(HttpTextLayer* htl, Layer* parent, GRect frame, GFont font, void* u_method, void* u_criteria, HTTPCallbacks* callbacks);

#endif
