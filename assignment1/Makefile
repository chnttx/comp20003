# Define C compiler and flags
CC = gcc
CFLAGS = -Wall -gcc

# Define libraries to be linked
LDLIBS = 

SRC = 

OBJ = $(SRC:.c=.o)

# Define the executable names
EXE = dict1

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ) $(LDLIBS)

clean: 
	rm -f $(OBJ) $(EXE)