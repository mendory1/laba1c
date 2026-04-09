#pragma once
#include <string>
#include <vector>
#include "Equation.h"

class Reader {
public:
    static std::vector<Equation> readEquations(const std::string& filename);
};
