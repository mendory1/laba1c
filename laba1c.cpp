#include <iostream>
#include <string>
#include <cmath>
#include <ctime>

struct Equation {
    double a, b, c;
};

struct Answer {
    double root1;
    double root2;
    int rootsCount;
};

class Student {
protected:
    std::string name;
public:
    Student(std::string n) : name(n) {}
    virtual ~Student() {}
    std::string getName() const { return name; }

    virtual Answer solve(Equation eq) = 0;
};

class BadStudent : public Student {
public:
    BadStudent(std::string n) : Student(n) {}
    Answer solve(Equation eq) override {
        return { 0, 0, 0 };  // всегда неправильно
    }
};

class AverageStudent : public Student {
public:
    AverageStudent(std::string n) : Student(n) {}
    Answer solve(Equation eq) override {
        if (rand() % 2 == 0) {
            return { 42, 42, 1 };  // случайный неправильный ответ
        }

        double d = eq.b * eq.b - 4 * eq.a * eq.c;

        if (d < 0) return { 0, 0, 0 };  // нет корней

        double sqrt_d = sqrt(d);
        double x1 = (-eq.b - sqrt_d) / (2 * eq.a);
        double x2 = (-eq.b + sqrt_d) / (2 * eq.a);

        if (d == 0) return { x1, x1, 1 };  // один корень
        return { x1, x2, 2 };  // два корня
    }
};

class GoodStudent : public Student {
public:
    GoodStudent(std::string n) : Student(n) {}
    Answer solve(Equation eq) override {
        double d = eq.b * eq.b - 4 * eq.a * eq.c;

        if (d < 0) return { 0, 0, 0 };

        double sqrt_d = sqrt(d);
        double x1 = (-eq.b - sqrt_d) / (2 * eq.a);
        double x2 = (-eq.b + sqrt_d) / (2 * eq.a);

        if (d == 0) return { x1, x1, 1 };
        return { x1, x2, 2 };
    }
};

struct Letter {
    Equation eq;
    Answer studentAnswer;
    std::string studentName;
    Letter* next;
};

struct Record {
    std::string name;
    int score;
};

class Teacher {
private:
    Letter* head;
    Record* table;
    int tableSize;

public:
    Teacher() : head(nullptr), table(nullptr), tableSize(0) {}

    ~Teacher() {
        while (head) {
            Letter* temp = head;
            head = head->next;
            delete temp;
        }
        delete[] table;
    }

    void registerStudents(Student** list, int count) {
        tableSize = count;
        table = new Record[tableSize];
        for (int i = 0; i < count; ++i) {
            table[i] = { list[i]->getName(), 0 };
        }
    }

    void receiveLetter(Equation eq, Answer ans, std::string name) {
        Letter* newLetter = new Letter{ eq, ans, name, nullptr };
        if (!head) head = newLetter;
        else {
            Letter* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newLetter;
        }
    }

    void checkLetters() {
        Letter* current = head;
        while (current) {
            double d = current->eq.b * current->eq.b - 4 * current->eq.a * current->eq.c;

            Answer correctAnswer;
            bool isCorrect = false;

            if (d < 0) {
                correctAnswer = { 0, 0, 0 };
                isCorrect = (current->studentAnswer.rootsCount == 0);
            }
            else {
                double sqrt_d = sqrt(d);
                double x1 = (-current->eq.b - sqrt_d) / (2 * current->eq.a);
                double x2 = (-current->eq.b + sqrt_d) / (2 * current->eq.a);

                if (d == 0) {
                    correctAnswer = { x1, x1, 1 };
                    // Проверяем один корень
                    isCorrect = (current->studentAnswer.rootsCount == 1 &&
                        std::abs(current->studentAnswer.root1 - x1) < 0.001);
                }
                else {
                    correctAnswer = { x1, x2, 2 };
                    // Проверяем два корня (порядок не важен)
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

    void publishTable() {
        std::cout << "ФИО студента\t| Решено задач правильно\n";
        std::cout << "----------------------------------------\n";
        for (int i = 0; i < tableSize; ++i) {
            std::cout << table[i].name << "\t| " << table[i].score << "\n";
        }
    }
};

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
        {1, -5, 6},   // корни 3 и 2
        {1, 2, 1},    // корень -1
        {1, -3, 2},   // корни 2 и 1
        {1, 0, -4},   // корни 2 и -2
        {2, -4, 2}    // корень 1
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
