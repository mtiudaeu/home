// Dependencies
//
// program : program_data
//           Calling state switch
//   hotkey_mouse_events <----------
//                                  \
//   state_menu : no_data           |
//      hotkey ---------------------|
//                                  |
//   state_game_loop : game_data    |
//      ai                          |
//      network                     |
//      hotkey ----------------------
//
//
//
/*
#include <dlfcn.h>

const char *GAME_LIBRARY = "./libgame.so";

struct game {
    void *handle;
    ino_t id;
    struct game_api api;
    struct game_state *state;
};

static void game_load(struct game *game)
{
    struct stat attr;
    if ((stat(GAME_LIBRARY, &attr) == 0) && (game->id != attr.st_ino)) {
        if (game->handle) {
            game->api.unload(game->state);
            dlclose(game->handle);
        }
        void *handle = dlopen(GAME_LIBRARY, RTLD_NOW);
        if (handle) {
            game->handle = handle;
            game->id = attr.st_ino;
            const struct game_api *api = (const struct game_api *)dlsym(game->handle, "GAME_API");
            if (api != NULL) {
                game->api = *api;
                if (game->state == NULL)
                    game->state = game->api.init();
                game->api.reload(game->state);
            } else {
                dlclose(game->handle);
                game->handle = NULL;
                game->id = 0;
            }
        } else {
            game->handle = NULL;
            game->id = 0;
        }
    }
}
*/
