#pragma once
#include <string>
#include <map>

class Table {
private:
    std::map<std::string, int> records;

public:
    Table() = default;
    ~Table() = default;

    void registerStudent(const std::string& name);
    void registerStudents(const std::string* names, int count);
    void addScore(const std::string& name, int points);
    int getScore(const std::string& name) const;
    void print() const;
};
