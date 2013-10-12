#ifndef WEATHER_H
#define WEATEER_H
#include "pebble_os.h"
#include "HttpTextLayer.h"
#include "http.h"

void _weather_upd(DynTextLayer*, PebbleTickEvent*, HttpTextLayer*);
bool _weather_upd_cri(PebbleTickEvent*);
void handle_success(int32_t cookie, int http_status, DictionaryIterator* received, void* context);
void handle_failed(int32_t cookie, int http_status, void* context);
void handle_location(float latitude, float longitude, float altitude, float accuracy, void* context);
void handle_reconnect(void* context);

#endif
