#ifndef _SP_ENTITY_PLAYER_H
#define _SP_ENTITY_PLAYER_H

#include <Nightmare.h>

START_HEAD

NEntity* Player_new();
void Player_destroy(NEntity* player);

void Player_control(NEntity* player);

END_HEAD

#endif
