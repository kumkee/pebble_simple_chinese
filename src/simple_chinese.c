#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#include "geometry.h"
#include "main.h"


#define MY_UUID { 0x5B, 0x1A, 0xC5, 0x99, 0xBD, 0x60, 0x45, 0xBF, 0xA3, 0x67, 0x72, 0x53, 0xE5, 0x71, 0x55, 0xC6 }
PBL_APP_INFO(MY_UUID,
             "Simple Chinese", "kumkee",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_WATCH_FACE);

Window window;

Layer line_layer;

TextLayer text_time_layer;
TextLayer text_period_layer;
TextLayer text_date_layer;
TextLayer text_cdate_layer;


void line_layer_update_callback(Layer *me, GContext* ctx) {

  graphics_context_set_stroke_color(ctx, contentcolor);

  graphics_draw_line(ctx, GPoint(line_pos_x, line_pos_y), GPoint(tot_length-line_pos_x, line_pos_y));
  graphics_draw_line(ctx, GPoint(line_pos_x, line_pos_y+1), GPoint(tot_length-line_pos_x, line_pos_y+1));

}


#define LayerInit(Layer, X, Y, L, H, Font) \
	text_layer_init(&Layer, window.layer.frame); \
	text_layer_set_text_color(&Layer, contentcolor); \
	text_layer_set_background_color(&Layer, GColorClear); \
	layer_set_frame(&Layer.layer, GRect(X, Y, L, H)); \
	text_layer_set_font(&Layer, Font); \
	layer_add_child(&window.layer, &Layer.layer);

#define LayerInitText(name) LayerInit(text_##name##_layer, name##_pos_x, name##_pos_y, name##_length, name##_height, name##_font)

void handle_init(AppContextRef ctx) {

  window_init(&window, "Simple Chinese");
  window_stack_push(&window, true /* Animated */);
  window_set_background_color(&window, backgroundcolor);

  resource_init_current_app(&APP_RESOURCES);

  layer_init(&line_layer, window.layer.frame);
  line_layer.update_proc = &line_layer_update_callback;
  layer_add_child(&window.layer, &line_layer);

  LayerInitText(period);

  LayerInitText(time);

  LayerInitText(date);

  LayerInitText(cdate);

}


void handle_minute_tick(AppContextRef ctx, PebbleTickEvent *evt)
{
  static TextDrawn d = 0;

  if( (evt->units_changed & DAY_UNIT) || !(d & DATE_DRAWN) )
  {
	update_textlayer(evt->tick_time,&text_date_layer,DateinZh);
	d |= DATE_DRAWN;
  }

  update_textlayer(evt->tick_time,&text_time_layer,TimeText);
  d |= TIME_DRAWN;

  if( (evt->units_changed & HOUR_UNIT) || !(d & PERIOD_DRAWN) )
  {
	update_textlayer(evt->tick_time,&text_period_layer,PeriodZh);
	d |= PERIOD_DRAWN;
  }

  if(!include_ccd)
	return;

  if( (evt->units_changed & HOUR_UNIT && evt->tick_time->tm_hour==23) || !(d & CDATE_DRAWN) )
  {
	update_textlayer(evt->tick_time,&text_cdate_layer,GenerateCDateText);
	d |= CDATE_DRAWN;
  }
}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .tick_info = {
      .tick_handler = &handle_minute_tick,
      .tick_units = MINUTE_UNIT
    }
  };
  app_event_loop(params, &handlers);
}
