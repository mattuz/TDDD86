// You will edit and turn in this CPP file.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace with your own

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"

// TODO: include any other header files you need

/*
 * Plays one game of Boggle using the given boggle game state object.
 */

//TODO: Funderar på om vi vill bryta ut funktioner som används nedan till hjälpfunktioner i boggleplay,
//så att det inte blir för mkt i playOnegGame
void playOneGame(Boggle& boggle) {
    string randomboard;
    string boardletters;

    cout << "Do you wish to generate a random board? (y/n): ";
    getline(cin, randomboard);
    bool validinput = boggle.checkRandomAnswer(randomboard);
    while(!validinput) {
        cout << "Please type a word that begins with 'y' or 'n'." << endl;
        getline(cin, randomboard);
        validinput = boggle.checkRandomAnswer(randomboard);
    }

    if (!boggle.boardChoice(randomboard)) {
        cout << "Please enter 16 letters that you want to use: ";
        getline(cin, boardletters);
        int validcheck = boggle.checkBoardString(boardletters);
        while (validcheck != 0) {
            if (validcheck == 1) {
                cout << "Please enter 16 letters from the alphabet: ";
                getline(cin, boardletters);
                validcheck = boggle.checkBoardString(boardletters);
            } else if (validcheck == 2) {
                cout << "Make sure you insert 16 letters: ";
                getline(cin, boardletters);
                validcheck = boggle.checkBoardString(boardletters);
            } else {
                cout << "Make sure you only insert letters: ";
                getline(cin, boardletters);
                validcheck = boggle.checkBoardString(boardletters);
            }
        }
        boggle.playersOwnBoard(boardletters);
        boggle.printCubeSide();
    }
}

/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}
