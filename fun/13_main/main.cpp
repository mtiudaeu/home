// Copyright 2015 Red Blob Games <redblobgames@gmail.com>
// License: Apache v2.0 <http://www.apache.org/licenses/LICENSE-2.0.html>

#include "common.h"
#include "glwrappers.h"
#include "window.h"
#include "render-sprites.h"
#include "render-shapes.h"
#include "render-surface.h"
#include "font.h"
#include "tetris.h"

#include <SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define SHOW_SPRITES 0
#define SHOW_SHAPES 0
#define SHOW_OVERLAY 1
#define TETRIS 1

std::unique_ptr<Window> window;
std::unique_ptr<RenderSprites> sprite_layer;
std::unique_ptr<RenderShapes> shape_layer;
static bool main_loop_running = true;

Triangle tri(float x1, float y1, float x2, float y2, float x3, float y3) {
  return Triangle{{x1, x2, x3}, {y1, y2, y3}};
}

void main_loop() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT: {
      main_loop_running = false;
      break;
    }
    case SDL_KEYUP: {
      int sym = event.key.keysym.sym;
      if (sym == SDLK_ESCAPE) { main_loop_running = false; }
      break;
    }
    case SDL_MOUSEBUTTONDOWN: {
      LOG("Mouse have been cliked mdtmp!");
      SDL_MouseButtonEvent& mouse_event = event.button;
      LOG("x:%d,y:%d", mouse_event.x, mouse_event.y);
      break;
    }
    }

    window->ProcessEvent(&event);
  }

  if (window->visible) {
    static float t = 0.0;
    t += 0.01f;

#if SHOW_SPRITES
    {
      std::vector<Sprite> sprites;
      int SIDE = 4; // Try changing to 100; can't have more than 128 though because I use GLushort somewhere
      int NUM = SIDE * SIDE;
      for (int j = 0; j < NUM; j++) {
        sprites.emplace_back();
        auto& s = sprites.back();
        s.image_id = 0;
        s.x = (0.5f + j % SIDE - 0.5f*SIDE + ((j/SIDE)%2) * 0.5f - 0.25f) * 2.0f / SIDE;
        s.y = (0.5f + j / SIDE - 0.5f*SIDE) * 2.0f / SIDE;
        s.scale = 2.0f / SIDE;
        s.rotation_degrees = j * 0.03f * t * DEG_TO_RAD;
      }

      sprite_layer->SetSprites(sprites);
    }
#endif

#if SHOW_SHAPES
    {
      std::vector<Shape> shapes;
      Shape s;
      s.r = 1.0; s.g = 0.5; s.b = 0.5; s.a = 1.0;
    
      s.triangles = {
        tri(0, -3, 1, -1, 0.5, 0),
        tri(1, -1, 3, 0, 0.5, 0),
        tri(3, 0, 1, 1, 0.5, 0),
        tri(1, 1, 0, 3, 0.5, 0),
        tri(0, 3, 0, 1, 0.5, 0),
        tri(0, 1, -1, 1, 0.5, 0),
        tri(-1, 1, -1, -1, 0.5, 0),
        tri(-1, -1, 0, -1, 0.5, 0),
        tri(0, -1, 0, -3, 0.5, 0)
      };
      shapes.push_back(s);
    
      shape_layer->SetShapes(shapes);
    }
#endif
    
    window->Render();
  }
}


int main(int, char**) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) { FAIL("SDL_Init"); }
  SDL_GL_SetSwapInterval(1);

  window = std::unique_ptr<Window>(new Window(800, 600));

  Font font("assets/DroidSans.ttf", 32, window.get());
  font.Draw(1, font.Baseline(), "Hello world");

#if SHOW_SPRITES
  sprite_layer = std::unique_ptr<RenderSprites>(new RenderSprites);
  window->AddLayer(sprite_layer.get());
#endif

#if SHOW_SHAPES
  shape_layer = std::unique_ptr<RenderShapes>(new RenderShapes);
  window->AddLayer(shape_layer.get());
#endif

#if SHOW_OVERLAY
  std::unique_ptr<IRenderLayer> overlay_layer(font.createRenderLayer());
  window->AddLayer(overlay_layer.get());
#endif

#if TETRIS
  std::unique_ptr<Tetris> tetris_layer(new Tetris());
  window->AddLayer(tetris_layer.get());
#endif
  
#ifdef __EMSCRIPTEN__
  // 0 fps means to use requestAnimationFrame; non-0 means to use setTimeout.
  emscripten_set_main_loop(main_loop, 0, 1);
#else
  while (main_loop_running) {
    main_loop();
    SDL_Delay(16);
  }
#endif

  sprite_layer = nullptr;
  shape_layer = nullptr;
  window = nullptr;
  SDL_Quit();
}