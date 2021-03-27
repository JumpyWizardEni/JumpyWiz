program_name = graph
tests_name = tests

tests_h = tests.h

tests_obj = tests.o
main_obj = main.o
dense_obj = dense.o
iterator_obj = iterator.o

tests_cpp = tests.cpp
main_cpp = main_p.cpp
dense_cpp = dense.cpp
iterator_cpp = iterator.cpp

CFLAGS = -O2 -c -g -ftrapv  -Wall -Werror -Wformat-security -Wignored-qualifiers\
		 -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body\
		 -Wlogical-op -Wmissing-field-initializers -Wcast-qual -Wwrite-strings
COMPILER = g++

all: $(program_name)

$(program_name): $(main_obj) $(matrix_obj)
	$(COMPILER)  $(main_obj) $(matrix_obj) -o $(program_name) -fsanitize=undefined -lm

$(dense_obj): $(dense_cpp)
	$(COMPILER) $(CFLAGS) $(dense_cpp) -o $(dense_obj) 

$(main_obj): $(main_cpp)
	$(COMPILER) $(CFLAGS) $(main_cpp) -o $(main_obj)

clean:
	rm -rf *.o $(program)
	rm $(program_name)

$(iterator_obj): $(iterator_cpp)
	$(COMPILER) $(CFLAGS) -o $@ $^

$(tests_obj): $(tests_cpp)
	$(COMPILER) $(CFLAGS) -o $@ $^ 

$(tests_cpp): $(tests_h)
	cxxtestgen --error-printer -o $@ $^

build_tests: $(dense_obj) $(tests_obj) $(iterator_obj)
	$(COMPILER) $^ -o $(tests_name) -fsanitize=undefined -lm

clean_tests:
	rm -rf *.o $(tests_name)
	rm $(tests_name)
	rm $(tests_cpp)