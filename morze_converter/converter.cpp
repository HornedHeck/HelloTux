#include "converter.h"

const std::map<char, std::string> converter = {
        {' ', "  "},
        {'a', ".- "},
        {'b', "-... "},
        {'c', "-.-. "},
        {'d', "-.. "},
        {'e', ". "},
        {'f', "..-. "},
        {'g', "--. "},
        {'h', ".... "},
        {'i', ".. "},
        {'j', ".--- "},
        {'k', "-.- "},
        {'l', ".-.. "},
        {'m', "-- "},
        {'n', "-. "},
        {'o', "--- "},
        {'p', ".--. "},
        {'q', "--.- "},
        {'r', ".-. "},
        {'s', "... "},
        {'t', "- "},
        {'u', "..- "},
        {'v', "...- "},
        {'w', ".-- "},
        {'x', "-..- "},
        {'y', "-.-- "},
        {'z', "--.. "},
        {'\n', "\n"}
};

std::stringstream morze(std::istream &in){
    std::stringstream res;
    char c;
    while (in.get(c)) {
        if (converter.find(c) != converter.end()) {
            res << converter.at(c);
        }
    }
    return res;
}
