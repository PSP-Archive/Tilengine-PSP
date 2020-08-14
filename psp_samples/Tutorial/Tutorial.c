#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <pspctrl.h>

#include <pspgu.h>
#include <pspgum.h>
#include <pspge.h>

#include "../common/callback.h"

#include "Tilengine.h"

#define WIDTH	480
#define HEIGHT	270

PSP_MODULE_INFO("Tutorial", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

/* entry point */
int main (int argc, char* argv[])
{
	setupExitCallback();


	TLN_Tilemap tilemap;
	int frame = 0;

	/* setup engine */
	TLN_Init (WIDTH, HEIGHT, 1,0,0);

	/* load layer */
	tilemap = TLN_LoadTilemap ("assets/Sonic_md_fg1.tmx", NULL);
	
	/* setup the layer */
	TLN_SetLayer (0, NULL, tilemap);
	TLN_SetBGColor (32,32,128);



	/* main loop */
	TLN_CreateWindow (NULL, 0);
	while (isRunning())
	{
		//TLN_ProcessWindow ();
		/* scroll the layer, one pixel per frame */
		TLN_SetLayerPosition (0, frame, 0);
		
		/* render to the window */
		TLN_DrawFrame (0);
		frame++;
	}

	/* release resources */
	TLN_DeleteTilemap (tilemap);
	TLN_Deinit ();

	sceKernelExitGame();

	return 0;
}
