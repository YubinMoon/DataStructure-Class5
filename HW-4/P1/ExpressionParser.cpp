#include "ExpressionParser.h"
#include <cctype>
#include <stdexcept>

void ExpressionParser::skipSpaces() {
    while (pos < static_cast<int>(expression.size()) &&
           std::isspace(static_cast<unsigned char>(expression[pos]))) {
        pos++;
    }
}

char ExpressionParser::peek() {
    skipSpaces();

    if (pos >= static_cast<int>(expression.size())) {
        return '\0';
    }

    return expression[pos];
}

char ExpressionParser::get() {
    skipSpaces();

    if (pos >= static_cast<int>(expression.size())) {
        return '\0';
    }

    return expression[pos++];
}

TreeNode* ExpressionParser::parse(const std::string& input) {
    expression = input;
    pos = 0;

    TreeNode* root = parseExpression();

    if (peek() != '\0') {
        throw std::runtime_error("수식 끝 이후에 알 수 없는 문자가 있습니다.");
    }

    return root;
}

TreeNode* ExpressionParser::parseExpression() {
    TreeNode* left = parseTerm();

    while (peek() == '+' || peek() == '-') {
        char op = get();
        TreeNode* right = parseTerm();

        TreeNode* parent = new TreeNode(std::string(1, op));
        parent->left = left;
        parent->right = right;

        left = parent;
    }

    return left;
}

TreeNode* ExpressionParser::parseTerm() {
    TreeNode* left = parseFactor();

    while (peek() == '*' || peek() == '/') {
        char op = get();
        TreeNode* right = parseFactor();

        TreeNode* parent = new TreeNode(std::string(1, op));
        parent->left = left;
        parent->right = right;

        left = parent;
    }

    return left;
}

TreeNode* ExpressionParser::parseFactor() {
    if (peek() == '(') {
        get();

        TreeNode* node = parseExpression();

        if (get() != ')') {
            throw std::runtime_error("닫는 괄호 ')'가 필요합니다.");
        }

        return node;
    }

    return parseOperand();
}

TreeNode* ExpressionParser::parseOperand() {
    skipSpaces();

    if (pos >= static_cast<int>(expression.size())) {
        throw std::runtime_error("피연산자가 필요합니다.");
    }

    std::string token;

    if (std::isalnum(static_cast<unsigned char>(expression[pos])) ||
        expression[pos] == '_') {

        while (pos < static_cast<int>(expression.size()) &&
               (std::isalnum(static_cast<unsigned char>(expression[pos])) ||
                expression[pos] == '_' ||
                expression[pos] == '.')) {
            token += expression[pos++];
        }
    } else {
        throw std::runtime_error("잘못된 피연산자입니다.");
    }

    return new TreeNode(token);
}