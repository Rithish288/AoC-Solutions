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

std::vector<std::string> CubeConundrum::splitBySemiColon(const std::string& line, std::string::const_iterator listStart) {
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

std::vector<std::string> CubeConundrum::splitListByComma(const std::string& list) {
    std::vector<std::string> colours{};
    size_t i = 0, j = 0;

    for (; i < list.length(); ++i) {
        if (list[i] == ',') {
            colours.push_back(list.substr(j, i - j));
            j = (++i) + 1;
        }
    }

    colours.push_back(list.substr(j, i - j));
    return colours;
}

bool CubeConundrum::validateSubList(const std::string& subList) {
    const std::vector<std::string> colours = splitListByComma(subList);

    for (const std::string& word: colours) {
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
    std::vector<std::string> colourList{ splitBySemiColon(line, listStart) };

    for (const std::string colours : colourList) {
        if(!validateSubList(colours))
            return 0;
    }

    return getGameId(line, listStart);
}

unsigned int CubeConundrum::getGamePower(const std::string& game) {
    std::string::const_iterator listStart = getListStartIndex(game);
    std::vector<std::string> colourList{ splitBySemiColon(game, listStart) };
    unsigned int minRGB[3] { 0, 0, 0 };

    for (const std::string& list : colourList) {
        const std::vector<std::string> colours = splitListByComma(list);
        for (const std::string& word : colours) {
            size_t space = word.find(' ', 0);
            unsigned int count = std::stoi(std::string(word.begin(), word.begin() + space));
            const std::string color = word.substr(space + 1, word.length() - space - 1);
            if (color == "red")
                minRGB[0] = std::max(minRGB[0], count);
            else if (color == "green")
                minRGB[1] = std::max(minRGB[1], count);
            else
                minRGB[2] = std::max(minRGB[2], count);
        }
    }

    return minRGB[0] * minRGB[1] * minRGB[2];
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

unsigned int CubeConundrum::sumGamePowers() {
    std::ifstream file;
    std::string line;
    file.open(filename);

    unsigned int sum = 0;
    while (std::getline(file, line)) {
        sum += getGamePower(line);
    }

    file.close();
    return sum;
}