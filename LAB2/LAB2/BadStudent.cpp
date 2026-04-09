#include "BadStudent.h" 

BadStudent::BadStudent(const std::string& n) : Student(n) {}

Answer BadStudent::solve(Equation eq) {
    return { 0, 0, 1 };
}
