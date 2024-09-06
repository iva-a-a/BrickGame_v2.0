CPP = g++
CPPFLAGS = -Wall -Werror -Wextra -std=c++17
#TESTFLAGS = -lgtest -lsubunit -pthread
LDLIBS = 

LIBDIR_TET =brick_game/tetris
LIBDIR_SN = brick_game/snake

GUIDIR_TET =gui/cli/cli_tetris
GUIDIR_SN =gui/cli/cli_snake

GUIDIR = gui/cli

BINDIR = ./bin

LIBRARY_TET = tetris.a
LIBRARY_SN = snake.a

SOURCES_C = $(wildcard $(LIBDIR_TET)/*.c) $(wildcard $(GUIDIR_TET)/*.c) $(wildcard $(GUIDIR)/*.c)
SOURCES_CPP = $(wildcard $(LIBDIR_SN)/*.cpp) $(wildcard $(GUIDIR_SN)/*.cpp) $(wildcard $(GUIDIR)/*.cpp)


OBJECTS_C = $(SOURCES_C:.c=.o)
OBJECTS_CPP =  $(SOURCES_CPP:.cpp=.o)

GAME = brickgame
GAME_VERSION = 2.0

ALL_SRC = $(wildcard   */*/*.c */*/*/*.c */*/*.cpp */*/*/*.cpp */*.h */*/*.h */*/*/*.h)

.PHONY: all $(GAME) $(LIBRARY_TET) $(LIBRARY_SN) clean

%.o: %.c
	$(CPP) $(CPPFLAGS) -c -o $@ $<

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c -o $@ $<

all: $(GAME)

$(GAME): $(OBJECTS_C) $(OBJECTS_CPP) $(LIBRARY_TET) $(LIBRARY_SN)
	$(CPP) $(CFLAGS) -o $@ $^ -lncurses

$(LIBRARY_TET): $(LIBDIR_TET)/back_tetris.o
	ar rcs $@ $^
	ranlib $@

$(LIBRARY_SN): $(LIBDIR_SN)/back_snake.o
	ar rcs $@ $^
	ranlib $@

clean:
	rm -f $(GAME) $(LIBDIR_TET)/*.o $(GUIDIR_TET)/*.o  $(GUIDIR)/*.o $(LIBDIR_SN)/*.o  $(GUIDIR_SN)/*.o *.a
	rm -f *.txt *.gz
	rm -rf doxygen
