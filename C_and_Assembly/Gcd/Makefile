sysformat=dwarf
format=elf

gcd: gcd.o 
	gcc -m32 -nostartfiles -g -o gcd gcd.o 

gcd.o: gcd.asm
	nasm -f $(format) -g -F $(sysformat) gcd.asm

