/*
 * TDDD86 Boggle
 * This file declares required function prototypes that are defined in
 * our provided bogglemain.cpp and your boggleplay.cpp that you will write.
 * See the respective .cpp files for implementation comments for each function.
 * Please do not modify this provided file.
 */

#ifndef _bogglemain_h
#define _bogglemain_h

#include "Boggle.h"
#include <string>
using namespace std;

void intro();

/*
 * Prints the "dice roll" that we got. This displays the board.
 */
void printCubeSides(Boggle& boggle);

/*
 * I/O handling for checking if the input string of custom board is correct.
 */
void checkValidInputString(int& validcheck);

/*
 * I/O handling for checking if the guessed word input from player is valid.
 */
void playerWords(Boggle& boggle);

/*
 * Prints the playes guesses.
 */
void printPlayerWordList(Boggle& boggle);

/*
 * Prints the computers guesses.
 */
void printComputerWordList(Boggle& boggle);

/*
 * The functions below were given with the assignment.
 */
void playOneGame(Boggle& boggle);
bool yesOrNo(string prompt);
void clearConsole();

#endif
