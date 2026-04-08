#pragma once
#include <string>
#include "Equation.h" 

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
    Teacher();
    ~Teacher();
    void registerStudents(class Student** list, int count);
    void receiveLetter(Equation eq, Answer ans, std::string name);
    void checkLetters();
    void publishTable();
};