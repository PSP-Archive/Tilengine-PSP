TARGET = Tutorial
OBJS = Tutorial.o ../common/callback.o 

INCDIR += ../../include
CFLAGS = -G0 -Wall -Ofast
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR += ../../lib/psp/
LDFLAGS =
LIBS = -lTilengine -lSDL_ttf -lfreetype -lSDL_image -lpng -ljpeg -lSDLmain -lSDL -lg -lc -lGL -lGLU -lglut -lz -lm \
            -lpspvfpu -lpspvram \
            -L${PSPDEV}/psp/sdk/lib \
            -L${PSPDEV}/psp \
            -lpspdebug  -lpspgu -lpspctrl -lpspge -lpspirkeyb -lpsppower -lpsppower_driver \
            -lpspdisplay -lpsphprm  -lpspsdk -lpsprtc -lpspaudio -lpsputility \
            -lpspnet_inet  -lc -lpspuser

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Tutorial

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
