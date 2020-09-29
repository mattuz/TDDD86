#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <typeinfo>

using namespace std;

void hangmanPlayer(const int& guesses, const string& answer, string& currentWord, set<string>& words, string& guessedLetters);
map<string, set<string>> wordFamilies(set<string>& words, string& currentWord, string userGuess);
void biggestFamily(map<string, set<string>>& allfamilies, string& currentWord, set<string>& words);
bool wordFound(string currentWord);
void gameOver(set<string> words, string currentWord, string& newGame);

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

int main() {

    string newGame = "y";
    map<int, set<string>> dictionary;
    string line;


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

    while(newGame == "y"){

    string guessedLetters;
    int wordLength;
    int numberOfGuesses;
    string showRemainingWords;
    string wordSoFar;

    cout << "Welcome to Hangman." << endl;

    cout << "Please insert word lenght: ";
    cin >> wordLength;

    while (typeid(wordLength) != typeid(int) && dictionary.count(wordLength) == 0)
    {
        cout << "Please insert a valid word lenght: ";
        cin >> wordLength;
    }

    cout << "Insert the number of guesses you would like: ";
    cin >> numberOfGuesses;

    while (numberOfGuesses < 1)
    {
        cout << "Please insert a valid number of guesses: ";
        cin >> numberOfGuesses;
    }

    cout << "Would you like to see the amount of remaining words? (y/n): ";
    cin >> showRemainingWords;

    while (showRemainingWords != "y" && showRemainingWords != "n")
    {
        cout << "Please insert a valid option: ";
        cin >> showRemainingWords;
    }

    set<string> fittingWords = dictionary[wordLength];

    for(int i = 0; i < wordLength; i++)
    {
        wordSoFar.append("-");
    }

    while(numberOfGuesses > 0 && !wordFound(wordSoFar))
    {
        hangmanPlayer(numberOfGuesses, showRemainingWords, wordSoFar, fittingWords, guessedLetters);
        numberOfGuesses--;
    }

    gameOver(fittingWords, wordSoFar, newGame);

    }

    return 0;
}

void hangmanPlayer(const int& numberOfGuesses, const string& showRemainingWords,
                   string& wordSoFar, set<string>& fittingWords, string& guessedLetters){

    int possibleWords = fittingWords.size();
    string userGuess;

    cout << "\nGuesses left: " << numberOfGuesses << "\nAlready guessed letters: " << guessedLetters << "\nThe word so far: " << wordSoFar;

    if(showRemainingWords == "y")
    {
        cout << "\nNumber of possible words left: " << possibleWords;
    }

    cout << "\nGuess a letter: ";
    cin >> userGuess;

    while (ALPHABET.find(userGuess) == ALPHABET.npos || userGuess.length() != 1 || guessedLetters.find(userGuess) != guessedLetters.npos)
    {
        if (guessedLetters.find(userGuess) != guessedLetters.npos)
        {
            cout << "You have already guessed this letter." << endl;
        }

        cout << "Please enter a (lower case) letter from the alphabet: ";
        cin >> userGuess;

    }

    guessedLetters.append(userGuess);
    wordFamilies(fittingWords, wordSoFar, userGuess);

}

map<string, set<string>> wordFamilies(set<string>& fittingWords, string& wordSoFar, string userGuess){

    map<string, set<string>> wordFamilies;
    string key = wordSoFar;

    for(const string& word : fittingWords)
    {                                               //För all ord av rätt längd
        if(word.find(userGuess) == word.npos)       //Om bokstaven inte finns i ordet
        {
            if(wordFamilies.count(wordSoFar) == 0)
            {
                set<string> familySet;
                familySet.insert(word);
                wordFamilies[wordSoFar] = familySet;
            }

            wordFamilies[wordSoFar].insert(word);
        }
        else                                        //Om bokstaven finns i ordet:
        {
            for(int i = 0; i < word.length(); i++)
            {                                        //Gå igenom ordet
                if(word[i] == userGuess[0])         //Om en bokstav = gissningen
                {
                    key[i] = userGuess[0];
                }
            }

            if(wordFamilies.count(key) == 0)
            {                                      //Om nyckeln inte redan finns i families
                set<string> familySet;
                familySet.insert(word);
                wordFamilies[key] = familySet;  //Skapa en set med ordet och lägg in i families tsm med nyckeln
            }
            else
            {
                wordFamilies[key].insert(word);     //Om nycken finns, lägg in ordet i dess set
            }

            key = wordSoFar;

        }
    }

    biggestFamily(wordFamilies, wordSoFar, fittingWords);
    return wordFamilies;

}

void biggestFamily(map<string, set<string>>& wordFamilies, string& wordSoFar, set<string>& fittingWords) {

    string biggestKey;
    int size = 0;
    map<string, set<string>> tempMap;

    for(map<string, set<string>>::iterator it = wordFamilies.begin(); it != wordFamilies.end(); ++it) //Itererar genom familjen och kollar vilken som är störst
    {
        if (size < it->second.size())
        {
            size = it->second.size();
            biggestKey = it->first;
        }
    }

    fittingWords = wordFamilies[biggestKey];     //Kopierar sedan in den i en temporär map och skriver sedan över vår wordFamilies.
    tempMap[biggestKey] = fittingWords;
    wordFamilies = tempMap;
    wordSoFar = biggestKey;
}

void gameOver(set<string> wordLengthWords, string wordSoFar, string& newGame){

    string winningWord = *wordLengthWords.begin();

    if(wordFound(wordSoFar))
    {
        cout << "Congrats, you won! The word was: " << winningWord << endl;
    }
    else
    {
    cout << "You lost, the correct word was: " << winningWord << endl;
    }

    cout << "Do you want to play again? (y/n)" << endl;
    cin >> newGame;
}

bool wordFound (string currentWord){
    for(int i = 0; i < currentWord.length(); i++)
    {
        char a = currentWord[i];
        if(a == '-')
        {
            return false;
        }
    }

    return true;
}
