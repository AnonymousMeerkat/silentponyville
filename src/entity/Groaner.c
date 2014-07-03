#include "Groaner.h"

#include "../Globals.h"

struct Groaner_data {
    uint lasttime;
    int dirtime;
    bool seen_player;
};

NEntity* Groaner_new() {
    NEntity_info Groaner_info = {
        Npos2i(50, 50), N_spritesheets[SP_SPRITESHEET_GROANER], .015, .03
    };
    NEntity* groaner = NEntity_new(Groaner_info);
    struct Groaner_data* data = malloc(sizeof(struct Groaner_data));
    data->lasttime = N_currtime;
    data->dirtime = 0;
    groaner->data = data;

    return groaner;
}

void Groaner_destroy(NEntity* groaner) {
    NEntity_destroy(groaner);
}


void Groaner_update(NEntity* groaner) {
    struct Groaner_data* data = groaner->data;

    NPosi distance = 100;
    if (data->seen_player) {
        distance = 150;
    } else if (NEntity_facing(groaner, N_player)) {
        distance = 120;
    }
    if (NEntity_distance(groaner, N_player) > distance) {
        NEntity_walk(groaner);
        if (data->dirtime == 0 || (N_currtime - data->lasttime) >= (uint)NABS(data->dirtime)) {
            data->dirtime = rand() % 2000 + rand() % 2000 + rand() % 2000;
            if (rand() % 2 == 1) {
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
        groaner->data = data;
    } else {
        NEntity_trot(groaner);
        NEntity_move_towards(groaner, N_player);
        data->dirtime = 0;
        data->seen_player = true;
        groaner->data = data;
    }

    NEntity_update(groaner);
}
