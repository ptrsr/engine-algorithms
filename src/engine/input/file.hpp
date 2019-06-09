#ifndef FILE_HPP_
#define FILE_HPP_

#include <string>

struct File {
    const std::string extention;
    const std::string content;

    File(std::string path);
};

#endif//FILE_HPP_
