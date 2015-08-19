CC = gcc
LD = ld
OBJ = emma_helper.o memtable.o
LDFLAGS = -shared
CCFLAGS = -std=c11 -DEMMA_LIB_EXPORT

ifeq ($(OS),Windows_NT)
  EXT = dll
else
  EXT = so
endif

all: $(OBJ)
	$(CC) $(LDFLAGS) -o emma.$(EXT) $(OBJ)
	
emma_helper.o: emma_helper.c
	$(CC) $(CCFLAGS) -c emma_helper.c
	
memtable.o: memtable.c
	$(CC) $(CCFLAGS) -c memtable.c
	
clean: 
	rm *.o emma.$(EXT)