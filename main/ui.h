#ifndef UI
#define UI

#include "global.h"

struct UiContext;

UiContext* ui_create();
void ui_render(const GlobalContext& global_context, UiContext& ui_context);
UiContext* ui_destroy(UiContext* ui_context);

#endif
