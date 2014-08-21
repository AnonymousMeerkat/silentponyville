#ifndef _SP_ENTITY_GROANER_H
#define _SP_ENTITY_GROANER_H

#include <NCompat.h>

START_HEAD

#include <NEntity.h>

NEntity* Groaner_new();
void Groaner_destroy(NEntity* groaner);

void Groaner_update(NEntity* groaner);

END_HEAD

#endif
