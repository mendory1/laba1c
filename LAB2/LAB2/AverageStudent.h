#pragma once
#include "Student.h" 

class AverageStudent : public Student {
public:
    AverageStudent(std::string n);
    Answer solve(Equation eq) override;
};