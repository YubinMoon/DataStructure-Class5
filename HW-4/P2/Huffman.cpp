#include "Huffman.h"

#include <cstdlib>
#include <iostream>

using namespace std;

Huffman::Huffman()
{
    for (int i = 0; i < 256; i++)
    {
        frequencies[i] = 0;
        codeTable[i].clear();
    }
}

void Huffman::makeHuffmanCode(const string &text)
{
    // 각 문자의 빈도수 계산
    for (int i = 0; i < int(text.length()); i++)
    {
        int index = int(text[i]);
        frequencies[index]++;
    }

    tree.makeTree(frequencies);
    tree.makeCodes(codeTable);
}

string Huffman::encode(const string &text) const
{
    string result;

    // 생성된 codeTable에서 각 문자의 코드 추출
    for (int i = 0; i < int(text.length()); i++)
    {
        int index = int(text[i]);
        result += codeTable[index];
    }

    return result;
}

string Huffman::decode(const string &bits) const
{
    const Node *root = tree.root();
    if (root == nullptr)
    {
        return "";
    }

    string result;

    // 문자가 1개일 때
    if (root->isLeaf())
    {
        for (int i = 0; i < int(bits.length()); i++)
        {
            result += char(root->value);
        }
        return result;
    }

    const Node *current = root;
    for (char bit : bits)
    {
        // 비트를 하나씩 읽으며 트리를 탐색
        if (bit == '0')
        {
            current = current->left;
        }
        else if (bit == '1')
        {
            current = current->right;
        }

        if (current->isLeaf())
        {
            // 리프 노드에 도착하면 1개 문자 복원
            result += char(current->value);
            current = root;
        }
    }

    return result;
}

vector<WordCodeInfo> Huffman::selectedWordCodes(const string &text, int count) const
{
    vector<WordCodeInfo> result;
    vector<string> words = firstUniqueWords(text, count);

    for (int i = 0; i < int(words.size()); i++)
    {
        const string &word = words[i];
        string code = encode(word);

        WordCodeInfo info;
        info.word = word;
        info.huffmanCode = code;
        info.huffmanBits = int(code.length());
        info.asciiBits = int(word.length()) * 8;
        result.push_back(info);
    }

    return result;
}

int Huffman::encodedLength(const string &bits) const
{
    return int(bits.length());
}

int Huffman::asciiLength(const string &text) const
{
    return int(text.length()) * 8;
}

bool Huffman::isWordCharacter(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
    {
        return true;
    }
    if (ch >= 'a' && ch <= 'z')
    {
        return true;
    }
    if (ch >= '0' && ch <= '9')
    {
        return true;
    }
    return false;
}

vector<string> Huffman::firstUniqueWords(const string &text,
                                         int count)
{
    vector<string> words;
    string current;

    for (int i = 0; i < int(text.length()); i++)
    {
        char ch = text[i];
        if (isWordCharacter(ch))
        {
            current += ch;
            continue;
        }

        if (!current.empty())
        {
            bool alreadyExists = false;
            // 각 단어는 처음 등장한 것만 저장
            for (int j = 0; j < int(words.size()); j++)
            {
                if (words[j] == current)
                {
                    alreadyExists = true;
                }
            }

            if (!alreadyExists)
            {
                words.push_back(current);
                if (int(words.size()) == count)
                {
                    return words;
                }
            }
        }
        current.clear();
    }

    if (!current.empty())
    {
        bool alreadyExists = false;
        for (int i = 0; i < int(words.size()); i++)
        {
            if (words[i] == current)
            {
                alreadyExists = true;
            }
        }

        if (!alreadyExists)
        {
            words.push_back(current);
        }
    }

    return words;
}
