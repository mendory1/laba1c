#include "Teacher.h"
#include "Table.h"
#include <cmath>
#define EPS 1e-9

void Teacher::receiveLetter(Equation eq, Answer ans, const std::string& name) {
    lettersMap[name].push_back(Letter(eq, ans));
}

Answer Teacher::correctAnswer(const Equation& eq) const {
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

    double d = eq.b * eq.b - 4 * eq.a * eq.c;

    if (d < -EPS) return { 0, 0, 0 };

    double sqrt_d = sqrt(d);
    double x1 = (-eq.b - sqrt_d) / (2 * eq.a);
    double x2 = (-eq.b + sqrt_d) / (2 * eq.a);

    if (std::abs(d) < EPS) return { x1, x1, 1 };
    return { x1, x2, 2 };
}

bool Teacher::isAnswerCorrect(const Answer& studentAns, const Equation& eq) const {
    Answer correct = correctAnswer(eq);

    if (correct.rootsCount == -1) {
        return studentAns.rootsCount == -1;
    }

    if (correct.rootsCount == 0) {
        return studentAns.rootsCount == 0;
    }

    if (correct.rootsCount == 1) {
        return studentAns.rootsCount == 1 &&
            std::abs(studentAns.root1 - correct.root1) < EPS;
    }

    return studentAns.rootsCount == 2 &&
        ((std::abs(studentAns.root1 - correct.root1) < EPS &&
            std::abs(studentAns.root2 - correct.root2) < EPS) ||
            (std::abs(studentAns.root1 - correct.root2) < EPS &&
                std::abs(studentAns.root2 - correct.root1) < EPS));
}

void Teacher::checkAndGrade(Table& table) {
    for (auto& pair : lettersMap) {
        const std::string& studentName = pair.first;
        const std::vector<Letter>& letters = pair.second;

        for (const Letter& letter : letters) {
            if (isAnswerCorrect(letter.studentAnswer, letter.eq)) {
                table.addScore(studentName, 1);
            }
        }
    }
    lettersMap.clear();
}
