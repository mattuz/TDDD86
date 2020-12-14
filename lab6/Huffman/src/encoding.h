/*
 * TDDD86 Huffman Encoding
 * This file declares the functions that you will need to write in this
 * assignment for your Huffman Encoder in huffmanencoding.cpp.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 */

#ifndef _encoding_h
#define _encoding_h

#include <iostream>
#include <string>
#include <map>
#include <queue>
#include "bitstream.h"
#include "HuffmanNode.h"
#include "strlib.h"

using namespace std;

/*
 * Puts the charachters from the input into a table, along with their frequencys.
 */
map<int, int> buildFrequencyTable(istream& input);

/*
 * Creates an encoding tree from a frequency table.
 */
HuffmanNode* buildEncodingTree(const map<int, int>& freqTable);

/*
 * Creates an encodingmap from an encoding tree.
 */
map<int, string> buildEncodingMap(HuffmanNode*& encodingTree);

/*
 * Handels the recursion in buildEncodingMap().
 */
map<int, string> encodingMapRecursion(HuffmanNode*& encodingTree, map<int, string>& encodingMap, string& stringOfBinaries);

/*
 * Reads characters from the input and trandlates into bits och zeros and ones using an encoding map.
 */
void encodeData(istream& input, const map<int, string>& encodingMap, obitstream& output);

/*
 * Reads bits one by one from the input and translates into characters using an encodingtree.
 */
void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output);

/*
 * Compresses the input and creates a header containing the corresponding frequency table.
 * Input is characters, output is bits of zeros and ones.
 */
void compress(istream& input, obitstream& output);

/*
 * Decodes the input, using the frequency table in its header.
 * Input is bits of zeros and ones, output is characters.
 */
void decompress(ibitstream& input, ostream& output);

/*
 * Deletes the tree where node is the root.
 */
void freeTree(HuffmanNode* node);


#endif
