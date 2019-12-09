// ToDo: Make Label.h with symbolTree
#include <utility>


#pragma once

#include <map>


namespace IrtTree {
class CLabel {
public:
std::string String() const
    {
        return label;
    }
private:
std::string label;
static std::map<std::string, int> counter;
};

class CTemp {
public:
std::string String() const
    {
        return label;
    }
private:
std::string label;
static std::map<std::string, int> counter;
};

};