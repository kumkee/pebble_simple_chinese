#ifndef WEATHER_H
#define wEATEER_H
void _weather_upd();
bool _weather_upd_cri();
void handle_success(int32_t cookie, int http_status, DictionaryIterator* received, void* context);
void handle_failed(int32_t cookie, int http_status, void* context);
#endif
