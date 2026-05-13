#include "Huffman.h"

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string readParagraph(const string &path)
{
    ifstream input(path);
    if (!input)
    {
        cerr << "Error: Cannot open " << path << '\n';
        exit(1);
    }

    ostringstream buffer;
    buffer << input.rdbuf();
    return buffer.str();
}

int main()
{
    const string paragraph = readParagraph("paragraph.txt");
    if (paragraph.empty())
    {
        cerr << "Error: paragraph.txt is empty.\n";
        return 1;
    }

    Huffman huffman;
    huffman.makeHuffmanCode(paragraph);

    const string encoded = huffman.encode(paragraph);
    const string decoded = huffman.decode(encoded);

    cout << "Selected 5 word Huffman codes\n";
    cout << left << setw(18) << "Word"
         << right << setw(14) << "Huffman bits"
         << setw(12) << "ASCII bits"
         << "  Huffman code\n";

    for (const WordCodeInfo &info : huffman.selectedWordCodes(paragraph, 5))
    {
        cout << left << setw(18) << info.word
             << right << setw(14) << info.huffmanBits
             << setw(12) << info.asciiBits
             << "  " << info.huffmanCode << '\n';
    }

    const int huffmanBits = huffman.encodedLength(encoded);
    const int asciiBits = huffman.asciiLength(paragraph);
    double ratio = 0.0;
    if (asciiBits != 0)
    {
        // 비율이 낮을수록 ASCII보다 적은 비트를 사용한 것이다.
        ratio = double(huffmanBits) / asciiBits * 100.0;
    }

    cout << "\nTotal length comparison\n";
    cout << "Huffman bits: " << huffmanBits << '\n';
    cout << "ASCII bits:   " << asciiBits << '\n';
    cout << "Ratio:        " << fixed << setprecision(2)
         << ratio << "%\n\n";

    cout << "Decode check: ";
    if (decoded == paragraph)
    {
        cout << "PASS\n";
    }
    else
    {
        cout << "FAIL\n";
    }

    return 0;
}
