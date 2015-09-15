CC = gcc
LD = ld
OBJ = emma_helper.o memtable.o api.o
LDFLAGS = -shared
CFLAGS = -std=c11 -DEMMA_LIB_EXPORT -Wall -Werror -pedantic-errors

ifeq ($(OS),Windows_NT)
  NAME = emma.dll
  EXEC_TEST = cp test/emma_test.exe . && ./emma_test.exe
else
  NAME = libemma.so
  EXEC_TEST = cp test/emma_test . && ./emma_test
endif

.PHONY: clean

release: $(OBJ)
	$(CC) $(LDFLAGS) $(CFLAGS) -Ofast -o $(NAME) $(OBJ)
	
debug: $(OBJ)
	$(CC) $(LDFLAGS) -g -Og -o $(NAME) $(OBJ)
	
emma_helper.o: emma_helper.h
	$(CC) $(CFLAGS) -c emma_helper.c
	
memtable.o: memtable.c
	$(CC) $(CFLAGS) -c memtable.c

api.o: api.c
	$(CC) $(CFLAGS) -c api.c
	
test: release
	$(MAKE) -C test
	$(EXEC_TEST)
	
testdbg: debug
	$(MAKE) -C test
	$(EXEC_TEST)
	
clean: 
	$(MAKE) -C test clean
	$(RM) *.o $(NAME) emma_test.*