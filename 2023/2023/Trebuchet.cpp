#include "utils.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include "Trebuchet.h"

std::pair<const char, const char> Trebuchet::findDigitsA(const std::string& word) {
    char firstDigit = '\t';
    char lastDigit = '\t';
    unsigned int n = word.length();
    for (size_t i = 0; i < n; i++) {
        if (charIsNum(word[i])) {
            if (firstDigit == '\t')
                firstDigit = word[i];
            lastDigit = word[i];
        }
    }
    return std::pair<const char, const char>(firstDigit, lastDigit);
}

unsigned int Trebuchet::sumDigitsA() {
    std::ifstream file;
    std::string line;
    file.open(filename);

    unsigned int sum = 0;
    while (std::getline(file, line)) {
        std::pair<const char, const char> digits = findDigitsA(line);
        sum += std::stoi(std::string(1, digits.first) + digits.second);
    }

    file.close();
    return sum;
}

unsigned int Trebuchet::sumDigitsB() {
    std::ifstream file;
    std::string line;
    file.open(filename);

    unsigned int sum = 0;
    while (std::getline(file, line)) {
        std::pair<const char, const char> digits = findDigitsB(line);
        sum += std::stoi(std::string(1, digits.first) + digits.second);
    }

    file.close();
    return sum;
}

std::pair<const char, const char> Trebuchet::findDigitsB(const std::string& word) {
    char firstDigit = '\t';
    char lastDigit = '\t';
    unsigned int n = word.length();
    for (size_t i = 0; i < n; i++) {
        for (const std::pair<const std::string, const char>& pair : wordToNumMap) {
            if (n - i >= pair.first.length() && word.substr(i, pair.first.length()) == pair.first) {
                if (firstDigit == '\t')
                    firstDigit = pair.second;
                lastDigit = pair.second;
            };

        }
        if (charIsNum(word[i])) {
            if (firstDigit == '\t')
                firstDigit = word[i];
            lastDigit = word[i];
        }
    }
    return std::pair<const char, const char>(firstDigit, lastDigit);
}