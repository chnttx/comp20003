# Define C compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Define libraries to be linked
LDLIBS = 

SRC = driver.c lists.c data.c

OBJ = $(SRC:.c=.o)

# Define the executable names
EXE = dict1

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ) $(LDLIBS)

clean: 
	rm -f $(OBJ) $(EXE)