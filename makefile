CC = g++
CFLAGS = -std=c++17 -Wall -I/opt/homebrew/opt/ncurses/include
LDFLAGS = -L/opt/homebrew/opt/ncurses/lib -lncurses

SRC = main.cpp shell.cpp
EXEC = shelld

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(EXEC)

clean:
	rm -f $(EXEC)

run: $(EXEC)
	./$(EXEC)

.PHONY: all clean run
