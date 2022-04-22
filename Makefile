EXE = SDLApp
LIBS = -lSDL2 -lSDL2_image
DEBUG = FALSE

GCC = gcc
GXX = g++

GCCFLAGS = -Wall -W -marm

ifeq ($(DEBUG),FALSE)
	GCCFLAGS += -Os
else
	GCCFLAGS += -O0 -g
endif

OBJS = $(patsubst %.c, %.o, $(shell find . -name \*.c))
OBJS += $(patsubst %.cpp, %.o, $(shell find . -name \*.cpp))
DISTDIR = .

.PHONY: all
all: $(EXE)

%.o: %.c
	$(GCC) $(GCCFLAGS) -c $< -o $@

%.o: %.cpp
	$(GXX) $(GCCFLAGS) -c $< -o $@

$(EXE): $(OBJS)
	$(GXX) $^ $(LIBS) -o $(DISTDIR)/$@

.PHONY: clean
clean:
	rm -f $(OBJS) $(DISTDIR)/$(EXE)