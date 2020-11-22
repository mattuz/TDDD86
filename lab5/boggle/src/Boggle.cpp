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
using namespace std;

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
            cout << cubes[i][j]; //TODO: Samma som nedan. Viktigaste är egentligen bara att vi löser så att denna också returnerar char/str.
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
        cout << cubes[i][0]; //TODO: Ta bort detta. Denna funktion kommer istället behöva returnera en char/str och så får vi printa i play..
    }
}

bool Boggle::boardChoice(string &answer) {
    answer = trim(toLowerCase(answer));
    if (startsWith(answer, 'y')) {
        shuffleCubes();
        printCubeSide(); //TODO: Ta bort denna, måste in i boggleplay
        return true;
    } else {
        return false;
    }
}

bool Boggle::checkRandomAnswer(string &answer) {
    if (!startsWith(answer, 'y') && !startsWith(answer, 'n')) {
        return false;
    } else {
        return true;
    }
}



void Boggle::playersOwnBoard(string &letters) {
    letters = trim(toUpperCase(letters));
    for (int i = 0; i < NUM_CUBES; i++) {
        cubes[i][0] = letters[i];
    }
}

int Boggle::checkBoardString(string &letters) {
    bool condition = true;

    for (unsigned int i = 0; i < letters.size(); i++) {
        if (ALPHABET.find(letters[i]) == string::npos) {
            condition = false;
            break;
        }
    }
    if (letters.size() != 16 && !condition) {
        condition = true;
        return 1;
    } else if (letters.size() != 16) {
        condition = true;
        return 2;
    } else if (!condition) {
        condition = true;
        return 3;
    } else {
        return 0;
    }
}
