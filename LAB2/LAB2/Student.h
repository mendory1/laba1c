#pragma once
#include <string>
#include "Equation.h" 

class Student {
protected:
    std::string name;
    Answer checkBadEquation(const Equation& eq) const;
public:
    Student(const std::string& n);
    virtual ~Student();
    std::string getName() const;
    virtual Answer solve(Equation eq) = 0;
};
