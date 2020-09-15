#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <typeinfo>

using namespace std;

void hangmanPlayer(const int& guesses, const string& answer, const int& wordlength, map<int, set<string>> dictionary);
map<string, set<string>> wordFamilies(set<string>& words, string currentWord, string userGuess);
void biggestFamily(map<string, set<string>> allfamilies);

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

int main() {
    map<int, set<string>> dictionary;
    string line;
    int wordLength;
    int guesses;
    string answer;

    cout << "Welcome to Hangman." << endl;

    ifstream dictFile("dictionary.txt");

    if(dictFile.is_open())
    {
        while(getline(dictFile, line))
        {
            int lineLenght = line.size();

            if (dictionary.find(lineLenght) != dictionary.end())
            {
                dictionary[lineLenght].insert(line);
            }
            else
            {
                set<string> words;
                words.insert(line);
                dictionary[lineLenght] = words;
            }
        }
        dictFile.close();
    }

    cout << "Please insert word lenght: ";
    cin >> wordLength;

    while (typeid(wordLength) != typeid(int) && dictionary.count(wordLength) == 0)
    {
        cout << "Please insert a valid word lenght: ";
        cin >> wordLength;
    }

    cout << "Insert the number of guesses you would like: ";
    cin >> guesses;

    while (guesses < 1)
    {
        cout << "Please insert a valid number of guesses: ";
        cin >> guesses;
    }

    cout << "Would you like to see the amount of remaining words? (y/n): ";
    cin >> answer;

    while (answer != "y" && answer != "n")
    {
        cout << "Please insert a valid option: ";
        cin >> answer;
    }

    hangmanPlayer(guesses, answer, wordLength, dictionary);

    return 0;
}

void hangmanPlayer(const int& guesses, const string& answer, const int& wordlength, map<int, set<string>> dictionary){

    string guessedLetters;
    int possibleWords = 0;
    string currentWord;
    string userGuess;
    set<string> words = dictionary[wordlength];

    for(int i = 0; i < wordlength; i++)
    {
        currentWord.append("-");
    }


    cout << "\nGuesses left: " << guesses << "\nAlready guessed letters: " << guessedLetters << "\nThe word so far: " << currentWord;

    if(answer == "y")
    {
        cout << "\nNumber of possible words left: " << possibleWords;
    }

    cout << "\nGuess a letter: ";
    cin >> userGuess;

    while (ALPHABET.find(userGuess) == ALPHABET.npos || userGuess.length() != 1)
    {
        if (guessedLetters.find(userGuess) != guessedLetters.npos)
        {
            cout << "You have already guessed this letter." << endl;
        }
        cout << "Please enter a (lower case) letter from the alphabet: ";
        cin >> userGuess;
    }
    wordFamilies(words, currentWord, userGuess);
}

map<string, set<string>> wordFamilies(set<string>& words, string currentWord, string userGuess){
    map<string, set<string>> families;
    string key = currentWord;


    for(string word : words){                       //För all aord av rätt längd
        if(word.find(userGuess) == word.npos){      //Om bokstaven inte finns i ordet
            if(families.count(currentWord) == 0){
                set<string> familySet;
                familySet.insert(word);
                families[currentWord] = familySet;
            }
            families[currentWord].insert(word);
        }
        else                                        //Om bokstaven finns i ordet:
        {
            for(int i = 0; i < word.length(); i++){     //Gå igenom ordet
                if(word[i] == userGuess[0])         //Om en bokstav = gissningen
                {
                    key[i] = userGuess[0];
                }
            }
            if(families.count(key) == 0){   //Om nyckeln inte redan finns i families
                set<string> familySet;
                familySet.insert(word);
                families[key] = familySet;  //Skapa en set med ordet och lägg in i families tsm med nyckeln
            }
            else
            {
                families[key].insert(word);     //Om nycken finns, lägg in ordet i dess set
            }
            key = currentWord;
        }
    }
    /*for(map<string, set<string>>::iterator it = families.begin(); it != families.end(); ++it){
        cout << it->first <<endl;
    }*/
    biggestFamily(families);
    return families;
}

void biggestFamily(map<string, set<string>> allfamilies) {
    set<string> biggestSet;
    int size = 0;
    for(map<string, set<string>>::iterator it = allfamilies.begin(); it != allfamilies.end(); ++it)
    {
    //cout << it->second.size() <<endl;

    if (size < it->second.size())
    {
        size = it->second.size();
    }
    }
    cout << size;
}
