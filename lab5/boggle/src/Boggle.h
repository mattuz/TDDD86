// This is the .h file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header and replace it with your own

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "vector.h"
#include "grid.h"
#include <set>
#include "lexicon.h"
#include <tuple>
// TODO: include any other header files you need

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;


    Boggle();
    set<string>& getWords();
    void makeLexicon();
    const Lexicon& getDictionary();

    char getCubes();
    Grid<char>& getCubeSides();

    void printCubes();
    void shuffleCubes();
    void cubeSide();
    bool boardChoice(string &answer);
    bool checkRandomAnswer(string &answer);
    void playersOwnBoard(string &goodboardstring);
    int checkBoardString(string &letters);

    void possibleWordsOnBoard();
    bool isValidPath(string word, int row, int col);

    int wordCheck(string& word);
    void removeInvalidWords();
    //tuple neighbours(char array, int i, int j, int rowSize, int colSize);



    // TODO: decide the public member functions and declare them

private:
    // TODO: decide the private member variables/functions and declare them
    char cubes[16][6] = {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}};
    Lexicon dictionary;
    set<string> words;
    Grid<char> cubesides = Grid<char>(4,4);
    bool visited[4][4] = {{},{},{},{}};
    int playerscore;


};

#endif
