#include "Tree.h"

Tree::Tree() : rootNode(nullptr) {}

Tree::~Tree()
{
    clear(rootNode);
}

void Tree::makeTree(const int frequencies[])
{
    clear(rootNode);
    rootNode = nullptr;

    Node *nodes[512];
    int count = 0;

    // 각 문자의 리프 노드 생성
    for (int i = 0; i < 256; i++)
    {
        if (frequencies[i] > 0) // 문자가 존재하면
        {
            nodes[count] = new Node(char(i), frequencies[i]);
            count++;
        }
    }

    // 빈도수가 가장 작은 노드 2개를 반복해서 결합
    while (count > 1)
    {
        int leftIndex = findSmallestNode(nodes, count, -1);
        int rightIndex = findSmallestNode(nodes, count, leftIndex);
        Node *parent = new Node(nodes[leftIndex], nodes[rightIndex]);

        // leftIndex에 부모 노드 삽입
        nodes[leftIndex] = parent;
        // rightIndex의 오른쪽 노드들을 윈쪽으로 한칸씩 이동
        for (int i = rightIndex; i < count - 1; i++)
        {
            nodes[i] = nodes[i + 1];
        }
        count--;
    }

    if (count == 1)
    {
        rootNode = nodes[0];
    }
}

void Tree::makeCodes(string codes[]) const
{
    collectCodes(rootNode, "", codes);
}

const Node *Tree::root() const
{
    return rootNode;
}

int Tree::findSmallestNode(Node *nodes[], int count, int skipIndex) const
{
    int smallestIndex = -1;

    // 전체 노드 중 skipIndex 를 제외한 가장 작은 node의 index 검색
    for (int i = 0; i < count; i++)
    {
        if (i == skipIndex)
        {
            continue;
        }

        if (smallestIndex == -1)
        {
            smallestIndex = i;
        }
        else if (nodes[i]->frequency < nodes[smallestIndex]->frequency)
        {
            smallestIndex = i;
        }
    }

    return smallestIndex;
}

void Tree::clear(Node *node)
{
    if (node == nullptr)
    {
        return;
    }

    clear(node->left);
    clear(node->right);
    delete node;
}

void Tree::collectCodes(const Node *node,
                        const string &prefix,
                        string codes[]) const
{
    if (node == nullptr)
    {
        return;
    }

    if (node->isLeaf())
    {
        // 문자가 1개일 때
        if (prefix.empty())
        {
            codes[int(node->value)] = "0";
        }
        else
        {
            codes[int(node->value)] = prefix;
        }
        return;
    }

    // 왼쪽 간선은 0, 오른쪽 간선은 1로 기록
    collectCodes(node->left, prefix + '0', codes);
    collectCodes(node->right, prefix + '1', codes);
}
