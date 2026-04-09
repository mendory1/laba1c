#include "Student.h"
#define EPS 1e-9

Student::Student(const std::string& n) : name(n) {}

Student::~Student() {}

std::string Student::getName() const {
    return name;
}

Answer Student::checkBadEquation(const Equation& eq) const {
    if (std::abs(eq.a) < EPS) {
        if (std::abs(eq.b) < EPS) {
            if (std::abs(eq.c) < EPS) {
                return { 0, 0, -1 };
            }
            else {
                return { 0, 0, 0 };
            }
        }
        else {
            double x = -eq.c / eq.b;
            return { x, x, 1 };
        }
    }
    return { 0, 0, -2 };
}
