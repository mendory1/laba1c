#pragma once
#include "Student.h"

class BadStudent : public Student {
public:
    BadStudent(std::string n);
    Answer solve(Equation eq) override;
};