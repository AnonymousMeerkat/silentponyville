#ifndef _SP_ENTITY_PLAYER_H
#define _SP_ENTITY_PLAYER_H

#include <NCompat.h>

START_HEAD

#include <NEntity.h>

NEntity* Player_new();
void Player_destroy(NEntity* player);

void Player_update(NEntity* player);

END_HEAD

#endif
