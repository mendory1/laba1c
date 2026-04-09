#include "AverageStudent.h" 
#include <cmath>
#include <random>
#define EPS 1e-9

AverageStudent::AverageStudent(const std::string& n) : Student(n) {}

Answer AverageStudent::solve(Equation eq) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 6);

    if (dist6(rng) % 2 == 0) {
        return { 1e100, 1e100, 2 };
    }

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
