CC = gcc
CFLAGS = -Wall -Wextra -I$(INC)
SRC = src
OBJ = obj
BIN = bin
INC = include
OBJECTS = $(OBJ)/main.o $(OBJ)/read.o $(OBJ)/random.o $(OBJ)/range.o $(OBJ)/geneticAlgorithm.o $(OBJ)/sat.o
NAME = maxsat

all: release

release: CFLAGS += -s -O3
release: main

debug: CFLAGS += -g
debug: main

main: $(OBJ) $(BIN) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $(BIN)/$(NAME)

$(OBJ):
	mkdir $(OBJ)
$(BIN):
	mkdir $(BIN)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm -f $(OBJ)/*.o
	rm -f $(BIN)/$(NAME)
