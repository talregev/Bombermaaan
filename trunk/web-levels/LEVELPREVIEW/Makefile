LIBPNG_CFLAGS = $(shell pkg-config libpng12 --cflags)
LIBPNG_LDFLAGS = $(shell pkg-config libpng12 --libs)

CPP  = g++
CC   = gcc
HOSTCPP = g++
WINDRES = 
RES  = 
BOMBERMAAAN_SRCDIR = ../Bombermaaan
OBJ  = LevelPreview.o COptions.o winreplace.o
LINKOBJ  = LevelPreview.o COptions.o winreplace.o
LIBS = -L../RESGEN -lbombermaaan
INCS =  -I./ -I$(BOMBERMAAAN_SRCDIR)
CXXINCS =  -I./ -I$(BOMBERMAAAN_SRCDIR)
BIN  = LevelPreview
REVISION = 0.0
CXXFLAGS = $(CXXINCS) -Wall -O2 $(LIBPNG_CFLAGS)
ifeq ($(DEBUG),1)
	CXXFLAGS += -g
endif
LDFLAGS = $(LIBS) $(LIBPNG_LDFLAGS)
INSTALL = install
RM = rm -f
CP = cp

.PHONY: all all-before all-after install clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	$(RM) $(BIN) $(OBJ) *~

install: all
	$(INSTALL) $(BIN) $(prefix)/bin

uninstall: all
	$(RM) $(prefix)/bin/$(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LDFLAGS) -o $(BIN) $(LINKOBJ)

LevelPreview.o: LevelPreview.cpp LevelPreview.h
	$(CPP) -c $< -o $@ $(CXXFLAGS)

COptions.o: COptions.cpp
	$(CPP) -c $< -o $@ $(CXXFLAGS)
	
winreplace.o: $(BOMBERMAAAN_SRCDIR)/winreplace.o
	$(CP) $(BOMBERMAAAN_SRCDIR)/winreplace.o .
