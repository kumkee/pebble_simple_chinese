#include "HttpTextLayer.h"

void htl_update(HttpTextLayer *self, PebbleTickEvent* evt)
{
    if(self->is_first_update)
    {
	snprintf(self->content, TXTBUFFERSIZE, "稍候... ");
	text_layer_set_text(&self->text_layer, self->content);
	self->_upd_method(self, evt);
    }
    else if(self->upd_criteria(evt, self))
    {
	self->_upd_method(self, evt);
    }

    //if(self->is_first_update || self->upd_criteria(evt, self))

    self->is_first_update = false;
}


void HTL_init(HttpTextLayer* htl, Layer* p, GRect f, GFont font, void* um, void* uc, HTTPCallbacks* callbacks)
{
   text_layer_init(&(htl->text_layer), p->frame); 
   text_layer_set_text_color(&(htl->text_layer), CONTENTCOLOR); 
   text_layer_set_background_color(&(htl->text_layer), GColorClear); 
   layer_set_frame(&(htl->text_layer.layer), f); 
   text_layer_set_font(&(htl->text_layer), font); 
   text_layer_set_text_alignment(&htl->text_layer, GTextAlignmentRight);
   layer_add_child(p, &(htl->text_layer).layer);

    htl->is_first_update = true;

    htl->_upd_method = um;
    htl->update = htl_update;
    htl->upd_criteria = uc;

   http_register_callbacks(*callbacks, htl);

   get_time(&htl->init_time);

   htl->located = false;
}
