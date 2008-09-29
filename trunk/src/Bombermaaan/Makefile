# SDL library
SDL_CONFIG := sdl-config
SDL_CFLAGS := $(shell $(SDL_CONFIG) --cflags)
SDL_LDFLAGS := $(shell $(SDL_CONFIG) --libs) -lSDL_mixer

CPP  = g++
CC   = gcc
OBJ  = CBoard.o CClock.o CCloudManager.o CCommandChunk.o CControls.o CDemo.o CDrawGame.o CHurryMessage.o CMatch.o CMenu.o CMenuBase.o CMenuBomber.o CMenuInput.o CMenuLevel.o CMenuMatch.o CMenuYesNo.o CModeScreen.o CMosaic.o CPauseMessage.o CRandomMosaic.o CScroller.o CTitle.o CVictory.o CWinner.o CConsole.o CSDLVideo.o CSDLInput.o CLog.o CWindow.o CDebug.o CDisplay.o CFont.o CGame.o CInput.o CMainInput.o COptions.o CPlayerInput.o CScores.o CSound.o CArena.o CArenaCloser.o CArenaSnapshot.o CBomb.o CBomber.o CBomberMove.o CElement.o CExplosion.o CFloor.o CItem.o CWall.o CAiArena.o CAiBomber.o CAiManager.o WinMain.o winreplace.o
SRC  = $(OBJ:%.o=%.cpp) STDAFX.CPP
LINKOBJ = $(OBJ) STDAFX.o
LIBS = -L../RESGEN $(SDL_LDFLAGS) -lbombermaaan
CXXINCS =  -I./
BIN  = Bombermaaan
CXXFLAGS = $(CXXINCS) $(SDL_CFLAGS) -Wall -O2
ifeq ($(DEBUG),1)
	CXXFLAGS += -g
endif
RM = rm -f
DEPENDFILE = .depend

.PHONY: all all-before all-after clean strip clean-custom

all: all-before $(DEPENDFILE) $(BIN) all-after

$(DEPENDFILE): $(SRC)
	$(CPP) -MM $(SRC) $(CXXFLAGS) > $(DEPENDFILE)

-include $(DEPENDFILE)

clean: clean-custom
	$(RM) $(LINKOBJ) $(BIN) $(DEPENDFILE) *~

install: all
	mkdir -p $(prefix)/bin
	$(INSTALL) $(BIN) $(prefix)/bin

uninstall: all
	$(RM) $(prefix)/bin/$(BIN)

strip: $(BIN)
	$(STRIP) $(BIN)

$(BIN): $(LINKOBJ)
	$(CPP) $(LINKOBJ) -o $(BIN) $(LIBS)

STDAFX.o: STDAFX.CPP
	$(CPP) -c $< -o $@ $(CXXFLAGS)

%.o: %.cpp
	$(CPP) -c $< -o $@ $(CXXFLAGS)

