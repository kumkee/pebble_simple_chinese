#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#include "config.h"
#include "main.h"


#define MY_UUID { 0x5B, 0x1A, 0xC5, 0x99, 0xBD, 0x60, 0x45, 0xBF, 0xA3, 0x67, 0x72, 0x53, 0xE5, 0x71, 0x55, 0xC6 }
PBL_APP_INFO(MY_UUID,
             "Simple Chinese", "kumkee",
             1, 0, /* App version */
             RESOURCE_ID_IMAGE_MENU_ICON,
             APP_INFO_WATCH_FACE);

Window window;

Layer line_layer;

DynTextLayer time_layer;
DynTextLayer period_layer;
DynTextLayer date_layer;
#if INCLUDE_CCD
DynTextLayer cdate_layer;
#endif
#if INCLUDE_SEC
DynTextLayer sec_layer;
#endif


void line_layer_update_callback(Layer *me, GContext* ctx) {

  graphics_context_set_stroke_color(ctx, CONTENTCOLOR);

  graphics_draw_line(ctx, GPoint(LINE_POS_X, LINE_POS_Y), GPoint(TOT_LENGTH-LINE_POS_X, LINE_POS_Y));
  graphics_draw_line(ctx, GPoint(LINE_POS_X, LINE_POS_Y+1), GPoint(TOT_LENGTH-LINE_POS_X, LINE_POS_Y+1));

}



void handle_init(AppContextRef ctx) {

  window_init(&window, "Simple Chinese");
  window_stack_push(&window, true /* Animated */);
  window_set_background_color(&window, BACKGROUNDCOLOR);

  resource_init_current_app(&APP_RESOURCES);

  layer_init(&line_layer, window.layer.frame);
  line_layer.update_proc = &line_layer_update_callback;
  layer_add_child(&window.layer, &line_layer);

  DTL_init(&time_layer, &window.layer, time_GRECT, time_FONT, _time_upd, _time_upd_cri);

  DTL_init(&date_layer, &window.layer, date_GRECT, date_FONT, _date_upd, _date_upd_cri);
  
  if(!clock_is_24h_style())
  	DTL_init(&period_layer, &window.layer, period_GRECT, period_FONT, _period_upd, _period_upd_cri);

  #if INCLUDE_CCD
  DTL_init(&cdate_layer, &window.layer, cdate_GRECT, cdate_FONT, _cdate_upd, _cdate_upd_cri);
  #endif

  #if INCLUDE_SEC
  DTL_init(&sec_layer, &window.layer, sec_GRECT, sec_FONT, _sec_upd, _sec_upd_cri);
  #endif

}


void handle_minsec_tick(AppContextRef ctx, PebbleTickEvent *evt)
{
  date_layer.update(&date_layer, evt);

  time_layer.update(&time_layer, evt);

  period_layer.update(&period_layer, evt);

  #if INCLUDE_CCD
  cdate_layer.update(&cdate_layer, evt);
  #endif

  #if INCLUDE_SEC
  sec_layer.update(&sec_layer, evt);
  #endif
}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .tick_info = {
      .tick_handler = &handle_minsec_tick,
      .tick_units = MY_TICK_UNIT
    }
  };
  app_event_loop(params, &handlers);
}
