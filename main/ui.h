#ifndef UI
#define UI

struct UiContext;

UiContext* ui_create();
void ui_render(UiContext& ui_context);
UiContext* ui_destroy(UiContext* ui_context);

#endif
