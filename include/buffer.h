#pragma once

#include <string>
#include <vector>

class Buffer {
public:
    Buffer();

    void load(const std::string& path);
    void save(const std::string& path) const;

    int lineCount() const;
    int lineLength(int row) const;
    const std::string& line(int row) const;

    void insertChar(int row, int col, char c);
    void insertTab(int row, int col, int width);
    void insertNewline(int row, int col);
    void deleteChar(int row, int col);
    void deleteNewline(int row);

private:
    std::vector<std::string> lines;
};
