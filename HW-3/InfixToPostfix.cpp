#include "InfixToPostfix.h"

#include "Stack/Stack.h"

bool isOperand(char ch) {
    return ch >= '0' && ch <= '9';
}

bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int precedence(char op) {
    if (op == '*' || op == '/') {
        return 2;
    }

    if (op == '+' || op == '-') {
        return 1;
    }

    return 0;
}

std::string infixToPostfix(const std::string& infix) {
    int length = infix.length();
    Stack operators(length);
    std::string postfix;
    char topValue = '\0';

    for (int i = 0; i < length; ++i) {
        char ch = infix[i];

        if (isOperand(ch)) {
            postfix += ch;
        } else if (ch == '(') {
            operators.push(ch);
        } else if (ch == ')') {
            while (operators.top(topValue) && topValue != '(') {
                operators.pop(topValue);
                postfix += topValue;
            }
            operators.pop(topValue);
        } else {
            while (operators.top(topValue) && topValue != '(' &&
                   precedence(topValue) >= precedence(ch)) {
                operators.pop(topValue);
                postfix += topValue;
            }
            operators.push(ch);
        }
    }

    while (operators.pop(topValue)) {
        postfix += topValue;
    }

    return postfix;
}

void appendToken(std::string& postfix, const std::string& token) {
    if (!postfix.empty()) {
        postfix += ' ';
    }

    postfix += token;
}

std::string infixToPostfixv2(const std::string& infix) {
    int length = infix.length();
    Stack operators(length);
    std::string postfix;
    char topValue = '\0';

    for (int i = 0; i < length; ++i) {
        char ch = infix[i];

        if (ch == ' ') {
            continue;
        }

        if (isOperand(ch)) {
            std::string number;

            while (i < length && isOperand(infix[i])) {
                number += infix[i];
                ++i;
            }

            --i;
            appendToken(postfix, number);
        } else if (ch == '(') {
            operators.push(ch);
        } else if (ch == ')') {
            while (operators.top(topValue) && topValue != '(') {
                operators.pop(topValue);
                appendToken(postfix, std::string(1, topValue));
            }
            operators.pop(topValue);
        } else if (isOperator(ch)) {
            while (operators.top(topValue) && topValue != '(' &&
                   precedence(topValue) >= precedence(ch)) {
                operators.pop(topValue);
                appendToken(postfix, std::string(1, topValue));
            }
            operators.push(ch);
        }
    }

    while (operators.pop(topValue)) {
        appendToken(postfix, std::string(1, topValue));
    }

    return postfix;
}
