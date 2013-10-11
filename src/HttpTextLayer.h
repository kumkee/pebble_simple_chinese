#ifndef HTL_H
#define HTL_H
#include "pebble_os.h"
#include "config.h"
#include "DynTextLayer.h"
#include "http.h"

typedef DynTextLayer HttpTextLayer;

void HTL_init(HttpTextLayer* htl, Layer* parent, GRect frame, GFont font, void* u_method, void* u_criteria, HTTPCallbacks* callbacks, void* ctx);

#endif
