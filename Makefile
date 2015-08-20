CC = gcc
LD = ld
OBJ = emma_helper.o memtable.o
LDFLAGS = -shared
CFLAGS = -std=c11 -DEMMA_LIB_EXPORT -Wall -Werror -pedantic-errors

ifeq ($(OS),Windows_NT)
  NAME = emma.dll
else
  NAME = libemma.so
endif

.PHONY: clean

release: $(OBJ)
	$(CC) $(LDFLAGS) -Ofast -o $(NAME) $(OBJ)
	
debug: $(OBJ)
	$(CC) $(LDFLAGS) -Og -o $(NAME) $(OBJ)
	
emma_helper.o: emma_helper.h
	$(CC) $(CFLAGS) -c emma_helper.c
	
memtable.o: memtable.c
	$(CC) $(CFLAGS) -c memtable.c
	
clean: 
	$(RM) *.o $(NAME)