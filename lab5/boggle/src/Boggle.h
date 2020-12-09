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



    /*
     * Creates the lexicon which we use as a dictionary.
     */
    void makeLexicon();

    /*
     * Set the score to zero. Done before every game
     * (incase of player wanting to play multiple rounds).
     */
    void setScoreZero();

    /*
     * Getter for Words.
     */
    set<string>& getWords();

    /*
     * Getter for dictionary.
     */
    const Lexicon& getDictionary();

    /*
     * Getter for computerwords (the list of words that the computer "guesses").
     */
    set<string>& getComputerwords();

    /*
     * Getter for cubes (dices).
     */
    char getCubes();

    /*
     * Getter for player score.
     */
    int getPlayerscore();

    /*
     * Getter for computer score.
     */
    int getComputerscore();

    /*
     * Getter for cube sides (individual letters, not the whole dice).
     */
    Grid<char>& getCubesides();

    /*
     * Set list of visited to false.
     */
    void setVisitedFalse();

    /*
     * Shuffle the cubes, used to get different random boards each time.
     */
    void shuffleCubes();

    /*
     * Converts the side of a cube (dice) to a string and adds them together.
     * This is then printed in boggleplay.
     */
    void cubeSide();

    /*
     * Checks if the player wanted a random board or not. If yes,
     * it shuffles the cubes.
     */
    bool boardChoice(string &answer);

    /*
     * Checks if the answer to the question of randomboard or not
     * is valid. (Starts with y or n.)
     */
    bool checkRandomAnswer(string &answer);

    /*
     * Creates the board that the player put in. It swaps out the letter that
     * would've been printed from randomboard and uses that same function to print
     * the custom board.
     */
    void playersOwnBoard(string &goodboardstring);

    /*
     * Checks if the board string from the player is valid.
     */
    int checkBoardString(string &letters);

    /*
     * Checks if the input guess from the player is valid.
     * Is it on board, long enough, not guessed before etc.
     */
    int wordCheck(string& word);

    /*
     * Recursively explores all different paths available given a first letter
     * (from findWordsOnBoard). If the word is valid, it is added to the computers
     * list of guessed words.
     */
    void explorePaths(string wordSoFar, int row, int col);

    /*
     * Computers "starter" function for searching for words on the board.
     */
    void findWordsOnBoard();



    /*
     * Simple checker to make sure the computer word is correct (has lenght > 3, not guessed before etc.).
     */
    bool isValidWord(string word);

    /*
     * Starter function for recursively searching the board to see if a players
     * guessed word is on the board.
     */
    bool isOnBoard(string word);

    /*
     * Recursively searches through the board to see if the players input guess
     * is a valid option on the board.
     */
    bool isValidPath(string& word, int row, int col);




private:
    char cubes[16][6] = {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{}};
    Lexicon dictionary;
    set<string> words;
    set<string> computerwords;
    Grid<char> cubesides = Grid<char>(4,4);
    Grid<bool> visited = Grid<bool>(4,4);
    int playerscore;
    int computerscore;


};

#endif
