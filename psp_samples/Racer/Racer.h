#ifndef _RACER_H
#define _RACER_H

#include "Tilengine.h"

#define WIDTH	480
#define HEIGHT	272

enum
{
	SPRITESET_TREES,
	MAX_SPRITESET
};

#define MAX_ACTOR	40
#define Z_NEAR		50
#define Z_FAR		1000

extern TLN_Spriteset spritesets[MAX_SPRITESET];
extern int pos;
extern int speed;
extern int pan;


#endif