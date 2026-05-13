#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "Tree.h"

#include <string>
#include <vector>

using namespace std;

struct WordCodeInfo
{
    string word;
    string huffmanCode;
    int huffmanBits;
    int asciiBits;
};

class Huffman
{
public:
    Huffman();

    void makeHuffmanCode(const string &text);
    string encode(const string &text) const;
    string decode(const string &bits) const;

    // Info
    vector<WordCodeInfo> selectedWordCodes(const string &text, int count) const;
    int encodedLength(const string &bits) const;
    int asciiLength(const string &text) const;

private:
    Tree tree;
    int frequencies[256];
    string codeTable[256];

    static bool isWordCharacter(char ch);
    static vector<string> firstUniqueWords(const string &text,
                                           int count);
};

#endif
