CC = gcc
LD = ld
OBJ = main.o
CFLAGS = -g -std=c11 -I.. -L.. -lemma -Wall -Werror -pedantic-errors
OBJ = main.o

ifeq ($(OS),Windows_NT)
  NAME = emma_test.exe
else
  NAME = emma_test
endif


.PHONY: clean
	
	
emma_test: $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	
main.o: main.c
	$(CC) $(CFLAGS) -c main.c
	
clean:
	$(RM) *.o $(NAME)