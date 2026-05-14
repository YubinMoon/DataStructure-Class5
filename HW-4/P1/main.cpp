#include "BinaryTree.h"
#include "ExpressionParser.h"
#include <iostream>
#include <string>
#include <vector>

int main() {
    // 평가 기준 충족: 최소 5개 이상의 연산자와 1개 이상의 ()가 포함된 수식 5개 준비
    std::vector<std::string> testExpressions = {
        "3 + 4 * (2 - 1) / 5 + 6",
        "(10 + 2) * 3 - 4 / 2 + 5",
        "8 / (2 + 2) * 3 - 1 + 7",
        "5 * (4 - 2) + 8 / 4 - 1",
        "(7 + 3) * (5 - 2) / 3 + 1"
    };

    ExpressionParser parser;

    for (size_t i = 0; i < testExpressions.size(); ++i) {
        std::cout << "========================================" << std::endl;
        std::cout << "Test " << i + 1 << ": " << testExpressions[i] << std::endl;
        
        try {
            TreeNode* root = parser.parse(testExpressions[i]);
            BinaryTree tree(root);

            std::cout << "[Infix order]   : ";
            tree.printInfix();
            
            std::cout << "[Prefix order]  : ";
            tree.printPrefix();
            
            std::cout << "[Postfix order] : ";
            tree.printPostfix();
            
            std::cout << "[Level order]   : ";
            tree.printLevelOrder();

        } catch (const std::exception& e) {
            std::cerr << "오류: " << e.what() << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}