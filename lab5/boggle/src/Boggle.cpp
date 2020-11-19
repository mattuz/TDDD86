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

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

Boggle::Boggle() {
    cout<<"o/"<<endl;
    for(int i = 0; i < NUM_CUBES; i++){
        //char s[6] = {};
        for(int j = 0; j < CUBE_SIDES; j++){
            cubes[i][j] = CUBES[i][j];
            //cout<<CUBES[i]<<" "<< CUBES[i][j]<<endl;
            //cout<<cubes[i]<<" "<< cubes[i][j]<<endl;

            }
        //cubes[i] = *s;
        //cout<<cubes[i]<<endl;
    }
}

char Boggle::getCubes(){
    return **cubes;
}

void Boggle::printCubes(){
    for(int i = 15; i < NUM_CUBES; i++){
            cout << cubes[14]<<"\n";
            }
}
// TODO: implement the members you declared in Boggle.h
