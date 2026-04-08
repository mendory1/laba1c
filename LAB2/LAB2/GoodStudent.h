#pragma once 
#include "Student.h"

class GoodStudent : public Student {
public:
    GoodStudent(std::string n);
    Answer solve(Equation eq) override;
};