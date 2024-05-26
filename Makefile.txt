# Compiler settings
CC = gcc
CFLAGS = -std=c11

# Source files
SRC = main.c

# Executable name
EXEC = PROJET

# Default target
all: $(EXEC)

# Compilation
$(EXEC): $(SRC)
    $(CC) $(CFLAGS) $(SRC) -o $(EXEC)

# Clean
clean:
    rm -f $(EXEC)
