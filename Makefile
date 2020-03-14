src_dir := src
out_dir := out
exe := output

# compiler flags
flags = -static-libgcc -Wall -Wpedantic -Wextra -O2

# source files
sources = $(src_dir)/*.c $(src_dir)/archive/*.c \
		  $(src_dir)/interface/*.c $(src_dir)/play/*.c \
		  $(src_dir)/render/*.c $(src_dir)/video/*.c \

all: run

clean:
	rm -rf $(out_dir)

build:
	mkdir -p $(out_dir)
	gcc $(sources) $(flags) -I./lib/include -lSDL2 -o $(out_dir)/$(exe)

run:
	$(MAKE) build
	$(out_dir)/$(exe)
