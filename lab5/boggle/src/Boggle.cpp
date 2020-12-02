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

Grid<char>& Boggle::getCubesides() {
    return cubesides;
}

set<string>& Boggle::getComputerwords(){
    return computerwords;
}
int Boggle::getPlayerscore(){
    return playerscore;
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
void Boggle::setVisitedFalse(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            visited.set(i,j,false);
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
        cubesides.set(r, i%4, cubes[i][0]);
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
    } else if(!isOnBoard(word)){
        return 4;
    }else {

        word = trim(toUpperCase(word));
        words.insert(word);
        playerscore += (word.size()-3);

        return 0;
    }

}

bool Boggle::isValidWord(string word){
    return(word.length() > 3 && dictionary.contains(word) && words.count(word) == 0 && computerwords.count(word) == 0);

}
void Boggle::explorePaths(string wordsofar, int row, int col){

    if(isValidWord(wordsofar)){
        computerwords.insert(wordsofar);
    }

    for (int i = row - 1; i <= row + 1 && i < 4; i++){
        for (int j = col - 1; j <= col + 1 && j < 4; j++){
            if (i >= 0 && j >= 0 && !(i == row && j == col) && !visited.get(i,j)){
                wordsofar+=cubesides.get(i, j);

                if(dictionary.containsPrefix(wordsofar)){
                    visited.set(i, j, true);
                    explorePaths(wordsofar, i, j);
                }
                wordsofar.erase(wordsofar.size()-1);
                visited.set(i,j,false);
            }
        }
    }
}

void Boggle::findWordsOnBoard(){
    string wordsofar;

    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++){
            string firstletter;
            firstletter += cubesides.get(row, col);
            setVisitedFalse();
            if(dictionary.containsPrefix(firstletter)){
                visited.set(row, col, true);
                wordsofar = "";
                wordsofar += cubesides.get(row, col);
                explorePaths(wordsofar, row, col);
            }
        }
    }
    setVisitedFalse();
}

bool Boggle::isOnBoard(string word){
    word = trim(toUpperCase(word));
    int present = 0;
    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++){
            if(word[0] == cubesides.get(row, col)){
                visited.set(row, col, true);
                string newword = word;
                newword.erase(0,1);
                if(isValidPath(newword, row, col)){
                    present++;
                }
            }
        }
    }
    return present > 0;
}

bool Boggle::isValidPath(string word, int row, int col){ //TODO for-loop i boggleplay
    string w = word;
    if(word == ""){
        setVisitedFalse();
        return true;
    }
    for (int i = row - 1; i <= row + 1 && i < 4; i++){
        for (int j = col - 1; j <= col + 1 && j < 4; j++){
            if (i >= 0 && j >= 0 && !(i == row && j ==col) && !visited.get(i,j)){

                if(word[0] == cubesides.get(i, j)){
                    visited.set(i, j, true);
                    w.erase(0,1);

                    return isValidPath(w, i, j);
                }
            }
        }
    }
    setVisitedFalse();
    return false;
}



