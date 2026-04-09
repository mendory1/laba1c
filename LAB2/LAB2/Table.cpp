#include "Table.h"
#include <iostream>

void Table::registerStudent(const std::string& name) {
    if (records.find(name) == records.end()) {
        records[name] = 0;
    }
}

void Table::registerStudents(const std::string* names, int count) {
    for (int i = 0; i < count; ++i) {
        registerStudent(names[i]);
    }
}

void Table::addScore(const std::string& name, int points) {
    auto point = records.find(name);
    if (point != records.end()) {
        point->second += points;
    }
}

int Table::getScore(const std::string& name) const {
    auto point = records.find(name);
    if (point != records.end()) {
        return point->second;
    }
    return -1;
}

void Table::print() const {
    std::cout << "ФИО студента - Решено задач правильно\n";
    std::cout << "------------------------------------\n";
    for (const auto& pair : records) {
        std::cout << pair.first << " - " << pair.second << "\n";
    }
}
