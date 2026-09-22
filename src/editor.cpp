#include "editor.h"
#include "terminal.h"
#include "../config.h"

#include <ncurses.h>
#include <string>

Editor::Editor(const std::string& path)
    : filename(path),
      mode(Mode::General),
      cursorRow(0),
      cursorCol(0),
      rowOffset(0),
      colOffset(0),
      running(true),
      modified(false) {
    buffer.load(path);
}

void Editor::run() {
    terminal::init();

    while (running) {
        render();
        int ch = getch();

        if (mode == Mode::General) {
            handleGeneral(ch);
        } else {
            handleWrite(ch);
        }
    }

    terminal::shutdown();
}

void Editor::enterWrite() {
    mode = Mode::Write;
    terminal::setCursorBar();
}

void Editor::enterGeneral() {
    mode = Mode::General;
    terminal::setCursorBlock();
}

void Editor::saveFile() {
    buffer.save(filename);
    modified = false;
}

void Editor::handleGeneral(int ch) {
    switch (ch) {
        case KEY_UP:
            moveCursor(-1, 0);
            break;
        case KEY_DOWN:
            moveCursor(1, 0);
            break;
        case KEY_LEFT:
            moveCursor(0, -1);
            break;
        case KEY_RIGHT:
            moveCursor(0, 1);
            break;
        default:
            break;
    }

    if (ch == quit) {
        running = false;
    } else if (ch == writeMode) {
        enterWrite();
    } else if (ch == save) {
        saveFile();
    }
}

void Editor::handleWrite(int ch) {
    if (ch == escape) {
        enterGeneral();
        return;
    }

    switch (ch) {
        case KEY_UP:
            moveCursor(-1, 0);
            return;
        case KEY_DOWN:
            moveCursor(1, 0);
            return;
        case KEY_LEFT:
            moveCursor(0, -1);
            return;
        case KEY_RIGHT:
            moveCursor(0, 1);
            return;
        default:
            break;
    }

    if (ch == KEY_BACKSPACE || ch == 127 || ch == 8) {
        if (cursorCol > 0) {
            buffer.deleteChar(cursorRow, cursorCol);
            cursorCol -= 1;
        } else if (cursorRow > 0) {
            int previousLength = buffer.lineLength(cursorRow - 1);
            buffer.deleteNewline(cursorRow);
            cursorRow -= 1;
            cursorCol = previousLength;
        }
        modified = true;
        return;
    }

    if (ch == '\n' || ch == KEY_ENTER || ch == 13) {
        buffer.insertNewline(cursorRow, cursorCol);
        cursorRow += 1;
        cursorCol = 0;
        modified = true;
        return;
    }

    if (ch == '\t') {
        buffer.insertTab(cursorRow, cursorCol, tab);
        cursorCol += tab;
        modified = true;
        return;
    }

    if (ch >= 32 && ch < 127) {
        buffer.insertChar(cursorRow, cursorCol, static_cast<char>(ch));
        cursorCol += 1;
        modified = true;
    }
}

void Editor::moveCursor(int deltaRow, int deltaCol) {
    cursorRow += deltaRow;
    cursorCol += deltaCol;
    clampCursor();
}

void Editor::clampCursor() {
    if (cursorRow < 0) {
        cursorRow = 0;
    }
    if (cursorRow >= buffer.lineCount()) {
        cursorRow = buffer.lineCount() - 1;
    }

    int length = buffer.lineLength(cursorRow);
    if (cursorCol < 0) {
        cursorCol = 0;
    }
    if (cursorCol > length) {
        cursorCol = length;
    }
}

int Editor::gutterWidth() const {
    if (!lines) {
        return 0;
    }
    int digits = static_cast<int>(std::to_string(buffer.lineCount()).size());
    if (digits < 2) {
        digits = 2;
    }
    return digits + 1;
}

void Editor::adjustViewport(int screenRows, int screenCols) {
    if (cursorRow < rowOffset) {
        rowOffset = cursorRow;
    }
    if (cursorRow >= rowOffset + screenRows) {
        rowOffset = cursorRow - screenRows + 1;
    }
    if (cursorCol < colOffset) {
        colOffset = cursorCol;
    }
    if (cursorCol >= colOffset + screenCols) {
        colOffset = cursorCol - screenCols + 1;
    }
}

void Editor::renderStatus(int screenRows, int screenCols) {
    std::string modeLabel = (mode == Mode::General) ? "GENERAL" : "WRITE";
    std::string dirty = modified ? "[modified]" : "";
    std::string status = modeLabel + " | " + filename + " " + dirty +
                          " | " + std::to_string(cursorRow + 1) + ":" +
                          std::to_string(cursorCol + 1);

    if (static_cast<int>(status.size()) > screenCols) {
        status.resize(screenCols);
    }

    attron(A_REVERSE);
    mvprintw(screenRows, 0, "%-*s", screenCols, status.c_str());
    attroff(A_REVERSE);
}

void Editor::render() {
    int screenRows;
    int screenCols;
    getmaxyx(stdscr, screenRows, screenCols);
    screenRows -= 1;

    int gutter = gutterWidth();
    int textCols = screenCols - gutter;
    if (textCols < 1) {
        textCols = 1;
    }

    clampCursor();
    adjustViewport(screenRows, textCols);

    erase();

    for (int row = 0; row < screenRows; ++row) {
        int fileRow = row + rowOffset;
        if (fileRow >= buffer.lineCount()) {
            break;
        }

        if (gutter > 0) {
            attron(A_DIM);
            mvprintw(row, 0, "%*d ", gutter - 1, fileRow + 1);
            attroff(A_DIM);
        }

        const std::string& text = buffer.line(fileRow);
        if (colOffset < static_cast<int>(text.size())) {
            std::string visible = text.substr(colOffset);
            if (static_cast<int>(visible.size()) > textCols) {
                visible.resize(textCols);
            }
            mvprintw(row, gutter, "%s", visible.c_str());
        }
    }

    renderStatus(screenRows, screenCols);

    move(cursorRow - rowOffset, gutter + cursorCol - colOffset);
    refresh();
}
