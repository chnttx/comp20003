CC = gcc
CFLAGS = -Wall -g 

LDLIBS = 

SRC = dict2.c data.c array.c
OBJ = $(SRC:.c=.o)

EXE = dict2

$(EXE): $(OBJ) 
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ) $(LDLIBS)

clean:
	rm -f $(OBJ) $(EXE)