![Tilengine logo](Tilengine.png)
# Tilengine - The 2D retro graphics engine
[![License: MPL 2.0](https://img.shields.io/badge/License-MPL%202.0-brightgreen.svg)](https://opensource.org/licenses/MPL-2.0)
[![Build Status](https://travis-ci.org/megamarc/Tilengine.svg?branch=master)](https://travis-ci.org/megamarc/Tilengine)

Tilengine-PSP is the PSP port of [Tilengine](https://github.com/megamarc/Tilengine).
Tilengine is an open source, cross-platform 2D graphics engine for creating classic/retro games with tile maps, sprites and palettes. Its unique scanline-based rendering algorithm makes raster effects a core feature, a technique used by many games running on real 2D graphics chips.

http://www.tilengine.org

Thanks [megamarc](https://github.com/megamarc) for writing such a portable and easy to read code.

# Contents
- [Tilengine - The 2D retro graphics engine](#tilengine---the-2d-retro-graphics-engine)
- [Contents](#contents)
- [Features](#features)
- [Getting binaries](#getting-binaries)
  - [Build from source](#build-from-source)
    - [PSP](#psp)
- [Running the samples](#running-the-samples)
  - [PSP](#unix-like)
- [The tilengine window](#the-tilengine-window)
- [Creating your first program](#creating-your-first-program)
- [Documentation](#documentation)
- [Editing assets](#editing-assets)
- [Creating packages](#creating-packages)
- [Bindings](#bindings)
- [Contributors](#contributors)

# Features
* Written in portable C (C99)
* MPL 2.0 license: free for any project, including commercial ones, allows console development
* Cross platform: available builds for Windows (32/64), Linux PC(32/64), Mac OS X and Raspberry Pi
* High performance: all samples run at 60 fps with CRT emulation enabled on a Raspberry Pi 3
* Streamlined, easy to learn API that requires very little lines of code
* Built-in SDL-based windowing for quick tests
* Integrate inside any existing framework as a slave renderer
* Loads assets from open standard standard file formats
* Create or modify graphic assets procedurally at run time
* True raster effects: modify render parameters between scanlines
* Background layer scaling and rotation
* Sprite scaling
* Several blending modes for layers and sprites
* Pixel accurate sprite vs sprite and sprite vs layer collision detection
* ~Special effects: per-column offset, mosaic, per-pixel displacement, CRT emulation...~
* Supports packaged assets with optional AES-128 encryption

# TODO
* offload math tasks to vfpu
* add the special effects (per-column offset, mosaic, per-pixel displacement, CRT emulation)
* change graphics renderer from SDL1.2 to sceGU

# Getting binaries


## Build from source
You can also build the library from source. Tilengine-PSP requires `SDL1.2` and `libpng` to build.

```
  make -f Makefile.psp
```


# Running the samples

C samples for the PSP are located in `Tilengine/psp_samples` folder. To build them you need the [pspsdk](https://github.com/pspdev/pspsdk).

Once installed, open a console window in the C samples folder and type 

```
> make
```
# Creating your first program
The following section shows how to create from scratch and execute a simple tilengine application that does the following:
1. Setup the PSP exit callback.
2. Reference the inclusion of Tilengine module
3. Initialize the engine with a resolution of 480x272, one layer, no sprites and no palette animations
4. Load a *tilemap*, the asset that contains background layer data
5. Attach the loaded tilemap to the allocated background layer
6. Create a display window with default parameters
7. Run the window loop, updating the display at each iteration until the window is closed
8. Release allocated resources

![Test](test.png)

Create a file called `test.c` in `Tilengine/samples` folder, and type the following code:
```
#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <pspctrl.h>

#include <pspgu.h>
#include <pspgum.h>
#include <pspge.h>
#include "Tilengine.h"

PSP_MODULE_INFO("Example", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

int main(int argc, char* argv[]) 
{
	  setupExitCallback ();
    
    TLN_Tilemap foreground;

    TLN_Init (480, 272, 1, 0, 0);
    TLN_SetLoadPath ("assets/sonic");
    foreground = TLN_LoadTilemap ("assets/sonic/Sonic_md_fg1.tmx", NULL);
    TLN_SetLayerTilemap (0, foreground);

    TLN_CreateWindow (NULL, 0);
    while (isRunning ()) 
    {
        TLN_DrawFrame (0);
    }

    TLN_DeleteTilemap (foreground);
    TLN_Deinit ();
    
    sceKernelExitGame ();
    
    return 0;
}
```

# Documentation
Doxygen-based documentation and API reference can be found in the following link:
http://www.tilengine.org/doc

# Editing assets
Tilengine is just a programming library that doesn't come with any editor, but the files it loads are made with standard open-source tools. Samples come bundled with several ready-to-use assets, but these are the tools you'll need to edit or create new ones:
* Source code: [VSCode](https://code.visualstudio.com/), [Notepad++](https://notepad-plus-plus.org/downloads/)...
* Graphics, tiles & sprites: [Aseprite](https://www.aseprite.org/), [Piskel](https://www.piskelapp.com/), [Grafx2](http://grafx2.chez.com/)...
* Maps: [Tiled Map Editor](https://www.mapeditor.org/)


# Contributors
These people contributed to tilengine:

@turric4an - the Pascal wrapper<br>
@davideGiovannini - help with the Linux-x86_64 port<br>
@shayneoneill - help with the OS X port<br>
@adtennant - provided cmake and pkg-config support<br>
@tvasenin - improved C# binding<br>
@tyoungjr - LUA/FFI binding<br>

# Disclaimer
This repository contains sprites from the Mario and Sonic series for use in its examples. The use of these sprites is strictly intended for educational purposes, and no infringement is intended upon the original copyright holders. If the use of these sprites is in violation of the copyright holders' wishes, we will remove any offending assets upon request.
