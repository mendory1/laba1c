#pragma once
#include <string>
#include <map>
#include <vector>
#include "Equation.h" 

class Table;

class Teacher {
private:
    struct Letter {
        Equation eq;
        Answer studentAnswer;

        Letter(Equation e, Answer a) : eq(e), studentAnswer(a) {}

    };
    std::map<std::string, std::vector<Letter>> lettersMap;

public:
    Teacher() = default;
    ~Teacher()= default;
    
    void receiveLetter(Equation eq, Answer ans, const std::string& name);
    void checkAndGrade(Table& table);

private:
    Answer correctAnswer(const Equation& eq) const;
    bool isAnswerCorrect(const Answer& studentAns, const Equation& eq) const;
};
