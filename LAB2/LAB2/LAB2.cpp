#include <iostream>
#include <vector>
#include "Equation.h"
#include "Student.h"
#include "BadStudent.h"
#include "AverageStudent.h"
#include "GoodStudent.h"
#include "Teacher.h"
#include "Table.h"
#include "Reader.h"

int main() {
    setlocale(LC_ALL, "Russian");
    
    Teacher teacher;
    Table table;

    std::vector<Student*> group;
    std::vector<std::string> names = { "Романов", "Егоров", "Николаев",
        "Андреев", "Макаров", "Степанов", "Фёдоров" };
    
    group.push_back(new GoodStudent(names[0]));
    group.push_back(new GoodStudent(names[1]));
    group.push_back(new AverageStudent(names[2]));
    group.push_back(new AverageStudent(names[3]));
    group.push_back(new BadStudent(names[4]));
    group.push_back(new BadStudent(names[5]));
    group.push_back(new BadStudent(names[6]));

    for (const auto& name : names) {
        table.registerStudent(name);
    }

    std::vector<Equation> tasks = Reader::readEquations("input.txt");

    if (tasks.empty()) {
        std::cout << "Нет уравнений для решения" << std::endl;
        return 1;
    }

    for (Student* student : group) {
        for (const Equation& eq : tasks) {
            teacher.receiveLetter(eq, student->solve(eq), student->getName());
        }
    }

    teacher.checkAndGrade(table);
    table.print();

    for (Student* student : group) {
        delete student;
    }

    return 0;
}
