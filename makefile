CC = g++
CFLAGS = -Wall -m32 -ggdb

all:	main.o _cipher.o _decipher.o cfb.o
	$(CC) $(CFLAGS)  main.o _cipher.o _decipher.o cfb.o -o out

_cipher.o:	_cipher.s
	nasm -f elf32 -o _cipher.o _cipher.s

_decipher.o:	_decipher.s
	nasm -f elf32 -o _decipher.o _decipher.s

main.o:	main.cpp cfb.h
	$(CC) $(CFLAGS) -c -o main.o main.cpp

cfb.o:	cfb.cpp cfb.h
	$(CC) $(CFLAGS) -c -o cfb.o cfb.cpp

clean:
	rm -f *.o
