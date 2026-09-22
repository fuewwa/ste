#include "buffer.h"

#include <fstream>

Buffer::Buffer() {
    lines.push_back("");
}

void Buffer::load(const std::string& path) {
    std::ifstream in(path);
    if (!in.is_open()) {
        return;
    }

    lines.clear();
    std::string current;
    while (std::getline(in, current)) {
        lines.push_back(current);
    }

    if (lines.empty()) {
        lines.push_back("");
    }
}

void Buffer::save(const std::string& path) const {
    std::ofstream out(path, std::ios::trunc);
    if (!out.is_open()) {
        return;
    }

    for (std::size_t i = 0; i < lines.size(); ++i) {
        out << lines[i];
        if (i + 1 < lines.size()) {
            out << '\n';
        }
    }
    out << '\n';
}

int Buffer::lineCount() const {
    return static_cast<int>(lines.size());
}

int Buffer::lineLength(int row) const {
    if (row < 0 || row >= lineCount()) {
        return 0;
    }
    return static_cast<int>(lines[row].size());
}

const std::string& Buffer::line(int row) const {
    return lines[row];
}

void Buffer::insertChar(int row, int col, char c) {
    if (row < 0 || row >= lineCount()) {
        return;
    }
    std::string& target = lines[row];
    if (col < 0) {
        col = 0;
    }
    if (col > static_cast<int>(target.size())) {
        col = static_cast<int>(target.size());
    }
    target.insert(target.begin() + col, c);
}

void Buffer::insertTab(int row, int col, int width) {
    for (int i = 0; i < width; ++i) {
        insertChar(row, col + i, ' ');
    }
}

void Buffer::insertNewline(int row, int col) {
    if (row < 0 || row >= lineCount()) {
        return;
    }
    std::string& target = lines[row];
    if (col < 0) {
        col = 0;
    }
    if (col > static_cast<int>(target.size())) {
        col = static_cast<int>(target.size());
    }
    std::string tail = target.substr(col);
    target.erase(col);
    lines.insert(lines.begin() + row + 1, tail);
}

void Buffer::deleteChar(int row, int col) {
    if (row < 0 || row >= lineCount()) {
        return;
    }
    std::string& target = lines[row];
    if (col <= 0 || col > static_cast<int>(target.size())) {
        return;
    }
    target.erase(target.begin() + col - 1);
}

void Buffer::deleteNewline(int row) {
    if (row <= 0 || row >= lineCount()) {
        return;
    }
    std::string prev = lines[row - 1];
    std::string current = lines[row];
    lines.erase(lines.begin() + row);
    lines[row - 1] = prev + current;
}
