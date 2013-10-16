#ifndef WEATHER_H
#define WEATHER_H
#include "HttpTextLayer.h"

void request_weather(HttpTextLayer* htl);


void _weather_upd(HttpTextLayer* htl, PebbleTickEvent* evt);


bool _weather_upd_cri(PebbleTickEvent* evt, HttpTextLayer* htl);



void handle_success(int32_t cookie, int http_status, DictionaryIterator* received, void* htl);



void handle_failed(int32_t cookie, int http_status, void* htl);


void handle_location(float latitude, float longitude, float altitude, float accuracy, void* htl);


void handle_reconnect(void* htl);

#endif
