
MODULES = main ui shader_utils text gl_wrapper assets menu square
ASSETS = assets/font.png assets/shaders/e_font_f.txt assets/shaders/e_font_v.txt assets/shaders/e_ui_f.txt assets/shaders/e_ui_v.txt

UNAME = $(shell uname -s)
BUILDDIR = ../build
BINDIR = ../bin
WWWDIR = ../www
_MKDIRS := $(shell mkdir -p $(BINDIR) $(WWWDIR) $(BUILDDIR))

COMMONFLAGS = -std=c++2a -MMD -MP -isystem .
LOCALFLAGS = -g -O2 $(COMMONFLAGS) $(shell pkg-config --cflags sdl2)

NOWARNDIRS = stb/
LOCALWARN = -Wall -Wextra -pedantic -Wpointer-arith -Wshadow -Wfloat-conversion -Wfloat-equal -Wno-unused-function -Wno-unused-parameter
# NOTE: also useful but noisy -Wconversion -Wshorten-64-to-32

LOCALLIBS = $(shell sdl2-config --libs) -lSDL2_image
ifeq ($(UNAME),Darwin)
	LOCALLIBS += -Wl,-dead_strip -framework OpenGL
else
	LOCALLIBS += -lGL
endif

EMXX = em++
EMXXFLAGS = $(COMMONFLAGS) -Oz -s USE_SDL=2 -s USE_SDL_IMAGE=2
# -s SAFE_HEAP=1 -s ASSERTIONS=2 --profiling  -s DEMANGLE_SUPPORT=1
EMXXLINK = -s TOTAL_MEMORY=50331648 --use-preload-plugins

all: $(BINDIR)/main

$(WWWDIR): $(WWWDIR)/index.html $(WWWDIR)/_main.js

$(BINDIR)/main: $(MODULES:%=$(BUILDDIR)/%.o) Makefile
	$(CXX) $(LOCALFLAGS) $(filter %.o,$^) $(LOCALLIBS) -o $@

$(WWWDIR)/index.html: emscripten-shell.html
	cp emscripten-shell.html $(dir $@)index.html

$(WWWDIR)/_main.js: $(MODULES:%=$(BUILDDIR)/%.em.o) $(ASSETS) Makefile
	$(EMXX) $(EMXXFLAGS) $(EMXXLINK) $(filter %.o,$^) $(ASSETS:%=--preload-file %) -o $@

$(BUILDDIR)/%.em.o: %.cpp Makefile
	@mkdir -p $(dir $@)
	@echo $(EMXX) -c $< -o $@
	@$(EMXX) $(EMXXFLAGS) -c $< -o $@

# The $(if ...) uses my warning flags only in WARNDIRS
$(BUILDDIR)/%.o: %.cpp Makefile
	@mkdir -p $(dir $@)
	@echo $(CXX) -c $< -o $@
	@$(CXX) $(LOCALFLAGS) $(if $(filter-out $(NOWARNDIRS),$(dir $<)),$(LOCALWARN)) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)/* $(BINDIR)/* $(WWWDIR)/*

include $(shell find $(BUILDDIR) -name \*.d)
