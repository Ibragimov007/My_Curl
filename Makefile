target := my_curl

sources_folder      := ./sources
objects_folder      := ./objects
headers_folder      := ./headers

my_lib_sources_folder := ./sources/my_lib
my_lib_objects_folder := ./objects/my_lib
my_lib_headers_folder := ./headers/my_lib

compiler       := gcc
compiler_flags := -Wall -Wextra -Werror
gdb_flags      := -ggdb -O0
asan_flags     := -g3 -fsanitize=address

sources := $(wildcard $(sources_folder)/*.c)
headers := $(wildcard $(headers_folder)/*.h)
objects := $(patsubst $(sources_folder)/%.c, $(objects_folder)/%.o,\
           $(sources))

my_lib_sources := $(wildcard $(my_lib_sources_folder)/*.c)
my_lib_headers := $(wildcard $(my_lib_headers_folder)/*.h)
my_lib_objects := $(patsubst $(my_lib_sources_folder)/%.c,\
                  $(my_lib_objects_folder)/%.o, $(my_lib_sources))

all: $(target)

$(target): $(objects) $(my_lib_objects)
	$(compiler) $(compiler_flags) -o $(target) $(objects) $(my_lib_objects)

$(objects_folder)/%.o: $(sources_folder)/%.c $(headers_folder)/%.h
	mkdir -p $(objects_folder)
	$(compiler) $(compiler_flags) -c $< -o $@

$(my_lib_objects_folder)/%.o: $(my_lib_sources_folder)/%.c\
                              $(my_lib_headers_folder)/%.h
	mkdir -p $(my_lib_objects_folder)
	$(compiler) $(compiler_flags) -c $< -o $@

clean:
	rm -rf $(objects_folder)/*.o
	rm -rf $(my_lib_objects_folder)/*.o

fclean: clean
	rm -rf $(target) $(objects_folder)

re: fclean all

gdb: gdb_concatenate all

gdb-re: gdb_concatenate re

gdb_concatenate:
	$(eval compiler_flags += $(gdb_flags))

asan: asan_concatenate all

asan-re: asan_concatenate re

asan_concatenate:
	$(eval compiler_flags += $(asan_flags))

.phony: all clean fclean re gdb_concatenate gdb-re gdb\
        asan_concatenate asan-re asan
