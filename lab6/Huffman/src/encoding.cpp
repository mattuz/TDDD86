#include "encoding.h"

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
    string stringOfBinaries = "";

    return encodingMapRecursion(encodingTree, encodingMap, stringOfBinaries);
}

map<int, string> encodingMapRecursion(HuffmanNode*& encodingTree, map<int, string>& encodingMap, string& stringOfBinaries){

    if (encodingTree->isLeaf()) {
        encodingMap.insert(pair<int, string>(encodingTree->character, stringOfBinaries));
    }

    else if (!encodingTree->isLeaf()) { //Kan skrivas som else
        if (encodingTree->zero != nullptr) { //Vänster
            stringOfBinaries += "0";
            encodingMap = encodingMapRecursion(encodingTree->zero, encodingMap, stringOfBinaries);
            stringOfBinaries.erase(stringOfBinaries.size()-1);
        }
        if (encodingTree->one != nullptr) { //Höger
            stringOfBinaries += "1";
            encodingMap = encodingMapRecursion(encodingTree->one, encodingMap, stringOfBinaries);
            stringOfBinaries.erase(stringOfBinaries.size()-1);
        }

    }
    return encodingMap;
}


void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    char c;


    while(input.get(c)) {

        for (auto number : encodingMap.at(c)) {
            if (number == '0') {
                output.writeBit(0);
            } else {
                output.writeBit(1);
            }
        }
    }
    for (auto number : encodingMap.at(PSEUDO_EOF)) {
        if (number == '0') {
            output.writeBit(0);

        } else {
            output.writeBit(1);

        }
    }
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    HuffmanNode* node = encodingTree;
    int bit = input.readBit();

    while(bit != -1) {
        if (bit == 0) {
            node = node->zero;
            if (node->isLeaf()) {
                output.put(node->character);
                node = encodingTree;
            }
        } else if (bit == 1) {
            node = node->one;
            if (node->isLeaf()) {
                output.put(node->character);
                node = encodingTree;
            }
        }
        bit = input.readBit();
    }
}

void compress(istream& input, obitstream& output) {
    unsigned int i = 0;
    map<int, int> freqTable;
    HuffmanNode* encodingTree;
    map<int, string> encodingMap;

    freqTable = buildFrequencyTable(input);
    encodingTree = buildEncodingTree(freqTable);
    encodingMap = buildEncodingMap(encodingTree);
    output.put('{');

    for (auto x : freqTable) {
        string first = to_string(x.first);
        for (unsigned int i = 0; i < first.size(); i++) {
            output.put(first[i]);
        }

        i++;
        output.put(':');

        string second = to_string(x.second);
        for (unsigned int i = 0; i < second.size(); i++) {
            output.put(second[i]);
        }
        if (i != freqTable.size()) {
            output.put(',');
            output.put(' ');
        }

    }
    output.put('}');
    input.clear();
    input.seekg(0, ios::beg);
    encodeData(input, encodingMap, output);
    freeTree(encodingTree);


}




void decompress(ibitstream& input, ostream& output) {
    map<int, int> freqTable;
    HuffmanNode* encodingTree;
    char c;
    char lastC;
    string key;
    string value;
    bool isKey = false;
    bool isValue = false;

    while (input.get(c)) {
        if( c !=' ' && c != '{' && c != ',' && c != ':' && c != '}'){

            if((lastC == '{' || lastC == ' ') || isKey){
                isKey = true;
                key += c;
            }
            if(lastC == ':' || isValue){
                isKey = false;
                isValue = true;
                value += c;
            }

        } else if(c == ',' || c == '}'){
            isValue = false;
            freqTable.insert(pair<int, int>(stringToInteger(key), stringToInteger(value)));
            key = "";
            value = "";
            if(c == '}'){
                break;
            }

        } else if(c == ':'){
            isKey = false;
        }

        lastC = c;
    }

    encodingTree = buildEncodingTree(freqTable);
    decodeData(input, encodingTree, output);
    freeTree(encodingTree);
}

void freeTree(HuffmanNode* node) { //förenkla, node ska alltid deletas

    if (node->zero == nullptr && node->one == nullptr) {
        delete node;
    } else {
        freeTree(node->zero);
        freeTree(node->one);
        delete node;
    }
}
