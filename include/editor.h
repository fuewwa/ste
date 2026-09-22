#pragma once

#include "buffer.h"

#include <string>

enum class Mode {
    General,
    Write
};

class Editor {
public:
    explicit Editor(const std::string& path);

    void run();

private:
    void render();
    void renderStatus(int screenRows, int screenCols);

    void handleGeneral(int ch);
    void handleWrite(int ch);

    void moveCursor(int deltaRow, int deltaCol);
    void clampCursor();
    void adjustViewport(int screenRows, int screenCols);

    void enterWrite();
    void enterGeneral();
    void saveFile();

    Buffer buffer;
    std::string filename;
    Mode mode;

    int cursorRow;
    int cursorCol;
    int rowOffset;
    int colOffset;

    bool running;
    bool modified;
};
