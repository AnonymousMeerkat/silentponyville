#include "Player.h"

#include "../Globals.h"

NEntity* Player_new() {
    NEntity_info Player_info = {
        Npos2i(50, 50), N_spritesheets[SP_SPRITESHEET_PLAYER], .027, .04
    };
    return NEntity_new(Player_info);
}

void Player_destroy(NEntity* player) {
    NEntity_destroy(player);
}

void Player_update(NEntity* player) {
#define check(dir) \
    bool dir##_down = false;\
    for (short i = 0; SP_##dir##_keys[i] && !(dir##_down = N_key_states[(int)SP_##dir##_keys[i]]); i++);

    check(left);
    check(right);
    check(run);

    SP_moved = true;

    if (run_down) {
        NEntity_trot(player);
    } else {
        NEntity_walk(player);
    }

    if (left_down) {
        NEntity_left(player);
    } else if (right_down) {
        NEntity_right(player);
    } else {
        SP_moved = false;
        NEntity_still(player);
    }

    NEntity_update(player);
}
