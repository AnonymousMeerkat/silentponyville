#include <Nightmare.h>

#include "Globals.h"
#include "entity/Player.h"

NEntity* player;

void Game_init() {
    Ndebug("Initing!");
    Globals_init();
    player = Player_new();
}

void Game_destroy() {
    Ndebug("Destroying!");
    Player_destroy(player);
    Globals_destroy();
}

void Game_loop() {
    /*NSpritesheet_update(N_spritesheets[0]);
    NSpritesheet_draw(N_spritesheets[0], 0, Npos2i(50, 50), 1);*/
    Player_control(player);
    NEntity_update(player);
    NEntity_draw(player);
}
