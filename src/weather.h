#ifndef WEATHER_H
#define WEATHER_H

#include "DynTextLayer.h"
#include "http.h"

extern DynTextLayer weather_layer;

void _weather_upd(DynTextLayer*, PebbleTickEvent*);
bool _weather_upd_cri(PebbleTickEvent*);
void handle_success(int32_t cookie, int http_status, DictionaryIterator* received, void* context);
void handle_failed(int32_t cookie, int http_status, void* context);
void handle_location(float latitude, float longitude, float altitude, float accuracy, void* context);
void handle_reconnect(void* context);
//void request_weather();

#endif
