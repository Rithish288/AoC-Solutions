#pragma once
#include <vector>

class CubeConundrum {
    std::string filename;
    std::string::const_iterator getListStartIndex(const std::string & line);
    unsigned int getGameId(const std::string& line, std::string::const_iterator listStart);
    std::vector<std::string> getColoursList(const std::string& line, std::string::const_iterator listStart);
    bool validateSubList(const std::string& subList);
public:
    CubeConundrum(const std::string& filename) : filename(filename) {};
    unsigned int getValidGameId(const std::string& line);
    unsigned int sumGameIds();
};