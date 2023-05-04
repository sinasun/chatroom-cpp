#include "file.h"


bool File::createFile(std::string fileName){
    std::ofstream file(fileName);
    if(file.is_open()){
        file.close();
        return true;
    }
    return false;
}

bool File::deleteFile(std::string fileName){
    if(remove(fileName.c_str()) == 0){
        return true;
    }
    return false;
}

std::string File::readFile(std::string fileName){
    std::ifstream file(fileName);
    std::string content;
    if(file.is_open()){
        std::string line;
        while(getline(file, line)){
            content += line + "\n";
        }
        file.close();
    }
    return content;
}

bool File::lineExist(std::string fileName, std::string line){
    std::string content = readFile(fileName);
    std::string::size_type pos = content.find(line);
    if(pos != std::string::npos){
        return true;
    }
    return false;
}


bool File::appendFile(std::string fileName, std::string content){
    std::ofstream file(fileName, std::ios_base::app);
    if(file.is_open()){
        file << content + "\n";
        file.close();
        return true;
    }
    return false;
}

bool File::deleteLine(std::string fileName, std::string line){
    std::string content = readFile(fileName);
    std::string::size_type pos = content.find(line);
    if(pos != std::string::npos){
        content.erase(pos, line.length());
        return appendFile(fileName, content);
    }
    return false;
}