#ifndef _SP_GLOBALS_H
#define _SP_GLOBALS_H

#include <Nightmare.h>

START_HEAD

void Globals_init();
void Globals_destroy();

#define SP_SPRITESHEET_PLAYER 0

#define SP_IMAGE_FAKELEVEL 0
#define SP_IMAGE_FAKEFOG 1

// Input

extern int* SP_left_keys;
extern int* SP_right_keys;
extern int* SP_run_keys;

END_HEAD

#endif
