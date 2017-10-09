SYMFORMAT=dwarf
FORMAT=elf
DESTINATION=/encs_share/cs/class/cs261/asm2

mystery: mystery.o
	gcc -m32 -nostartfiles -g -o mystery mystery.o

mystery.o: mystery.asm
	nasm -f $(FORMAT) -g -F $(SYMFORMAT) mystery.asm

install: mystery
	cp mystery.asm mystery Makefile $(DESTINATION)

