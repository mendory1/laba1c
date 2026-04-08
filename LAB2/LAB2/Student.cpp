#include "Student.h"

Student::Student(std::string n) : name(n) {}

Student::~Student() {}

std::string Student::getName() const {
    return name;
}