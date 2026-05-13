#ifndef NODE_H
#define NODE_H

// Tree를 구성하는 Node
class Node
{
public:
    char value;
    int frequency;
    Node *left;
    Node *right;

    Node(char value, int frequency);
    Node(Node *left, Node *right);
    bool isLeaf() const;
};

#endif
