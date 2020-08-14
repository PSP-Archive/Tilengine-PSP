/******************************************************************************
*
* Tilengine sample
* 2015 Marc Palacios
* http://www.tilengine.org
*
* This example show a classic Mode 7 perspective projection plane like the 
* one seen in SNES games like Super Mario Kart. It uses a single transformed
* layer with a raster effect setting the scaling factor for each line
*
******************************************************************************/
#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <pspctrl.h>

#include <pspgu.h>
#include <pspgum.h>
#include <pspge.h>

#include "../common/callback.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Tilengine.h"
#include "Sin.h"

#define WIDTH	480
#define HEIGHT	272

PSP_MODULE_INFO("Mode7", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

/* linear interploation */
#define lerp(x, x0,x1, fx0,fx1) \
	(fx0) + ((fx1) - (fx0))*((x) - (x0))/((x1) - (x0))

/*
/* layers */
enum
{
	LAYER_FOREGROUND,
	LAYER_BACKGROUND,
	MAX_LAYER
};

enum
{
	MAP_HORIZON,
	MAP_TRACK,
	MAX_MAP
};

int pos_foreground = {0};
int pos_background[6] = {0};
int inc_background[6] = {0};

fix_t x,y,s,a;

static TLN_Tileset road, horizon;
static int angle;

static void raster_callback (int line);

/* entry point */
int main (int argc, char* argv[])
{
	setupExitCallback();

	/* setup engine */
	TLN_Init (WIDTH,HEIGHT, MAX_LAYER, 0, 0);
	TLN_SetRasterCallback (raster_callback);
	TLN_SetBGColor (0,0,0);

	/* load resources*/
	TLN_SetLoadPath ("assets/");
	road = TLN_LoadTilemap ("track1.tmx", NULL);
	horizon = TLN_LoadTilemap ("track1_bg.tmx", NULL);

	/* startup display */
	TLN_CreateWindow (NULL, 0);

	x = int2fix(-136);
	y = int2fix(336);
	s = 0;
	a = float2fix(0.2f);
	angle = 0;
	BuildSinTable ();

	/* main loop */
	while (isRunning())//TLN_ProcessWindow ())
	{
		TLN_SetLayerTilemap (LAYER_FOREGROUND, horizon);
		TLN_SetLayerTilemap (LAYER_BACKGROUND, horizon);
		TLN_SetLayerPosition (LAYER_FOREGROUND, lerp(angle*2, 0,360, 0,256), 24);
		TLN_SetLayerPosition (LAYER_BACKGROUND, lerp(angle, 0,360, 0,256), 0);
		TLN_ResetLayerMode (LAYER_BACKGROUND);

		/* input */		
		if (TLN_GetInput (INPUT_LEFT))
			angle-=2;
		else if (TLN_GetInput (INPUT_RIGHT))
			angle+=2;
		if (TLN_GetInput (INPUT_UP))
		{
			s += a;
			if (s > int2fix(2))
				s = int2fix(2);
		}
		else if (s >= a)
			s -= a;
		if (TLN_GetInput (INPUT_DOWN))
		{
			s -= a;
			if (s < -int2fix(2))
				s = -int2fix(2);
		}
		else if (s <= -a)
			s += a;

		if (s != 0)
		{
			angle = angle%360;
			if (angle < 0)
				angle += 360;

			x += CalcSin (angle, s);
			y -= CalcCos (angle, s);
		}

		/* render to window */
		TLN_DrawFrame (0);
	}

	/* deinit */
	TLN_DeleteTilemap (road);
	TLN_DeleteTilemap (horizon);
	TLN_DeleteWindow ();
	TLN_Deinit ();

	sceKernelExitGame();

	return 0;
}

/* raster callback (virtual HBLANK) */
static void raster_callback (int line)
{
	if (line == 24)
	{
		TLN_SetLayerTilemap (LAYER_BACKGROUND, road);
		TLN_SetLayerPosition (LAYER_BACKGROUND, fix2int(x), fix2int(y));
		TLN_DisableLayer (LAYER_FOREGROUND);
	}

	if (line >= 24)
	{
		fix_t s0 = float2fix (0.2f);
		fix_t s1 = float2fix (5.0f);
		fix_t s = lerp (line, 24,HEIGHT, s0,s1);
		float scale = fix2float (s);
		TLN_SetLayerTransform (LAYER_BACKGROUND, (float)angle, WIDTH/2, HEIGHT, scale, scale);
	}
}
