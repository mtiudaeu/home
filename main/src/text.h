#ifndef TEXT_H
#define TEXT_H

#include <string>

namespace text {

void init();
void uninit();

struct Context {
  float x;
  float y;
  float size;
  std::string value;
};

void render(Context& context);
}

#endif

