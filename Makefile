SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
BIN_DIR = .

EXE = $(BIN_DIR)/out
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = gcc
CPPFLAGS 	= -I$(INC_DIR) -MMD -MP
CFLAGS 		= -Wall 
LDLIBS	 	= -lSDL2
LDFLAGS		=

.PHONY: clean all

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) -c $< -o $@

-include $(OBJ:.o=.d)
