CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11
# CHECK_FLAGS = $(shell pkg-config --cflags --libs check)
# GCOV_FLAGS = -fprofile-arcs -ftest-coverage -lgcov --coverage

test_flags=-fprofile-arcs -ftest-coverage
OS=$(shell uname -s)

ifeq ($(OS),Linux)
	test_libs=-lcheck -lm -lsubunit
	open=xdg-open
else
	test_libs=-lcheck
	open=open
endif

all: s21_string.a test gcov_report

clang:
	clang-format -i */*.c */*.h

rebuild: clean all

test: string/*.c __test__/*.c sprintf/*.c shared/*.c
	$(CC) $(CFLAGS) $(test_flags) string/*.c shared/*.c sprintf/*.c __test__/*.c -o test $(test_libs)
	./test

s21_string.a:
	$(CC) $(CFLAGS) -c string/string.c -o string.o
	$(CC) $(CFLAGS) -c shared/utils.c -o utils.o
	$(CC) $(CFLAGS) -c shared/str_format_parser.c -o str_format_parser.o
	$(CC) $(CFLAGS) -c sprintf/sprintf.c -o sprintf.o
	$(CC) $(CFLAGS) -c sprintf/sprintf_strategy.c -o sprintf_strategy.o
	ar rcs $@ *.o

gcov_report:
	lcov -t "test" -o $(tests_info)test.info -c -d .
	genhtml -o report $(tests_info)test.info
	$(open) report/index.html

clean:
	rm -fr *.o *.a test test.dSYM/ *.gcda *.gcno report/ test.info *.html valgrind.txt

valgrind: clean test
	CK_FORK=no valgrind --log-file="valgrind.txt" --track-origins=yes --trace-children=yes --leak-check=full --leak-resolution=med ./test
