#ifndef _SP_ENTITY_PLAYER_H
#define _SP_ENTITY_PLAYER_H

#include <NEntity.h>

NEntity* Player_new();
void Player_destroy(NEntity* player);

void Player_update(NEntity* player);

#endif
