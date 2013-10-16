#include "HttpTextLayer.h"

void htl_update(HttpTextLayer *self, PebbleTickEvent* evt)
{
    if(self->mydtl.is_first_update)
    {
	snprintf(self->mydtl.content, TXTBUFFERSIZE, "稍候... ");
	text_layer_set_text(&self->mydtl.text_layer, self->mydtl.content);
    }

    if(self->mydtl.is_first_update || self->_upd_criteria(evt, self))
    {
	self->_upd_method(self, evt);
	text_layer_set_text(&self->mydtl.text_layer, self->mydtl.content);
    }

    self->mydtl.is_first_update = false;
}


void HTL_init(HttpTextLayer* htl, Layer* parent, GRect frame, GFont font, void* u_method, void* u_criteria, HTTPCallbacks* callbacks)
{
   DTL_init(&htl->mydtl, parent, frame, font, NULL, NULL);

   text_layer_set_text_alignment(&htl->mydtl.text_layer, GTextAlignmentRight);

   http_register_callbacks(*callbacks, htl);

   get_time(&htl->init_time);

   htl->located = false;

   htl->_upd_method = u_method;
   htl->_upd_criteria = u_criteria;
   htl->update = htl_update;
}
