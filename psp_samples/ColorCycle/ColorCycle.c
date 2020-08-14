#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <pspctrl.h>

#include <pspgu.h>
#include <pspgum.h>
#include <pspge.h>

#include "../common/callback.h"

#include <stdio.h>
#include <string.h>
#include "Tilengine.h"

PSP_MODULE_INFO("ColorCycle", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

int main (int argc, char* argv[])
{
	setupExitCallback();

	TLN_Bitmap background;
	TLN_SequencePack sp;
	TLN_Sequence sequence;
	TLN_Palette palette;

	/* engine init */
	TLN_Init (480, 272, 0, 0, 1);

	/* load resources */
	TLN_SetLoadPath ("assets/");
	background = TLN_LoadBitmap ("beach.png");
	palette    = TLN_GetBitmapPalette (background);
	sp		   = TLN_LoadSequencePack ("beach.sqx");
	sequence   = TLN_FindSequence (sp, "beach");

	/* setup */
	TLN_SetBGBitmap (background);
	TLN_SetPaletteAnimation (0, palette, sequence, true);

	/* main loop */
	TLN_CreateWindow (NULL, 0);
	while (isRunning ())//TLN_ProcessWindow ())
		TLN_DrawFrame (0);

	TLN_DeleteBitmap (background);
	TLN_DeleteSequencePack (sp);
	TLN_Deinit ();

	sceKernelExitGame();

	return 0;
}
