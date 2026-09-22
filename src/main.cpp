#include "editor.h"

#include <iostream>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "usage: ste <file>" << std::endl;
        return 1;
    }

    Editor editor(argv[1]);
    editor.run();

    return 0;
}
