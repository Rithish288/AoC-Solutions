#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "CubeConundrum.h"


std::string::const_iterator CubeConundrum::getListStartIndex(const std::string& line) {
    std::string::const_iterator it = line.begin();
    for (; it != line.end(); it++) {
        if (*it == ':')
            return it + 2;
    }
    return line.end();
}

unsigned int CubeConundrum::getGameId(const std::string& line, std::string::const_iterator listStart) {
    const std::string strId = line.substr(5, (listStart-line.begin())-6);
    return std::stoi(strId);
}

std::vector<std::string> CubeConundrum::getColoursList(const std::string& line, std::string::const_iterator listStart) {
    std::vector<std::string> vec{};
    std::string::const_iterator subListstart = listStart, it = listStart;
    for (; it != line.end(); ++it) {
        if (*it == ';') {
            vec.push_back(std::string(subListstart, it));
            subListstart = (++it)+1;
        }
    }
    vec.push_back(std::string(subListstart, it));
    return vec;
}

bool CubeConundrum::validateSubList(const std::string& subList) {
    // splitting "8 green, 4 blue, 2 red" by comma
    std::vector<std::string> coloursCount{};
    size_t i = 0, j = 0;
    for (; i < subList.length(); ++i) {
        if (subList[i] == ',') {
            coloursCount.push_back(subList.substr(j, i - j));
            j = (++i) + 1;
        }
    }
    coloursCount.push_back(subList.substr(j, i - j));

    // a map to hold to color and its count. Eg. {"green", 8}
    std::map<const std::string, unsigned int> m;
    for (const std::string& word: coloursCount) {
        size_t space = word.find(' ', 0);
        unsigned int count = std::stoi(std::string(word.begin(), word.begin() + space));
        const std::string color = word.substr(space+1, word.length()-space-1);
        if (
            color == "red" && count > 12 ||
            color == "green" && count > 13 ||
            color == "blue" && count > 14
            ) return false;
    }
    return true;
}

unsigned int CubeConundrum::getValidGameId(const std::string& line) {
    std::string::const_iterator listStart = getListStartIndex(line);
    std::vector<std::string> colourList{ this->getColoursList(line, listStart) };
    for (const std::string colours : colourList) {
        if(!validateSubList(colours))
            return 0;
    }
    return getGameId(line, listStart);
}

unsigned int CubeConundrum::sumGameIds() {
    std::ifstream file;
    std::string line;
    file.open(filename);

    unsigned int sum = 0;
    while (std::getline(file, line)) {
        sum += getValidGameId(line);
    }

    file.close();
    return sum;
}