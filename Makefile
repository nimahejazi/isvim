.PHONY: all

all: compile_code

compile_code:
	gcc -o isvim isvim.c

install:
	cp isvim /usr/local/bin

clean:
	rm isvim

uninstall:
	rm /usr/local/bin/isvim
