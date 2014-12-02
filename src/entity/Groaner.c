#include "Groaner.h"

#include "../Globals.h"
#include <NGlobals.h>
#include <stdlib.h>

struct Groaner_data {
    uint lasttime;
    uint alerted_time;
    uint shock_time;
    uint attack_delay;
    int dirtime;
    bool seen_player;
    bool attacking;
};

NEntity* Groaner_new() {
    NEntity_info Groaner_info = {
        NVec2i(50, 50), N_spritesheets[SP_SPRITESHEET_GROANER], .015, .03
    };
    NEntity* groaner = NEntity_new(Groaner_info);
    struct Groaner_data* data = malloc(sizeof(struct Groaner_data));
    data->lasttime = N_currtime;
    data->dirtime = 0;
    data->alerted_time = 0;
    data->shock_time = 0;
    data->attack_delay = 0;

    data->attacking = false;
    data->seen_player = false;
    groaner->data = data;

    return groaner;
}

void Groaner_destroy(NEntity* groaner) {
    NEntity_destroy(groaner);
}


void Groaner_update(NEntity* groaner) {
    struct Groaner_data* data = groaner->data;

    if (data->shock_time != 0 && N_currtime - data->shock_time < 2000) {
        if (N_player->state == NEntity_TROT) {
            data->seen_player = true;
        } else {
            goto end;
        }
    } else {
        data->shock_time = 0;
    }

    bool facing = NEntity_facing(groaner, N_player);
    int distance = NEntity_distance(groaner, N_player);

    int min_distance = 100;
    if (data->seen_player) {
        min_distance = 180;
    } else if (N_currtime - data->alerted_time < 5000) {
        if (facing) {
            min_distance = 160;
        } else {
            min_distance = 140;
        }
    } else if (facing) {
        if (SP_moved) {
            min_distance = 150;
        } else {
            min_distance = 130;
        }
    }
    if (distance > min_distance) {
        if (SP_moved && ((facing && (distance < 180)) || (!facing && (distance < 150)))) {
                NEntity_still(groaner);
                data->shock_time = N_currtime;
                goto end;
        }
        NEntity_walk(groaner);
        if (data->dirtime == 0 || (N_currtime - data->lasttime) >= (uint)NABS(data->dirtime)) {
            // This will encourage more middleish values
            data->dirtime = rand() % 2000 + rand() % 2000 + rand() % 2000;

            if (data->seen_player) {
                data->alerted_time = N_currtime;

                if ((groaner->pos.x - N_player->pos.x) < 0) {
                    data->dirtime = -data->dirtime;
                }
            } else if (rand() % 2 == 1) {
                data->dirtime = -data->dirtime;
            }

            data->lasttime = N_currtime;
        }

        if (data->dirtime < 0) {
            NEntity_left(groaner);
        } else {
            NEntity_right(groaner);
        }

        data->seen_player = false;
    } else if (distance > 50) {
        NEntity_trot(groaner);
        NEntity_move_towards(groaner, N_player);
        data->dirtime = 0;
        data->seen_player = true;
    } else {
        if (data->attacking && groaner->state != NEntity_ATTACK) {
            if (data->attack_delay == 0) {
                data->attack_delay = N_currtime;
            } else if ((N_currtime - data->attack_delay) >= 500) {
                NEntity_attack(groaner);
            }
        } else {
            NEntity_attack(groaner);
            data->attacking = true;
            data->attack_delay = 0;
        }
    }

end:

    groaner->data = data;
    NEntity_update(groaner);
}
