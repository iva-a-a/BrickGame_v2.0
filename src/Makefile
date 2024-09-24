CPP = g++
CPPFLAGS = -g -Wall -Werror -Wextra -std=c++17
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


GAME_CONSOLE = console
GAME_DESKTOP = desktop
GAME = brickgame
GAME_VERSION = 2.0

ALL_SRC = $(wildcard   */*/*.c */*/*/*.c */*/*.cpp */*/*/*.cpp */*.h */*/*.h */*/*/*.h)

.PHONY: all install uninstall clean dvi dist $(GAME_CONSOLE) $(GAME_DESKTOP)


all: $(GAME_DESKTOP)

$(GAME_CONSOLE): $(OBJECTS_C) $(OBJECTS_CPP) $(LIBRARY_TET) $(LIBRARY_SN)
	mkdir -p build_cli
	$(CPP) $(CFLAGS) -o $@ $^ -lncurses
	mv console ./build_cli

$(GAME_DESKTOP):
	mkdir desk
	cd desk && qmake ../gui/desktop
	cd desk && make
	mkdir -p build_desk
	mv desk/desktop ./build_desk
	rm -rf desk

install: clean all $(GAME_CONSOLE) $(GAME_DESKTOP)
	mkdir $(BINDIR)
	cp build_desk/$(GAME_DESKTOP) $(BINDIR)
	cp build_cli/$(GAME_CONSOLE) $(BINDIR)

uninstall:
	rm -rf $(BINDIR)

dvi:
	doxygen
	xdg-open doxygen/html/index.html

dist:
	mkdir $(GAME)-$(GAME_VERSION)
	cp brick_game gui Makefile $(GAME)-$(GAME_VERSION) -r
	tar -czf $(GAME)-$(GAME_VERSION).tar.gz $(GAME)-$(GAME_VERSION)
	rm -rf $(GAME)-$(GAME_VERSION)

test:

clean:
	rm -f $(GAME) $(LIBDIR_TET)/*.o $(GUIDIR_TET)/*.o  $(GUIDIR)/*.o $(LIBDIR_SN)/*.o  $(GUIDIR_SN)/*.o *.a
	rm -f *.txt *.gz
	rm -rf doxygen
	rm -rf desk
	rm -rf build_cli
	rm -rf build_desk

%.o: %.c
	$(CPP) $(CPPFLAGS) -c -o $@ $<

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c -o $@ $<

$(LIBRARY_TET): $(LIBDIR_TET)/back_tetris.o
	ar rcs $@ $^
	ranlib $@

$(LIBRARY_SN): $(LIBDIR_SN)/controller_snake.o $(LIBDIR_SN)/model_snake.o
	ar rcs $@ $^
	ranlib $@

cppcheck:
	cppcheck --std=c++17 --enable=all --language=c++ --suppress=missingIncludeSystem $(ALL_SRC)

clang:
	cp ./../materials/linters/.clang-format ./
	clang-format -i $(ALL_SRC)
	rm -f .clang-format
