SYMFORMAT=dwarf
FORMAT=elf
DESTINATION=/encs_share/cs/class/cs261/asm2

strgt: strgt.o string.o
	gcc  string.c strgt.o -m32 -o string

strgt.o: strgt.asm
	nasm -f $(FORMAT) -g -F $(SYMFORMAT) strgt.asm

install: strgt
	cp strgt.asm strgt Makefile $(DESTINATION)

