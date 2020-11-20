// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace it with your own

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"

static const string ALPHABET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

Boggle::Boggle() {
    for(int i = 0; i < NUM_CUBES; i++){
        //char s[6] = {};
        for(int j = 0; j < CUBE_SIDES; j++){
            cubes[i][j] = CUBES[i][j];
            }
    }
}

char Boggle::getCubes(){
    return **cubes;
}

//TODO: Kan vara bättre att bara dra ut for (int i... < NUM_CUBES...) och kör det som egen hjälpfunktion. Används mycket.

void Boggle::printCubes(){ //Mainly used for testing. Prints the entire cube, not the current side.
    for(int i = 0; i < NUM_CUBES; i++){
        if (i > 0) cout << ", ";
        for(int j = 0; j < CUBE_SIDES; j++) {
            cout << cubes[i][j];
        }
    }
}

void Boggle::shuffleCubes() {
    for (int i = 0; i < NUM_CUBES; i ++) {
        shuffle(cubes[i], 6);
    }
}

void Boggle::printCubeSide() {  //Always prints the first letter in "i" cube. Migh want to add randomness here as well if necessary.
    for (int i = 0; i < NUM_CUBES; i++) {
        if (i == 4 || i == 8 || i == 12) cout << endl;
        cout << cubes[i][0];
    }
}

void Boggle::boardChoice() {
    cout << "Do you wish to generate a random board? (y/n): ";
    int check = 0;
    while (check == 0) {
        string answer;
        getline(cin, answer);
        answer = trim(toLowerCase(answer));
        if (startsWith(answer, 'y')) {
            shuffleCubes();
            printCubeSide();
            check = 1;
        } else if (startsWith(answer, 'n')) {
            playersOwnBoard();
            check = 1;
        } else {
        cout << "Please type a word that begins with 'y' or 'n'." << endl;
        }
    }
}

void Boggle::playersOwnBoard() {
    cout << "Please enter 16 letters that you want to use: ";
    int check = 0;
    while (check == 0) {
        string letters;
        getline(cin, letters);
        for (unsigned int i = 0; i < letters.size(); i++) {
           /* if (ALPHABET.find(letters[i])) {
                Ska typ kolla om den kan hitta bokstaven i letters i Alphabet.. npos verkar inte funka :(
            }*/
        }


    }
}
