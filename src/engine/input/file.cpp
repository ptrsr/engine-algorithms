#include "file.hpp"
#include <fstream>
#include <stdexcept>

std::string GetExtention(std::string path) {
    return path.substr(path.find_last_of('.') + 1);
}

std::string GetContent(std::string path) {
    std::ifstream in(path);
    if (!in) {
        throw new std::runtime_error("Could not load file: " + path);
    }
    in.seekg(0, std::ios::end);
    size_t len = in.tellg();
    in.seekg(0);
    std::string content(len, '\0');
    in.read(&content[0], len);
    in.close();
    return content;
}

File::File(std::string path)
    : extention(GetExtention(path))
    , content(GetContent(path))
    { }
