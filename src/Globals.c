#include "Globals.h"

#include <Nightmare.h>

#define genkeys(type, ...)\
short _SP_##type##_keys[] = {\
    __VA_ARGS__, 0\
};\
short* SP_##type##_keys = _SP_##type##_keys;

genkeys(left, 'a', 'h', 'z', 37);
genkeys(right, 'd', 'l', 'c', 39);
genkeys(run, 16, 16);


void Globals_init() {
    SP_left_keys[3] = N_WMan.left_key;
    SP_right_keys[3] = N_WMan.right_key;
    SP_run_keys[0] = N_WMan.lshift_key;
    SP_run_keys[1] = N_WMan.rshift_key;
}

void Globals_destroy() {
}
