#include "GoodStudent.h"
#include <cmath>
#define EPS 1e-9

GoodStudent::GoodStudent(const std::string& n) : Student(n) {}

Answer GoodStudent::solve(Equation eq) {
    if (std::abs(eq.a) < EPS) {
        return checkBadEquation(eq);
    }

    double d = eq.b * eq.b - 4 * eq.a * eq.c;

    if (d < -EPS) return { 0, 0, 0 };

    double sqrt_d = sqrt(d);
    double x1 = (-eq.b - sqrt_d) / (2 * eq.a);
    double x2 = (-eq.b + sqrt_d) / (2 * eq.a);
    if (std::abs(d) < EPS) return { x1, x1, 1 };
    return { x1, x2, 2 };
}
