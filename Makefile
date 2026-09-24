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
	install -Dm755 $(BIN) $(DESTDIR)$(PREFIX)/bin/$(BIN)
	install -Dm644 assets/$(BIN).desktop $(DESTDIR)$(PREFIX)/share/applications/$(BIN).desktop
	-update-desktop-database $(DESTDIR)$(PREFIX)/share/applications 2>/dev/null

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/$(BIN)
	rm -f $(DESTDIR)$(PREFIX)/share/applications/$(BIN).desktop
	-update-desktop-database $(DESTDIR)$(PREFIX)/share/applications 2>/dev/null

.PHONY: all clean install uninstall
