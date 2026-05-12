#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <string>

struct TreeNode {
    std::string data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const std::string& value);
};

class BinaryTree {
private:
    TreeNode* root;

    static void destroy(TreeNode* node);

    static void printInfix(TreeNode* node);
    static void printPrefix(TreeNode* node);
    static void printPostfix(TreeNode* node);

public:
    explicit BinaryTree(TreeNode* rootNode = nullptr);
    ~BinaryTree();

    BinaryTree(const BinaryTree&) = delete;
    BinaryTree& operator=(const BinaryTree&) = delete;

    TreeNode* getRoot() const;

    void printInfix() const;
    void printPrefix() const;
    void printPostfix() const;
    void printLevelOrder() const;
};

#endif