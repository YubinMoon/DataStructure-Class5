#ifndef TREE_H
#define TREE_H

#include "Node.h"

#include <string>

using namespace std;

class Tree
{
public:
    Tree();
    ~Tree();

    void makeTree(const int frequencies[]); // Huffman Tree 생성
    void makeCodes(string codes[]) const;   // 각 문자의 코드 추출
    const Node *root() const;

private:
    Node *rootNode;

    int findSmallestNode(Node *nodes[], int count, int skipIndex) const;
    void clear(Node *node);
    void collectCodes(const Node *node,
                      const string &prefix,
                      string codes[]) const;
};

#endif
