program_name = matrix
tests_name = tests

tests_h = tests.h

tests_obj = tests.o
main_obj = main.o
matrix_obj = matrix.o

tests_cpp = tests.cpp
main_cpp = main_p.cpp
matrix_cpp = matrix.cpp


CFLAGS = -O2 -c -g -ftrapv  -Wall -Werror -Wformat-security -Wignored-qualifiers\
		 -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body\
		 -Wlogical-op -Wmissing-field-initializers -Wcast-qual -Wwrite-strings
COMPILER = g++

all: $(program_name)

$(program_name): $(main_obj) $(matrix_obj)
	$(COMPILER)  $(main_obj) $(matrix_obj) -o $(program_name) -fsanitize=undefined -lm

$(matrix_obj): $(matrix_cpp)
	$(COMPILER) $(CFLAGS) $(matrix_cpp) -o $(matrix_obj)

$(main_obj): $(main_cpp)
	$(COMPILER) $(CFLAGS) $(main_cpp) -o $(main_obj)

clean:
	rm -rf *.o $(program)
	rm $(program_name)

$(tests_obj): $(tests_cpp)
	$(COMPILER) $(CFLAGS) $(tests_cpp) -o $(tests_obj)
$(tests_cpp): $(tests_h)
	cxxtestgen --error-printer -o $(tests_cpp) $(tests_h)
build_tests: $(tests_obj) $(matrix_obj)
	$(COMPILER) $(tests_obj) $(matrix_obj) -o $(tests_name) -fsanitize=undefined -lm

clean_tests:
	rm $(tests_name)
	rm $(tests_cpp)
	rm $(tests_obj)
