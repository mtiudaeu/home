#ifndef UI
#define UI

struct UiContext;

void ui_create(UiContext& ui_context);

void ui_render(UiContext& ui_context);

void ui_destroy(UiContext& ui_context);

#endif
