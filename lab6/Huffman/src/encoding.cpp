// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"
//#include "strlib.h"
// TODO: include any other headers you need

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
    // TODO: implement this function
    //typedef priority_queue<int, HuffmanNode, HuffmanNode> comp_type;

    //priority_queue<HuffmanNode*, vector<HuffmanNode>, int> nodequeue;
    //std::priority_queue<HuffmanNode, std::vector<HuffmanNode>, decltype(compare)> nodequeue(compare);
    auto compare = [](HuffmanNode* a, HuffmanNode* b) { return *a < *b; };
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, decltype(compare)> nodequeue(compare);
    HuffmanNode* node;
    HuffmanNode* root;
    for(auto& pair: freqTable){
        node = new HuffmanNode(get<0>(pair), get<1>(pair), nullptr, nullptr); //ev behövs inte nullptr skrivas ut
        nodequeue.push(node);
    }
    while(!nodequeue.empty()){ //det här är fel nu, tar nog den största och inte den minsta??? ska kombineras med hoffmannode <
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

map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    // TODO: implement this function
    map<int, string> encodingMap;
    return encodingMap;
}

void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    // TODO: implement this function
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    // TODO: implement this function
}

void compress(istream& input, obitstream& output) {
    // TODO: implement this function
}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function
}
