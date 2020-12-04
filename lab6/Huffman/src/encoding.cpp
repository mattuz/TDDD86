// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"
//#include "strlib.h"
// TODO: include any other headers you need

string stringOfBinaries = "";


map<int, int> buildFrequencyTable(istream& input) {
    map<int, int> freqTable;
    char c;
    
    while(input.get(c)){
        map<int, int>::iterator it = freqTable.find(c);
        if (it != freqTable.end()){
            freqTable.at(c)++;
        }
        else {
            freqTable.insert(pair<int, int>(c,1));
        }
    }
    freqTable.insert(pair<int, int>(PSEUDO_EOF,1));

    return freqTable;
}

HuffmanNode* buildEncodingTree(const map<int, int> &freqTable) {
    auto compare = [](HuffmanNode* a, HuffmanNode* b) { return *a < *b; };
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, decltype(compare)> nodequeue(compare);
    HuffmanNode* node;
    HuffmanNode* root;

    for(auto& pair: freqTable){
        node = new HuffmanNode(get<0>(pair), get<1>(pair), nullptr, nullptr); //ev behövs inte nullptr skrivas ut
        nodequeue.push(node);
    }
    while(!nodequeue.empty()){
        if(nodequeue.size() > 1){
            HuffmanNode* leftchild = nodequeue.top();
            nodequeue.pop();
            HuffmanNode* rightchild = nodequeue.top();
            nodequeue.pop();
            node = new HuffmanNode(NOT_A_CHAR, leftchild->count + rightchild->count, leftchild, rightchild);
            nodequeue.push(node);

        } else {
            root = nodequeue.top();
            nodequeue.pop();
        }
    }
    return root;
}

map<int, string> buildEncodingMap(HuffmanNode*& encodingTree) {
    map<int, string> encodingMap;

    if (encodingTree->isLeaf()) {
        encodingMap.insert(pair<int, string>(encodingTree->character, stringOfBinaries));
    }

    else if (!encodingTree->isLeaf()) {
        if (encodingTree->zero != nullptr) { //Vänster
            stringOfBinaries += "0";
            encodingMap = mergeMaps(encodingMap, buildEncodingMap(encodingTree->zero));
            stringOfBinaries.erase(stringOfBinaries.size()-1);
        }
        if (encodingTree->one != nullptr) { //Höger
            stringOfBinaries += "1";
            encodingMap = mergeMaps(encodingMap, buildEncodingMap(encodingTree->one));
            stringOfBinaries.erase(stringOfBinaries.size()-1);
        }

    }

    return encodingMap;
}

map<int, string> mergeMaps(map<int, string> m1, map<int, string> m2) {
    for (auto x : m2) {
        m1.insert(x);
    }
    return m1;
}

void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    char c;


    while(input.get(c)) {

        for (auto number : encodingMap.at(c)) {
            if (number == '0') {
                //cout << '0';
                output.writeBit(0);
            } else {
                output.writeBit(1);
                //cout << '1';
            }
        }
    }
    for (auto number : encodingMap.at(PSEUDO_EOF)) {
        if (number == '0') {
            output.writeBit(0);
            //cout << '0';

        } else {
            output.writeBit(1);
            //cout << '1';

        }
    }
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    HuffmanNode* node = encodingTree;

    while(input.readBit()) {
        if (input.readBit() == 0) {
            node = node->zero;
            if (node->isLeaf()) {
                output.put(node->character);
                node = encodingTree;
            }
        } else if (input.readBit() == 1) {
            node = node->one;
            if (node->isLeaf()) {
                output.put(node->character);
                node = encodingTree;

        } else {
            break;
            }
        }
    }
}

void compress(istream& input, obitstream& output) {
    // TODO: implement this function
    unsigned int i = 0;
    map<int, int> freqTable;
    HuffmanNode* encodingTree;
    map<int, string> encodingMap;

    freqTable = buildFrequencyTable(input);
    encodingTree = buildEncodingTree(freqTable);
    encodingMap = buildEncodingMap(encodingTree);
    //Lägg in headern. Lägg in map i output
    output.put('{');
    cout << '{';

    for (auto x : freqTable) {
        string first = to_string(x.first);
        for (unsigned int i = 0; i < first.size(); i++) {
            output.put(first[i]);
        }

        i++;
        cout << x.first << ':' << x.second;
        output.put(':');

        string second = to_string(x.second);
        for (unsigned int i = 0; i < second.size(); i++) {
            output.put(second[i]);
        }
        if (i != freqTable.size()) {
            cout << ','<< ' ';
            output.put(',');
            output.put(' ');
        }

    }
    cout << '}' << endl;
    output.put('}');
    input.clear();
    input.seekg(0, ios::beg);
    encodeData(input, encodingMap, output);
    freeTree(encodingTree);


}




void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
    map<int, int> freqTable;
    char c;

    while (input.get(c)) {
        if (c == '}') {
            break;
        }
    }
}

void freeTree(HuffmanNode* node) {
    if (node->zero == nullptr && node->one == nullptr) {
        delete node;
    } else {
        if (node->zero != nullptr) {
            freeTree(node->zero);
        }
        if (node->one != nullptr) {
            freeTree(node->one);
        }
    }
}
