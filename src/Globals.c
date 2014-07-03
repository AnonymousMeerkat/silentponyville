#include "Globals.h"

#include <Nightmare.h>

#define genkeys(type, ...)\
short _SP_##type##_keys[] = {\
    __VA_ARGS__, 0\
};\
short* SP_##type##_keys = _SP_##type##_keys;

genkeys(left, 'A', 'H', 'Z', 37);
genkeys(right, 'D', 'L', 'C', 39);
genkeys(run, 16);

bool SP_moved;


void Globals_init() {
    SP_left_keys[3] = N_WMan.left_key;
    SP_right_keys[3] = N_WMan.right_key;
    SP_run_keys[0] = N_WMan.shift_key;

    SP_moved = false;
}

void Globals_destroy() {
}
