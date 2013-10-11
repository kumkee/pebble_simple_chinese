#include "HttpTextLayer.h"

void HTL_init(HttpTextLayer* htl, Layer* parent, GRect frame, GFont font, void* u_method, void* u_criteria, HTTPCallbacks* callbacks)
{
   DTL_init(&htl->mydtl, parent, frame, font, u_method, u_criteria);

   text_layer_set_text_alignment(&htl->mydtl.text_layer, GTextAlignmentRight);

   http_register_callbacks(*callbacks, htl);

   htl->located = false;
}
