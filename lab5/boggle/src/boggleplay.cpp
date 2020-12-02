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

string boardletters;


void printCubeSides(Boggle& boggle) {  //Always prints the first letter in "i" cube. Migh want to add randomness here as well if necessary.
    cout << "It's your turn!" << endl;
    for (int i = 0; i < 4 ; i++) {
        cout << endl;
        for (int j = 0; j < 4; j++) {
            cout << boggle.getCubesides().get(i, j);
        }
    }
    cout << endl;
}

void checkValidInputString(int& validcheck, Boggle& boggle) {
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
}

void playerWords(Boggle& boggle){
    boggle.setScoreZero();
    string word;
    getline(cin, word);

   while (word != ""){
       int checker = boggle.wordCheck(word);

       if (checker == 1) {
           clearConsole();
           printCubeSides(boggle);
           printPlayerWordList(boggle);

           cout << "Word is too short. Make sure it's atleast 4 letters: ";
           getline(cin, word);

       } else if (checker == 2) {
           clearConsole();
           printCubeSides(boggle);
           printPlayerWordList(boggle);

           cout << "You've already found this word. Make sure the word is unique: ";
           getline(cin, word);

       } else if (checker == 3) {
           clearConsole();
           printCubeSides(boggle);
           printPlayerWordList(boggle);

           cout << "Word is not in dictionary. Please enter a new word: ";
           getline(cin, word);

       } else if(checker == 4){
           clearConsole();
           printCubeSides(boggle);
           printPlayerWordList(boggle);

           boggle.setVisitedFalse();
           cout << "Word is not on the board. Please enter a new word: ";
           getline(cin, word);

       } else {
           clearConsole();
           printCubeSides(boggle);

           cout << "You've found a word!" << endl;
           printPlayerWordList(boggle);
           cout << "Type a word, or press ENTER to end your turn: ";

           getline(cin, word);
       }
    }
}

void printPlayerWordList(Boggle& boggle) {
    cout << "Your words (" << boggle.getWords().size() << "): ";
    cout << "{" << " ";
    for (auto& x : boggle.getWords()) {
        cout << x << " ";
    }
    cout << "}" << endl;
    cout<<"Your score: "<< boggle.getPlayerscore()<<endl;
}

void printComputerWordList(Boggle& boggle) {
    cout << "My words (" << boggle.getComputerwords().size() << "): ";
    cout << "{" << " ";
    for (auto& x : boggle.getComputerwords()) {
        cout << x << " ";
    }
    cout << "}" << endl;
    cout<<"My score: "<< boggle.getComputerscore()<<endl;

    cout << "Easy win :)" << endl;
}


//TODO: Funderar på om vi vill bryta ut funktioner som används nedan till hjälpfunktioner i boggleplay,
//så att det inte blir för mkt i playOnegGame
void playOneGame(Boggle& boggle) {
    boggle.getWords().clear();
    string randomboardanswer;
    boggle.getComputerwords().clear();

    cout << "Do you wish to generate a random board? (y/n): ";
    getline(cin, randomboardanswer);
    bool validinput = boggle.checkRandomAnswer(randomboardanswer);

    while(!validinput) {
        cout << "Please type a word that begins with 'y' or 'n'." << endl;
        getline(cin, randomboardanswer);
        validinput = boggle.checkRandomAnswer(randomboardanswer);
    }

    if (!boggle.boardChoice(randomboardanswer)) {
        cout << "Please enter 16 letters that you want to use: ";
        getline(cin, boardletters);
        int validcheck = boggle.checkBoardString(boardletters);

        checkValidInputString(validcheck, boggle);
    }
        boggle.cubeSide();
        printCubeSides(boggle);

        playerWords(boggle);
        boggle.findWordsOnBoard();

        printComputerWordList(boggle);




}

/*
 * Help functions
 */


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
