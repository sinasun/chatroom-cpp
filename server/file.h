#ifndef FILE_H
#define FILE_H

#include <string>
#include <fstream>

class File{
    public:
        bool createFile(std::string fileName);
        bool deleteFile(std::string fileName);
        std::string readFile(std::string fileName);
        bool lineExist(std::string fileName, std::string line);
        bool appendFile(std::string fileName, std::string content);
        bool deleteLine(std::string fileName, std::string line);
};


#endif