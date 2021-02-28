program_name = complex

main_obj = main.o
matrix_obj = complex.o

main_cpp = main.cpp
matrix_cpp = complex.cpp


CFLAGS = -O2 -g -c -ftrapv   -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal \
         -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wmissing-field-initializers  -Wcast-qual -Wwrite-strings 
COMPILER = g++

all: $(program_name)

$(program_name): $(main_obj) $(matrix_obj)
	$(COMPILER) $(main_obj) $(matrix_obj) -o $(program_name) -lm

$(matrix_obj): $(matrix_cpp)
	$(COMPILER) $(CFLAGS) $(matrix_cpp) -o $(matrix_obj)

$(main_obj): $(main_c)
	$(COMPILER) $(CFLAGS) $(main_cpp) -o $(main_obj)

clean:
	rm -rf *.o $(program)
