CC = g++
CFLAGS = -std=c++17 -Wall

SRC = main.cpp shell.cpp
EXEC = shelld

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)

clean:
	rm -f $(EXEC)

run: $(EXEC)
	./$(EXEC)

.PHONY: all clean run
