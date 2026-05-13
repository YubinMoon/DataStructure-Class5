#include "Node.h"

Node::Node(char value, int frequency)
    : value(value), frequency(frequency), left(nullptr), right(nullptr) {}

Node::Node(Node *leftNode, Node *rightNode)
    : value(0), frequency(0), left(leftNode), right(rightNode)
{
    if (leftNode != nullptr)
    {
        frequency += leftNode->frequency;
    }
    if (rightNode != nullptr)
    {
        frequency += rightNode->frequency;
    }
}

bool Node::isLeaf() const
{
    return left == nullptr && right == nullptr;
}
