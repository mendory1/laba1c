#include "BadStudent.h" 

BadStudent::BadStudent(std::string n) : Student(n) {}

Answer BadStudent::solve(Equation eq) {
    return { 0, 0, 0 };
}