# Project: Bombermaaan
# Makefile created by Dev-C++ 4.9.9.2

SDL_CONFIG := sdl-config

SDL_CFLAGS := $(shell $(SDL_CONFIG) --cflags)
SDL_LDFLAGS := $(shell $(SDL_CONFIG) --libs) -lSDL_mixer

CPP  = g++
CC   = gcc
WINDRES = 
RES  = 
OBJ  = CBoard.o CClock.o CCloudManager.o CCommandChunk.o CControls.o CDemo.o CDrawGame.o CHurryMessage.o CMatch.o CMenu.o CMenuBase.o CMenuBomber.o CMenuInput.o CMenuLevel.o CMenuMatch.o CMenuYesNo.o CModeScreen.o CMosaic.o CPauseMessage.o CRandomMosaic.o CScroller.o CTitle.o CVictory.o CWinner.o CConsole.o CSDLVideo.o CSDLInput.o CLog.o CWindow.o CDebug.o CDisplay.o CFont.o CGame.o CInput.o CMainInput.o COptions.o CPlayerInput.o CScores.o CSound.o CArena.o CArenaCloser.o CArenaSnapshot.o CBomb.o CBomber.o CBomberMove.o CElement.o CExplosion.o CFloor.o CItem.o CWall.o CAiArena.o CAiBomber.o CAiManager.o STDAFX.o WinMain.o winreplace.o
LINKOBJ  = CBoard.o CClock.o CCloudManager.o CCommandChunk.o CControls.o CDemo.o CDrawGame.o CHurryMessage.o CMatch.o CMenu.o CMenuBase.o CMenuBomber.o CMenuInput.o CMenuLevel.o CMenuMatch.o CMenuYesNo.o CModeScreen.o CMosaic.o CPauseMessage.o CRandomMosaic.o CScroller.o CTitle.o CVictory.o CWinner.o CConsole.o CSDLVideo.o CSDLInput.o CLog.o CWindow.o CDebug.o CDisplay.o CFont.o CGame.o CInput.o CMainInput.o COptions.o CPlayerInput.o CScores.o CSound.o CArena.o CArenaCloser.o CArenaSnapshot.o CBomb.o CBomber.o CBomberMove.o CElement.o CExplosion.o CFloor.o CItem.o CWall.o CAiArena.o CAiBomber.o CAiManager.o STDAFX.o WinMain.o winreplace.o
LIBS = -L../RESGEN $(SDL_LDFLAGS) -lbombermaaan
INCS =  -I./
CXXINCS =  -I./
BIN  = Bombermaaan
CXXFLAGS = $(CXXINCS) $(SDL_CFLAGS) -Wall -O2
ifeq ($(DEBUG),1)
	CXXFLAGS += -g
endif
RM = rm -f

.PHONY: all all-before all-after clean strip clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	$(RM) $(OBJ) $(BIN) *~

install: all
	mkdir -p $(prefix)/bin
	$(INSTALL) $(BIN) $(prefix)/bin

uninstall: all
	$(RM) $(prefix)/bin/$(BIN)

strip: $(BIN)
	$(STRIP) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o $(BIN) $(LIBS)

CBoard.o: CBoard.cpp
	$(CPP) -c CBoard.cpp -o CBoard.o $(CXXFLAGS)

CClock.o: CClock.cpp
	$(CPP) -c CClock.cpp -o CClock.o $(CXXFLAGS)

CCloudManager.o: CCloudManager.cpp
	$(CPP) -c CCloudManager.cpp -o CCloudManager.o $(CXXFLAGS)

CCommandChunk.o: CCommandChunk.cpp
	$(CPP) -c CCommandChunk.cpp -o CCommandChunk.o $(CXXFLAGS)

CControls.o: CControls.cpp
	$(CPP) -c CControls.cpp -o CControls.o $(CXXFLAGS)

CDemo.o: CDemo.cpp
	$(CPP) -c CDemo.cpp -o CDemo.o $(CXXFLAGS)

CDrawGame.o: CDrawGame.cpp
	$(CPP) -c CDrawGame.cpp -o CDrawGame.o $(CXXFLAGS)

CHurryMessage.o: CHurryMessage.cpp
	$(CPP) -c CHurryMessage.cpp -o CHurryMessage.o $(CXXFLAGS)

CMatch.o: CMatch.cpp
	$(CPP) -c CMatch.cpp -o CMatch.o $(CXXFLAGS)

CMenu.o: CMenu.cpp
	$(CPP) -c CMenu.cpp -o CMenu.o $(CXXFLAGS)

CMenuBase.o: CMenuBase.cpp
	$(CPP) -c CMenuBase.cpp -o CMenuBase.o $(CXXFLAGS)

CMenuBomber.o: CMenuBomber.cpp
	$(CPP) -c CMenuBomber.cpp -o CMenuBomber.o $(CXXFLAGS)

CMenuInput.o: CMenuInput.cpp
	$(CPP) -c CMenuInput.cpp -o CMenuInput.o $(CXXFLAGS)

CMenuLevel.o: CMenuLevel.cpp
	$(CPP) -c CMenuLevel.cpp -o CMenuLevel.o $(CXXFLAGS)

CMenuMatch.o: CMenuMatch.cpp
	$(CPP) -c CMenuMatch.cpp -o CMenuMatch.o $(CXXFLAGS)

CMenuYesNo.o: CMenuYesNo.cpp
	$(CPP) -c CMenuYesNo.cpp -o CMenuYesNo.o $(CXXFLAGS)

CModeScreen.o: CModeScreen.cpp
	$(CPP) -c CModeScreen.cpp -o CModeScreen.o $(CXXFLAGS)

CMosaic.o: CMosaic.cpp
	$(CPP) -c CMosaic.cpp -o CMosaic.o $(CXXFLAGS)

CPauseMessage.o: CPauseMessage.cpp
	$(CPP) -c CPauseMessage.cpp -o CPauseMessage.o $(CXXFLAGS)

CRandomMosaic.o: CRandomMosaic.cpp
	$(CPP) -c CRandomMosaic.cpp -o CRandomMosaic.o $(CXXFLAGS)

CScroller.o: CScroller.cpp
	$(CPP) -c CScroller.cpp -o CScroller.o $(CXXFLAGS)

CTitle.o: CTitle.cpp
	$(CPP) -c CTitle.cpp -o CTitle.o $(CXXFLAGS)

CVictory.o: CVictory.cpp
	$(CPP) -c CVictory.cpp -o CVictory.o $(CXXFLAGS)

CWinner.o: CWinner.cpp
	$(CPP) -c CWinner.cpp -o CWinner.o $(CXXFLAGS)

CConsole.o: CConsole.cpp
	$(CPP) -c CConsole.cpp -o CConsole.o $(CXXFLAGS)

CSDLVideo.o: CSDLVideo.cpp
	$(CPP) -c CSDLVideo.cpp -o CSDLVideo.o $(CXXFLAGS)

CSDLInput.o: CSDLInput.cpp
	$(CPP) -c CSDLInput.cpp -o CSDLInput.o $(CXXFLAGS)

CLog.o: CLog.cpp
	$(CPP) -c CLog.cpp -o CLog.o $(CXXFLAGS)

CWindow.o: CWindow.cpp
	$(CPP) -c CWindow.cpp -o CWindow.o $(CXXFLAGS)

CDebug.o: CDebug.cpp
	$(CPP) -c CDebug.cpp -o CDebug.o $(CXXFLAGS)

CDisplay.o: CDisplay.cpp
	$(CPP) -c CDisplay.cpp -o CDisplay.o $(CXXFLAGS)

CFont.o: CFont.cpp
	$(CPP) -c CFont.cpp -o CFont.o $(CXXFLAGS)

CGame.o: CGame.cpp
	$(CPP) -c CGame.cpp -o CGame.o $(CXXFLAGS)

CInput.o: CInput.cpp
	$(CPP) -c CInput.cpp -o CInput.o $(CXXFLAGS)

CMainInput.o: CMainInput.cpp
	$(CPP) -c CMainInput.cpp -o CMainInput.o $(CXXFLAGS)

COptions.o: COptions.cpp
	$(CPP) -c COptions.cpp -o COptions.o $(CXXFLAGS)

CPlayerInput.o: CPlayerInput.cpp
	$(CPP) -c CPlayerInput.cpp -o CPlayerInput.o $(CXXFLAGS)

CScores.o: CScores.cpp
	$(CPP) -c CScores.cpp -o CScores.o $(CXXFLAGS)

CSound.o: CSound.cpp
	$(CPP) -c CSound.cpp -o CSound.o $(CXXFLAGS)

CArena.o: CArena.cpp
	$(CPP) -c CArena.cpp -o CArena.o $(CXXFLAGS)

CArenaCloser.o: CArenaCloser.cpp
	$(CPP) -c CArenaCloser.cpp -o CArenaCloser.o $(CXXFLAGS)

CArenaSnapshot.o: CArenaSnapshot.cpp
	$(CPP) -c CArenaSnapshot.cpp -o CArenaSnapshot.o $(CXXFLAGS)

CBomb.o: CBomb.cpp
	$(CPP) -c CBomb.cpp -o CBomb.o $(CXXFLAGS)

CBomber.o: CBomber.cpp
	$(CPP) -c CBomber.cpp -o CBomber.o $(CXXFLAGS)

CBomberMove.o: CBomberMove.cpp
	$(CPP) -c CBomberMove.cpp -o CBomberMove.o $(CXXFLAGS)

CElement.o: CElement.cpp
	$(CPP) -c CElement.cpp -o CElement.o $(CXXFLAGS)

CExplosion.o: CExplosion.cpp
	$(CPP) -c CExplosion.cpp -o CExplosion.o $(CXXFLAGS)

CFloor.o: CFloor.cpp
	$(CPP) -c CFloor.cpp -o CFloor.o $(CXXFLAGS)

CItem.o: CItem.cpp
	$(CPP) -c CItem.cpp -o CItem.o $(CXXFLAGS)

CWall.o: CWall.cpp
	$(CPP) -c CWall.cpp -o CWall.o $(CXXFLAGS)

CAiArena.o: CAiArena.cpp
	$(CPP) -c CAiArena.cpp -o CAiArena.o $(CXXFLAGS)

CAiBomber.o: CAiBomber.cpp
	$(CPP) -c CAiBomber.cpp -o CAiBomber.o $(CXXFLAGS)

CAiManager.o: CAiManager.cpp
	$(CPP) -c CAiManager.cpp -o CAiManager.o $(CXXFLAGS)

STDAFX.o: STDAFX.CPP
	$(CPP) -c STDAFX.CPP -o STDAFX.o $(CXXFLAGS)

WinMain.o: WinMain.cpp
	$(CPP) -c WinMain.cpp -o WinMain.o $(CXXFLAGS)
