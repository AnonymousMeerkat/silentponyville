#include <NImage.h>
#include <NEntity.h>
#include <NLevel.h>
#include <NLog.h>
#include <NRsc.h>
#include <NShader.h>
#include <wrap/gl.h>

#include "Globals.h"
#include "entity/Player.h"
#include "entity/Groaner.h"

NImage* level;
NImage* fog;
NImage* fbo1;
NImage* swapfbo;
NImage* fbo2;

NEntity* groan;

bool yesno;

bool Game_init() {
    yesno = false;
    Ndebug("Initing!");
    Globals_init();
    N_player = Player_new();
    N_player->pos.y = 137;
    N_player->z = N_levels[0]->default_layer;
    groan = Groaner_new();
    groan->pos.x = 400;
    //groan->pos.y = 141;
    groan->pos.y = 148;
    groan->z = N_levels[0]->default_layer;
    level = N_images[SP_IMAGE_FAKELEVEL];
    //fog = N_images[SP_IMAGE_FAKEFOG];
    fbo1 = NImage_new(NImage_FBO);
    swapfbo = NImage_new(NImage_FBO);
    fbo2 = NImage_new(NImage_FBO);

    fog = NRsc_load_fog("fog.fog3");

    NLIST_PUSH(N_levels[0]->entities, groan);

    return true;
}

void Game_destroy() {
    Ndebug("Destroying!");
    NImage_destroy(fbo2);
    NImage_destroy(swapfbo);
    NImage_destroy(fbo1);
    NImage_destroy(fog);
    Player_destroy(N_player);
    Globals_destroy();
}

void Game_loop() {
    // Check if ESC key is pressed
    if (N_key_states[27]) {
        N_running = false;
        return;
    }

    // Swap FBO's
    NImage* fbo = fbo1;
    NImage* otherfbo = fbo2;
    if (yesno) {
        fbo = fbo2;
        otherfbo = fbo1;
    }
    yesno = !yesno;

    // Update entities
    Player_update(N_player);
    Groaner_update(groan);

    // Start drawing to the base FBO
    NImage_record(swapfbo);

    glClear(GL_COLOR_BUFFER_BIT);

    NLevel_draw(N_levels[0], fog);

    // Draw fog
#if 0
    uint move_x_amt = ((N_currtime/40)-(int)N_levels[0]->camera)%1024u;
    uint move_y_amt = (-N_currtime/100)%1024u;
    NShader_run(N_shaders[3]);
    NIMAGE_DRAW(fog, .size = Npos2i(1024, 1024), .pos = Npos2i(move_x_amt, move_y_amt));
    NIMAGE_DRAW(fog, .size = Npos2i(1024, 1024), .pos = Npos2i(move_x_amt - 1024, move_y_amt));
    NIMAGE_DRAW(fog, .size = Npos2i(1024, 1024), .pos = Npos2i(move_x_amt - 1024, move_y_amt - 1024));
    NIMAGE_DRAW(fog, .size = Npos2i(1024, 1024), .pos = Npos2i(move_x_amt, move_y_amt - 1024));
    NShader_stop();
#endif

    NImage_stoprecord();

    NIMAGE_DRAW(swapfbo);

    // Draw postprocessing effects
#if 1
    NImage_record(fbo);

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 2.0);

    NShader_run(N_shaders[1]);
    NVec2f_t pos_screen = NVec2f_div(NVec2f_sub(NEntity_center(N_player), NVec2f(N_levels[0]->camera, 0)), NVec2i_2f(N_game_size));
    pos_screen.y = 1-pos_screen.y;
    NShader_set_vec2(N_shaders[1], "SP_pos", pos_screen);
    NIMAGE_DRAW(swapfbo);
    NShader_stop();

    // Draw the other FBO for motion blur
    NIMAGE_DRAW(otherfbo, .alpha = 0.83);

    NImage_stoprecord();

    NIMAGE_DRAW(fbo);
#endif
}
