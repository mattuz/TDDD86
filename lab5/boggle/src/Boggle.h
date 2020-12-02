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
    set<string>& getComputerwords();
    char getCubes();
    int getPlayerscore();
    Grid<char>& getCubesides();
    void setVisitedFalse();

    void printCubes();
    void shuffleCubes();
    void cubeSide();
    bool boardChoice(string &answer);
    bool checkRandomAnswer(string &answer);
    void playersOwnBoard(string &goodboardstring);
    int checkBoardString(string &letters);

    void findWordsOnBoard();
    bool isValidPath(string word, int row, int col);
    void explorePaths(string wordSoFar, int row, int col);
    bool isValidWord(string word);
    int wordCheck(string& word);
    void removeInvalidWords();
    bool isOnBoard(string word);
    //tuple neighbours(char array, int i, int j, int rowSize, int colSize);



    // TODO: decide the public member functions and declare them

private:
    // TODO: decide the private member variables/functions and declare them
    char cubes[16][6] = {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}};
    Lexicon dictionary;
    set<string> words;
    set<string> computerwords;
    Grid<char> cubesides = Grid<char>(4,4);
    Grid<bool> visited = Grid<bool>(4,4);
    int playerscore = 0;


};

#endif
