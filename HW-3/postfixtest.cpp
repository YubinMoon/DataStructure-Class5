#include "InfixToPostfix.h"

#include <iostream>
#include <string>

bool checkPostfix(const std::string& infix, const std::string& expected) {
    std::string actual = infixToPostfix(infix);

    if (actual != expected) {
        std::cout << "FAIL: " << infix << " -> " << actual
                  << " expected " << expected << '\n';
        return false;
    }

    std::cout << "PASS: " << infix << " -> " << actual << '\n';
    return true;
}

bool checkPostfixv2(const std::string& infix, const std::string& expected) {
    std::string actual = infixToPostfixv2(infix);

    if (actual != expected) {
        std::cout << "FAIL v2: " << infix << " -> " << actual
                  << " expected " << expected << '\n';
        return false;
    }

    std::cout << "PASS v2: " << infix << " -> " << actual << '\n';
    return true;
}

int main() {
    bool passed = true;

    passed = checkPostfix("1+2", "12+") && passed;
    passed = checkPostfix("1+2*3", "123*+") && passed;
    passed = checkPostfix("(1+2)*3", "12+3*") && passed;
    passed = checkPostfix("1*(2+3)-4/5", "123+*45/-") && passed;
    passed = checkPostfix("((1+2)*(3-4))/5", "12+34-*5/") && passed;
    passed = checkPostfixv2("12+34", "12 34 +") && passed;
    passed = checkPostfixv2("12+34*5", "12 34 5 * +") && passed;
    passed = checkPostfixv2("(12+34)*56", "12 34 + 56 *") && passed;
    passed = checkPostfixv2("123*(45+6)-78/9", "123 45 6 + * 78 9 / -") && passed;
    passed = checkPostfixv2("100 + (20 - 3) * 4", "100 20 3 - 4 * +") && passed;

    if (passed) {
        std::cout << "All postfix tests passed.\n";
        return 0;
    }

    std::cout << "Some postfix tests failed.\n";
    return 1;
}
