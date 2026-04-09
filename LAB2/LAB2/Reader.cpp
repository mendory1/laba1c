#include "Reader.h"
#include <fstream>
#include <iostream>

std::vector<Equation> Reader::readEquations(const std::string& filename) {
    std::vector<Equation> equations;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return equations;
    }

    double a, b, c;
    while (file >> a >> b >> c) {
        equations.push_back({ a, b, c });
    }

    file.close();
    return equations;
}
