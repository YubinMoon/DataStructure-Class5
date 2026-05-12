#include "BinaryTree.h"

#include <iostream>
#include <queue>

TreeNode::TreeNode(const std::string& value)
    : data(value), left(nullptr), right(nullptr) {}

BinaryTree::BinaryTree(TreeNode* rootNode)
    : root(rootNode) {}

BinaryTree::~BinaryTree() {
    destroy(root);
}

TreeNode* BinaryTree::getRoot() const {
    return root;
}

void BinaryTree::destroy(TreeNode* node) {
    if (node == nullptr) return;

    destroy(node->left);
    destroy(node->right);
    delete node;
}

void BinaryTree::printInfix(TreeNode* node) {
    if (node == nullptr) return;

    bool isOperatorNode = (node->left != nullptr || node->right != nullptr);

    if (isOperatorNode) std::cout << "(";

    printInfix(node->left);
    std::cout << node->data;
    printInfix(node->right);

    if (isOperatorNode) std::cout << ")";
}

void BinaryTree::printPrefix(TreeNode* node) {
    if (node == nullptr) return;

    std::cout << node->data << " ";
    printPrefix(node->left);
    printPrefix(node->right);
}

void BinaryTree::printPostfix(TreeNode* node) {
    if (node == nullptr) return;

    printPostfix(node->left);
    printPostfix(node->right);
    std::cout << node->data << " ";
}

void BinaryTree::printInfix() const {
    printInfix(root);
    std::cout << std::endl;
}

void BinaryTree::printPrefix() const {
    printPrefix(root);
    std::cout << std::endl;
}

void BinaryTree::printPostfix() const {
    printPostfix(root);
    std::cout << std::endl;
}

void BinaryTree::printLevelOrder() const {
    if (root == nullptr) {
        std::cout << std::endl;
        return;
    }

    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();

        std::cout << current->data << " ";

        if (current->left != nullptr) {
            q.push(current->left);
        }

        if (current->right != nullptr) {
            q.push(current->right);
        }
    }

    std::cout << std::endl;
}