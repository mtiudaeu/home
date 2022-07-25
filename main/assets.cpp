#include "assets.h"

#ifdef __EMSCRIPTEN__

const char* const SHADER_FONT_F_PATH = "assets/shaders/e_font_f.txt";
const char* const SHADER_FONT_V_PATH = "assets/shaders/e_font_v.txt";
const char* const SHADER_UI_F_PATH = "assets/shaders/e_ui_f.txt";
const char* const SHADER_UI_V_PATH = "assets/shaders/e_ui_v.txt";

#else

const char* const SHADER_FONT_F_PATH = "assets/shaders/g_font_f.txt";
const char* const SHADER_FONT_V_PATH = "assets/shaders/g_font_v.txt";
const char* const SHADER_UI_F_PATH = "assets/shaders/g_ui_f.txt";
const char* const SHADER_UI_V_PATH = "assets/shaders/g_ui_v.txt";

#endif
