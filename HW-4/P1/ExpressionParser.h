#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

#include "BinaryTree.h"

#include <string>

class ExpressionParser {
private:
    std::string expression;
    int pos;

    void skipSpaces();
    char peek();
    char get();

    TreeNode* parseExpression();
    TreeNode* parseTerm();
    TreeNode* parseFactor();
    TreeNode* parseOperand();

public:
    TreeNode* parse(const std::string& input);
};

#endif