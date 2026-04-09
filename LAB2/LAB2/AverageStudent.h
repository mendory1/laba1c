#pragma once
#include "Student.h" 

class AverageStudent : public Student {
public:
    AverageStudent(const std::string& n);
    Answer solve(Equation eq) override;
};
