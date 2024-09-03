CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
LDLIBS = 

LIBDIR=brick_game/tetris
GUIDIR=gui/cli

BINDIR = ./bin

LIBRARY = back.a


SOURCES = $(wildcard $(LIBDIR)/*.c) $(wildcard $(GUIDIR)/*.c)
HEADERS = $(wildcard $(LIBDIR)/*.h) $(wildcard $(GUIDIR)/*.h)
OBJECTS = $(SOURCES:.c=.o)
GAME = tetris
GAME_VERSION = 1.0

TEST_DIR = test
TEST_SOURCES := $(wildcard $(TEST_DIR)/*test*.c)
TEST_FUNC_OBJECTS := $(patsubst %.c,%.o,$(TEST_SOURCES))
TEST_SUITE_SOURCES = $(wildcard $(TEST_DIR)/*_suite.c)
TEST_SUITE_OBJECTS = $(patsubst %.c,%.o,$(TEST_SUITE_SOURCES))
TEST_EXECUTABLES = $(patsubst %.c,%,$(TEST_SUITE_SOURCES))



ALL_SRC = $(wildcard *.c */*.c */*/*.c *.h */*.h */*/*.h)

.PHONY: all $(GAME) $(LIBRARY) install uninstall clean dvi dist test gcov_report clang valgrind cppcheck

all: $(GAME)

$(LIBRARY): $(LIBDIR)/function.o
	ar rcs $@ $^
	ranlib $@

$(GAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ -lncurses

install: clean all
	mkdir $(BINDIR)
	cp $(GAME) $(BINDIR)

uninstall:
	rm -rf $(BINDIR)

clean:
	rm -f $(GAME) $(TEST_SUITE_OBJECTS) $(TEST_EXECUTABLES) $(LIBDIR)/*.o $(GUIDIR)/*.o $(TEST_DIR)/*.o *.a *.gz
	rm -f *.gcno *.gcda *.gcov **/*.gcno **/*.gcda **/**/*.gcno **/**/*.gcda **/**/*.gcov coverage.info -r coverage_report
	rm -f *.txt
	rm -rf doxygen

dvi:
	doxygen

dist: $(SOURCES) $(HEADERS) Makefile
	mkdir $(GAME)-$(GAME_VERSION)
	cp brick_game gui Makefile $(GAME)-$(GAME_VERSION) -r
	tar -czf $(GAME)-$(GAME_VERSION).tar.gz $(GAME)-$(GAME_VERSION)
	rm -rf $(GAME)-$(GAME_VERSION)

$(TEST_DIR)/%.o: LDLIBS = -lcheck -lm -lsubunit -lrt -lpthread
$(TEST_DIR)/%.o: $(TEST_DIR)/%.c $(LIBRARY)
	$(CC) $(CFLAGS) $(LDLIBS) -c -o $@ $< -L. -l:$(LIBRARY)

$(TEST_EXECUTABLES): LDLIBS = -lcheck -lm -lsubunit -lrt -lpthread
$(TEST_EXECUTABLES): %: %.o $(LIBRARY) $(TEST_FUNC_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $< $(TEST_FUNC_OBJECTS) $(LDLIBS) -L. -l:$(LIBRARY)

test: clean $(LIBRARY) $(TEST_EXECUTABLES) 
#перенесла тесты на тетрис в папку tetris_test
	for test in $(TEST_EXECUTABLES); do ./$$test; done

gcov_report: CFLAGS += -coverage
gcov_report: clean test
	gcov $(SOURCES)
	mkdir coverage_report
	lcov --directory . --capture --output-file coverage.info
	genhtml coverage.info --output-directory coverage_report

clang:
	cp ./../materials/linters/.clang-format ./
	clang-format -i $(ALL_SRC)
	rm -f .clang-format

valgrind: CFLAGS += -DVALGRIND
valgrind: clean $(GAME) $(TEST_EXECUTABLES)
	for test in $(TEST_EXECUTABLES); do CK_FORK=no valgrind --tool=memcheck --leak-check=yes ./$$test; done

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem $(ALL_SRC)