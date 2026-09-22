BIN = ste
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)

PREFIX = /usr/local

all: $(BIN)

$(BIN): $(OBJ)
	g++ $(OBJ) -o $(BIN) -lncurses

src/%.o: src/%.cpp
	g++ -std=c++17 -Wall -Wextra -O2 -I. -Iinclude -c $< -o $@

clean:
	rm -f $(OBJ) $(BIN)

install: $(BIN)
	install -Dm755 $(BIN) $(PREFIX)/bin/$(BIN)

uninstall:
	rm -f $(PREFIX)/bin/$(BIN)

.PHONY: all clean install uninstall
