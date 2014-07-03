#include <Nightmare.h>
#include <GLKit/GLKMath.h>

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

void Game_init() {
    yesno = false;
    Ndebug("Initing!");
    Globals_init();
    N_player = Player_new();
    N_player->pos.y = 137;
    N_player->z = N_levels[0]->default_layer;
    groan = Groaner_new();
    groan->pos.x = 400;
    groan->pos.y = 141;
    groan->z = N_levels[0]->default_layer;
    level = N_images[SP_IMAGE_FAKELEVEL];
    //fog = N_images[SP_IMAGE_FAKEFOG];
    fbo1 = NImage_new(NImage_FBO);
    swapfbo = NImage_new(NImage_FBO);
    fbo2 = NImage_new(NImage_FBO);

    NLIST_PUSH(N_levels[0]->entities, groan);
}

void Game_destroy() {
    Ndebug("Destroying!");
    NImage_destroy(fbo2);
    NImage_destroy(swapfbo);
    NImage_destroy(fbo1);
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
    glClearColor(0.0, 0.0, 0.0, 2.0);

    NLevel_draw(N_levels[0]);

    // Draw fog
    /*uint move_x_amt = (N_currtime/20)%2048u;
    uint move_y_amt = (-N_currtime/50)%2048u;
    NImage_draw(fog, Npos2i(move_x_amt, move_y_amt), 0, 1);
    NImage_draw(fog, Npos2i(move_x_amt - 2048, move_y_amt), 0, 1);
    NImage_draw(fog, Npos2i(move_x_amt - 2048, move_y_amt - 2048), 0, 1);
    NImage_draw(fog, Npos2i(move_x_amt, move_y_amt - 2048), 0, 1);*/

    NImage_stoprecord();

    NImage_draw(swapfbo, NPos2i0, 0, 1);

    // Draw postprocessing effects
#if 1
    NImage_record(fbo);

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 2.0);

    NImage_bind(swapfbo);
    NShader_run(N_shaders[1]);
    GLKVector2 pos_screen = GLKVector2Divide(GLKVector2Subtract(NEntity_center(N_player), Npos2f(N_levels[0]->camera, 0)), GLKpos2i(N_game_size));
    pos_screen.y = 1-pos_screen.y;
    NShader_set_vec2(N_shaders[1], "SP_pos", pos_screen);
    NShader_set_float(N_shaders[1], "N_alpha", 1);
    NSquare_draw(NPos2i0, swapfbo->size);
    NShader_stop();
    NImage_unbind();

    // Draw the other FBO for motion blur
    NImage_draw(otherfbo, NPos2i0, 0, 0.83);

    NImage_stoprecord();

    NImage_draw(fbo, NPos2i0, 0, 1);
#endif
}
