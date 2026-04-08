#include "AverageStudent.h" 
#include <cmath>
#include <cstdlib>

AverageStudent::AverageStudent(std::string n) : Student(n) {}

Answer AverageStudent::solve(Equation eq) {
    if (rand() % 2 == 0) {
        return { 42, 42, 1 };
    }

    double d = eq.b * eq.b - 4 * eq.a * eq.c;

    if (d < 0) return { 0, 0, 0 };

    double sqrt_d = sqrt(d);
    double x1 = (-eq.b - sqrt_d) / (2 * eq.a);
    double x2 = (-eq.b + sqrt_d) / (2 * eq.a);

    if (d == 0) return { x1, x1, 1 };
    return { x1, x2, 2 };
}