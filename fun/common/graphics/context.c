#include "graphics/context.h"

#include <stdlib.h>
#include <assert.h>

GraphicsContext* graphics_context_malloc() {
  GraphicsContext* graphics_context = malloc(sizeof(GraphicsContext));
  // MDTMP set program_id and initialize program context
  graphics_context->program_id = 0;
  return graphics_context;
}

void graphics_context_free(GraphicsContext* graphics_context) {
  assert(graphics_context);
  // MDTMP uninitialize program_id
  free(graphics_context);
}
