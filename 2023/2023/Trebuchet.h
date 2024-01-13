#pragma once
#include <map>

class Trebuchet {
    std::string filename;
    std::map<const std::string, const char> wordToNumMap{
        { "one", '1' },
        { "two", '2' },
        { "three", '3' },
        { "four", '4' },
        { "five", '5' },
        { "six", '6' },
        { "seven", '7' },
        { "eight", '8' },
        { "nine", '9' }
    };
    std::pair<const char, const char> findDigitsA(const std::string& word);
    std::pair<const char, const char> findDigitsB(const std::string& word);
public:
    Trebuchet(const std::string& filename) : filename(filename) {};
    unsigned int sumDigitsA();
    unsigned int sumDigitsB();
};