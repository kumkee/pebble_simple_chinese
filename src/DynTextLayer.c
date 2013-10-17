#include "DynTextLayer.h"
#include "stdarg.h"


void update(DynTextLayer *self, PebbleTickEvent* evt)
{
    if(self->is_first_update || self->_upd_criteria(evt))
    {
	self->_upd_method(self,evt);
	text_layer_set_text(&self->text_layer, self->content);
    }

    if(self->is_first_update) self->is_first_update = false;
}


void DTL_init(DynTextLayer* dtl, Layer* p, GRect f,  GFont font, void* um, void* uc)
{
    text_layer_init(&(dtl->text_layer), p->frame); 
    text_layer_set_text_color(&(dtl->text_layer), CONTENTCOLOR); 
    text_layer_set_background_color(&(dtl->text_layer), GColorClear); 
    layer_set_frame(&(dtl->text_layer.layer), f); 
    text_layer_set_font(&(dtl->text_layer), font); 
    layer_add_child(p, &(dtl->text_layer).layer);

    dtl->is_first_update = true;

    dtl->_upd_method = (void(*)(DynTextLayer*,PebbleTickEvent*)) (um);
    dtl->update = update;
    dtl->_upd_criteria = uc;
}


void DTL_mv_horz(DynTextLayer *dtl, int16_t dx)
{
    GRect r = layer_get_frame( &dtl->text_layer.layer );
    r.origin.x += dx;

    layer_set_frame( &dtl->text_layer.layer, r);
}


void DTL_mv_vert(DynTextLayer *dtl, int16_t dy)
{
    GRect r = layer_get_frame( &dtl->text_layer.layer );
    r.origin.y += dy;

    layer_set_frame( &dtl->text_layer.layer, r);
}
