#include <SDL.h>

#include "glwrappers.h"
#include "tetris.h"

//--------------------------------------------------
static unsigned int compile_shader(unsigned int type,
                                   const std::string& source) {
  unsigned int id = glCreateShader(type);
  const char* src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char* message = (char*)alloca(length * sizeof(char));
    glGetShaderInfoLog(id, length, &length, message);
    LOG_ERROR("Failed to compile shader!");
    LOG_ERROR("%s", message);
    glDeleteShader(id);
    return 0;
  }
  return id;
}

//--------------------------------------------------
static unsigned int create_program(const std::string& vertexShader, const std::string& fragmentShader) {
  unsigned int program = glCreateProgram();
  unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragmentShader);

  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;
}

//--------------------------------------------------
struct TetrisImpl {
  unsigned int buffer;
};

//--------------------------------------------------
Tetris::Tetris() : self(new TetrisImpl()) {
  float positions[6] = {-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f};
  glGenBuffers(1, &self->buffer);
  glBindBuffer(GL_ARRAY_BUFFER, self->buffer);
  glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

  std::string vertexShader = 
"attribute vec4 position;\n"
"void main() { \n"
"  gl_Position = position;\n"
"}\n";
  std::string fragmentShader = 
"void main() { \n"
"  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
"}\n";
  
 unsigned int program = create_program(vertexShader, fragmentShader);
 glUseProgram(program);


}

//--------------------------------------------------
Tetris::~Tetris() {}

//--------------------------------------------------
void Tetris::Render(SDL_Window* window, bool reset, float time_delta) {
  glClear(GL_COLOR_BUFFER_BIT);

  glDrawArrays(GL_TRIANGLES, 0, 3);

  /*
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    SDL_Surface *screenSurface = SDL_GetWindowSurface(window);

    // Clear screen
    //SDL_SetRenderDrawColor(screenSurface, 0xFF, 0xFF, 0xFF, 0xFF);
    //SDL_Clear(screenSurface);
    // Render red filled quad
    SDL_Rect fillRect = {w / 4, h / 4, w / 2,
                         h / 2};
    //SDL_SetDrawColor(screenSurface, 0xFF, 0x00, 0x00, 0xFF);
    SDL_FillRect(screenSurface, &fillRect, SDL_MapRGB(screenSurface->format,
    255, 0, 0) );
  */
}

//--------------------------------------------------
void Tetris::ProcessEvent(SDL_Event* event) {}
