CPP  = g++
CC   = gcc
HOSTCPP = g++
WINDRES = 
RES  = 
OBJ  = ResData.o
LINKOBJ  = ResData.o
LIBS = 
INCS =  -I./ -I../Bombermaaan
CXXINCS =  -I./ -I../Bombermaaan
BASENAME = libbombermaaan.so
BIN  = $(BASENAME).1
REVISION = 0.0
CXXFLAGS = $(CXXINCS) -fPIC -Wall -O2
LDFLAGS = -shared -Wl,-soname,$(BIN) -lc
RESGENBIN = ./ResGen
#RESGEN1632 = --sprite
#RESGENDIR = --bin
RES32DIR = ../RES32
RES16DIR = ../RES
INSTALL = install
RM = rm -f
SYMLINK = ln -sf

.PHONY: all all-before all-after install clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	$(RM) $(BIN) $(OBJ) $(RESGENBIN) ResData.c $(BIN) $(BASENAME) $(BIN).$(REVISION)

install: all
	$(INSTALL) $(BIN) $(BIN).$(REVISION) $(prefix)/lib

uninstall: all
	$(RM) $(prefix)/lib/$(BIN) $(prefix)/lib/$(BIN).$(REVISION)

$(BIN): $(OBJ)
	$(CC) $(LDFLAGS) -o $(BIN).$(REVISION) $(LINKOBJ) $(LIBS)
	$(SYMLINK) $(BIN).$(REVISION) $(BIN)
	$(SYMLINK) $(BIN).$(REVISION) $(BASENAME)

ResData.o: ResData.c
	$(CC) -c ResData.c -o ResData.o $(CXXFLAGS)

ResData.c: $(RESGENBIN)
	$(RESGENBIN)

ResGen: ResGen.cpp
	$(HOSTCPP) -o ResGen ResGen.cpp $(CXXFLAGS)

