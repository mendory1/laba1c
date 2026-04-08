#include <ctime>
#include <cstdlib>
#include <locale.h>
#include "Equation.h"
#include "Student.h"
#include "BadStudent.h"
#include "AverageStudent.h"
#include "GoodStudent.h"
#include "Teacher.h"


int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    Teacher teacher;

    Student* group[7];
    group[0] = new GoodStudent("Романов   ");
    group[1] = new GoodStudent("Егоров    ");
    group[2] = new AverageStudent("Николаев  ");
    group[3] = new AverageStudent("Андреев   ");
    group[4] = new BadStudent("Макаров   ");
    group[5] = new BadStudent("Степанов  ");
    group[6] = new BadStudent("Фёдоров   ");

    teacher.registerStudents(group, 7);

    Equation tasks[5] = {
        {1, -5, 6},
        {1, 2, 1},
        {1, -3, 2},
        {1, 0, -4},
        {2, -4, 2}
    };

    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 5; ++j) {
            teacher.receiveLetter(tasks[j], group[i]->solve(tasks[j]), group[i]->getName());
        }
    }

    teacher.checkLetters();
    teacher.publishTable();

    for (int i = 0; i < 7; ++i) delete group[i];

    return 0;
}