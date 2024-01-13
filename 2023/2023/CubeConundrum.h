#pragma once
#include <vector>

class CubeConundrum {
    std::string filename;
    std::string::const_iterator getListStartIndex(const std::string & line);
    unsigned int getGameId(const std::string& line, std::string::const_iterator listStart);
    std::vector<std::string> splitBySemiColon(const std::string& line, std::string::const_iterator listStart);
    std::vector<std::string> splitListByComma(const std::string& list);
    bool validateSubList(const std::string& subList);
public:
    CubeConundrum(const std::string& filename) : filename(filename) {};
    unsigned int getValidGameId(const std::string& line);
    unsigned int sumGameIds();
    unsigned int getGamePower(const std::string& game);
    unsigned int sumGamePowers();
};