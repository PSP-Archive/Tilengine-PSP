#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <pspctrl.h>

#include <pspgu.h>
#include <pspgum.h>
#include <pspge.h>

#include "../common/callback.h"

#include <stdio.h>
#include "Tilengine.h"

#define WIDTH	480
#define HEIGHT	272

PSP_MODULE_INFO("SuperMarioClone", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);


/* layers */
enum
{
	LAYER_FOREGROUND,
	LAYER_BACKGROUND,
	MAX_LAYER
};

int main (int argc, char* argv[])
{
	setupExitCallback();

	TLN_Sequence seq_walking;
	TLN_Spriteset spriteset;
	TLN_Tilemap foreground, background;
	int player_x = -16;
	int player_y = 160;

	/* basic setup */
	TLN_Init (WIDTH, HEIGHT, MAX_LAYER,1,0);
	TLN_SetBGColor (0, 96, 184);

	/* load resources */
	TLN_SetLoadPath ("assets/");
	foreground = TLN_LoadTilemap ("smw_foreground.tmx", NULL);
	background = TLN_LoadTilemap ("smw_background.tmx", NULL);
	TLN_SetLayerTilemap (LAYER_FOREGROUND, foreground);
	TLN_SetLayerTilemap (LAYER_BACKGROUND, background);
	TLN_SetLayerPosition (LAYER_FOREGROUND, 0,48);
	TLN_SetLayerPosition (LAYER_BACKGROUND, 0,80);

	/* setup sprite */
	spriteset = TLN_LoadSpriteset ("smw_sprite");
	TLN_SetSpriteSet (0, spriteset);
	TLN_SetSpritePicture (0, 0);
	TLN_SetSpritePosition (0, player_x, player_y);

	/* setup animations */
	seq_walking = TLN_CreateSpriteSequence (NULL, spriteset, "walking", 6);
	TLN_SetSpriteAnimation (0, seq_walking, 0);

	/* main loop */
	TLN_CreateWindow (NULL, 0);
	while (isRunning())//TLN_ProcessWindow())
	{
		player_x += 1;
		if (player_x >= WIDTH)
			player_x = -16;
		TLN_SetSpritePosition (0, player_x, player_y);
		TLN_DrawFrame (0);
	}

	/* deinit */
	TLN_DeleteTilemap (foreground);
	TLN_DeleteTilemap (background);
	TLN_Deinit ();

	sceKernelExitGame();

	return 0;
}
