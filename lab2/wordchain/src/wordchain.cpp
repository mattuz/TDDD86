#include <fstream>
#include <iostream>
#include <string>
#include <queue>
//#include <deque>
#include <stack>
#include <set>

using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

void wordChain(const string& w1, const string& w2, const set<string>& dictionary);
void findNeighbours(stack<string>& currentStack, queue<stack<string>>& chains, const set<string>& dictionary, set<string>& usedWords);

int main() {
    string line;
    set<string> dictionary;
    string w1, w2;

    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;
    cout << "Please type two words: "<<endl;
    cin >> w1 >> w2;

    ifstream dictFile("dictionary.txt");

    if(dictFile.is_open())
    {
        while(getline(dictFile, line))
        {
            dictionary.insert(line);
        }
        dictFile.close();
    }

    wordChain(w1, w2, dictionary);

    return 0;
}

void wordChain(const string& w1, const string& w2, const set<string>& dictionary) {
    queue<stack<string>> chains;
    stack<string> stack1;
    set<string> usedWords;
    usedWords.insert(w1);
    stack1.push(w1);
    chains.push(stack1);

    while(!chains.empty())
    {
        stack<string> currentStack = chains.front();
        chains.pop();
        if (currentStack.top() == w2)
        {
            while(!currentStack.empty())
            {
                string stackstr = currentStack.top();
                cout << stackstr << " ";
                currentStack.pop();
            }
            cout << endl;
            break;
        }
        else
        {
            findNeighbours(currentStack, chains, dictionary, usedWords);
        }
    }
}

void findNeighbours(stack<string>& currentStack, queue<stack<string>>& chains, const set<string>& dictionary, set<string>& usedWords) {
    string word = currentStack.top();
    for(int i = 0; i < word.length(); i++)
    {
        for(int j = 0; j < ALPHABET.length(); j++)
        {

            string s (1,ALPHABET[j]);
            string tempWord = word;
            tempWord.replace(i, 1, s);
            if((dictionary.count(tempWord) == 1) && (usedWords.count(tempWord) == 0))
            {
                usedWords.insert(tempWord);
                stack<string> copyStack = currentStack;
                copyStack.push(tempWord);
                chains.push(copyStack);
            }
        }
    }
}
