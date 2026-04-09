#pragma once
#include "Student.h"

class BadStudent : public Student {
public:
    BadStudent(const std::string& n);
    Answer solve(Equation eq) override;
};
