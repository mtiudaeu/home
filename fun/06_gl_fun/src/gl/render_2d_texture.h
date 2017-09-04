#ifndef GL_RENDER_2D_H
#define GL_RENDER_2D_H

#include "gl/drawing_data_2d.h"

#include "app.h"

Status gl_render_2d_init();
Status gl_render_2d();

drawing_data_2d_s& gl_render_2d_get_data();

#endif
