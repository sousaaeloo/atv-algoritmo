CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -Werror -pedantic
all: testes
testes: atm.c testes.c atm.h
	$(CC) $(CFLAGS) atm.c testes.c -o testes
test: testes
	./testes
clean:
	rm -f testes
.PHONY: all test clean
