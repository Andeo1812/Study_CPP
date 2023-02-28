#include <iostream>
#include <array>
#include <memory>
#include <vector>
#include <unordered_map>
#include <regex>
#include <cmath>

//    Напишите программу на любом языке программирования, которая поместит + (2.jpeg+3.jpeg), - (3.jpeg-2.jpeg), или ничего ( ) в
//    промежутках между цифрами от 9 до 0 (в таком порядке) так, чтобы в результате получилось 200.
//    Например: 98+76-5+43-2.jpeg-10=200.

//  Global params
const size_t base = 3;
const size_t quantity = 20000;
const std::regex numReg(R"([-+]?\d*\.?\d+)");

//  Messages
const std::string_view errorSuchExpressionNotExist = "Нет выражений для такого результата!";
const std::string_view success = "Для заданного результата есть выражения:";

std::string ternary(int64_t number) {
    std::string res;

    while (number > 0) {
        res = std::to_string(number % base) + res;

        number /= base;
    }

    return res;
}

std::string mathExpression(size_t number) {
    std::string ter = ternary(number);
    if (ter.empty()) {
        return {};
    }

    std::vector<char> terVector(ter.length());
    for (size_t i = 0; i < ter.capacity(); ++i) {
        terVector[i] = ter[i];
    }

    std::array<char, 9> mark = {'\0'};

    size_t offset = mark.size() - terVector.size();

    for (size_t i = 0; i < terVector.size(); ++i) {
        char elem = terVector[i];

        if (elem == '1') {
            mark[i + offset] = '+';
        } else if (elem == '2') {
            mark[i + offset] = '-';
        }
    }

    std::string res;

    for (size_t i = 0; i < mark.size(); ++i) {
        res += std::to_string(mark.size() - i);

        if (mark[i] != '\0') {
            res += mark[i];
        }
    }
    res += '0';

    return res;
}

int64_t evalNative(std::string exp) {
    if (exp.empty()) {
        return {};
    }

    int64_t res = 0;

    for (auto i = std::sregex_iterator(exp.begin(), exp.end(), numReg);
         i != std::sregex_iterator(); ++i) {
        res += std::stoll(i->str());
    }


    return res;
}

void run(int64_t expressionResult) {
    std::map <std::string, int64_t> results;

    for (size_t i = 0; i < quantity; ++i) {
        std::string exp = mathExpression(i);

        int64_t resCalk = evalNative(exp);

        if (resCalk == expressionResult) {
            results.insert({exp, expressionResult});
        }
    }

    // Output
    if (!results.empty()) {
        std::cout << success << std::endl;

        for (const auto &pair: results) {
            std::cout << "\t" << pair.first << std::endl;
        }

        return;
    }

    std::cout << errorSuchExpressionNotExist << std::endl;

    return;
}

int main() {
    run(200);

    return EXIT_SUCCESS;
}
