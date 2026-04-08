#include "Teacher.h"
#include "Student.h"
#include <cmath>
#include <iostream>

Teacher::Teacher() : head(nullptr), table(nullptr), tableSize(0) {}

Teacher::~Teacher() {
    while (head) {
        Letter* temp = head;
        head = head->next;
        delete temp;
    }
    delete[] table;
}

void Teacher::registerStudents(Student** list, int count) {
    tableSize = count;
    table = new Record[tableSize];
    for (int i = 0; i < count; ++i) {
        table[i] = { list[i]->getName(), 0 };
    }
}

void Teacher::receiveLetter(Equation eq, Answer ans, std::string name) {
    Letter* newLetter = new Letter{ eq, ans, name, nullptr };
    if (!head) head = newLetter;
    else {
        Letter* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newLetter;
    }
}

void Teacher::checkLetters() {
    Letter* current = head;
    while (current) {
        double d = current->eq.b * current->eq.b - 4 * current->eq.a * current->eq.c;

        bool isCorrect = false;

        if (d < 0) {
            isCorrect = (current->studentAnswer.rootsCount == 0);
        }
        else {
            double sqrt_d = sqrt(d);
            double x1 = (-current->eq.b - sqrt_d) / (2 * current->eq.a);
            double x2 = (-current->eq.b + sqrt_d) / (2 * current->eq.a);

            if (d == 0) {
                isCorrect = (current->studentAnswer.rootsCount == 1 &&
                    std::abs(current->studentAnswer.root1 - x1) < 0.001);
            }
            else {
                isCorrect = (current->studentAnswer.rootsCount == 2 &&
                    ((std::abs(current->studentAnswer.root1 - x1) < 0.001 &&
                        std::abs(current->studentAnswer.root2 - x2) < 0.001) ||
                        (std::abs(current->studentAnswer.root1 - x2) < 0.001 &&
                            std::abs(current->studentAnswer.root2 - x1) < 0.001)));
            }
        }

        if (isCorrect) {
            for (int i = 0; i < tableSize; ++i) {
                if (table[i].name == current->studentName) {
                    table[i].score++;
                    break;
                }
            }
        }
        current = current->next;
    }
}

void Teacher::publishTable() {
    std::cout << "            \t|                       \n";
    std::cout << "----------------------------------------\n";
    for (int i = 0; i < tableSize; ++i) {
        std::cout << table[i].name << "\t| " << table[i].score << "\n";
    }
}