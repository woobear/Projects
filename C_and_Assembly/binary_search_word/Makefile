CC=gcc
PROJECT=ok
O_FILE=ok.o
c_FILE=ok.c
COPTS=-g -Wall -pedantic -std=c99
JUNK=*.o $(PROJECT) $(PROJECT).dSYM

all: $(PROJECT)

clean: 
	rm -rf $(JUNK)

$(PROJECT): $(O_FILE)
	$(CC) $^ $(COPTS) -o $@

.c.o: 
	$(CC) $< $(COPTS) -c
