#include "terminal.h"

#include <cstdio>
#include <ncurses.h>

namespace terminal {

void init() {
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(1);
    setCursorBlock();
}

void shutdown() {
    setCursorBlock();
    endwin();
}

void setCursorBlock() {
    std::fputs("\x1b[2 q", stdout);
    std::fflush(stdout);
}

void setCursorBar() {
    std::fputs("\x1b[6 q", stdout);
    std::fflush(stdout);
}

}
