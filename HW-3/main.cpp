#include "BinaryTree.h"
#include "ExpressionParser.h"
#include <iostream>
#include <string>

int main() {
    std::string input;

    std::cout << "산술식을 입력하세요: ";
    std::getline(std::cin, input);

    try {
        ExpressionParser parser;
        TreeNode* root = parser.parse(input);
        BinaryTree tree(root);

        std::cout << "Infix order 출력: ";
        tree.printInfix();
    } catch (const std::exception& e) {
        std::cerr << "오류: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}