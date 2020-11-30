// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace it with your own

#include <sstream>
#include <fstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include "math.h"

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
            visited[i][j] = false;
        }
    }
}

void Boggle::makeLexicon() {
    dictionary = *new Lexicon(DICTIONARY_FILE);
}

const Lexicon& Boggle::getDictionary() {
    return dictionary;
}


set<string>& Boggle::getWords() {
    return words;
}

char Boggle::getCubes(){
    return **cubes;
}

char& Boggle::getCubeSides() {
    return **cubesides;
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

void Boggle::cubeSide() {  //Converts the sides into a string that can be printed in boggleplay.
    for (int i = 0; i < NUM_CUBES; i++) {
        int r = int (round(i/4));
        cubesides[r][i%4] = cubes[i][0];
    }
}

bool Boggle::boardChoice(string &answer) { //Randomboard (y/n)?
    answer = trim(toLowerCase(answer));
    if (startsWith(answer, 'y')) {
        shuffleCubes();
        return true;
    } else {
        return false;
    }
}

bool Boggle::checkRandomAnswer(string &answer) { //validanswer (y/n)?
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
        playersOwnBoard(letters);
        return 0;
    }
}

int Boggle::wordCheck(string& word) {
    if (word.length() < 4) {
        return 1;

    } else if (words.count(word) != 0) {
        return 2;
    } else if (!dictionary.contains(word)) {

        return 3;
    } else {

        word = trim(toUpperCase(word));
        words.insert(word);

        return 0;
    }

}


/*tuple<int, int> Boggle::neighbours(char array, int i, int j, int rowSize, int colSize){
    Vector<tuple> neighbours;
    for (int row = i - 1; row <= i + 1 && row < rowSize; row++)
            for (int col = j - 1; col <= j + 1 && col < colSize; col++)
                if (row >= 0 && col >= 0){
                    tuple<int, int> t = make_tuple(i, j);
                    neighbours.push_back(t);
                }

    return neighbours;
}
*/


void Boggle::possibleWordsOnBoard() {

}

