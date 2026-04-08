#pragma once
#include <string>
#include "Equation.h" 

class Student {
protected:
    std::string name;
public:
    Student(std::string n);
    virtual ~Student();
    std::string getName() const;
    virtual Answer solve(Equation eq) = 0;
};