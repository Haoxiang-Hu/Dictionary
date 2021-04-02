#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

class Dictionary{
public:
    Dictionary();
    void LoadDictionaryFile(string filename);
    void AddWord(string word);
    bool IsWord(string word);
    bool IsPrefix(string word);
    void SaveDictionaryFile(string filename);
    void MakeEmpty();
    void test();


    struct Node{
        Node* chars[26];
        bool isWord;

        Node(){
            isWord = false;
            for(int i=0; i<26; i++){
                chars[i] = nullptr;
            }
        }
    };

    Node* root;
    int numWords = 0;
    void SaveDictionaryHelper(Node* curr, string currPrefix, ofstream& outFile);
    void destroyHelper(Node * thisTree);
};

Dictionary ::Dictionary() {
    root = new Node();
}

void Dictionary:: LoadDictionaryFile(string filename)
{
    ifstream f(filename.c_str());
    if(!f.is_open()){
        cout << "file not found" << endl;
    }
    string line;
    while(!f.eof()){
        getline(f,line);
        int start = 0;
        int end = line.find(" ");
        string word;
        while(end != string::npos){
            word = line.substr(start, end-start);
            cout << word << endl;
            AddWord(word);
            start = end + 1;
            end = line.find(" ", start);
        }
        word = line.substr(start, end);
        cout << word << endl;
        AddWord(word);
    }
}

void Dictionary:: AddWord(string word){
    Node* curr = new Node();
    curr = root;
    for(int i=0; i<word.length(); i++){
        char c = word[i];
        if((c-'a')<0 || (c-'z')>0){
            throw "wrong";
        }
        else{
            if (curr->chars[c-'a'] == nullptr){
                Node* newNode = new Node();
                curr->chars[c-'a'] = newNode;
            }
        }
        curr = curr->chars[c-'a'];
    }
    curr->isWord = true;
}

bool Dictionary::IsWord(string word) {
    Node* curr = new Node();
    curr = root;
    for(int i=0; i<word.length(); i++){
        char c = word[i];
        if((c-'a')<0 || (c-'z')>0){
            return false;
        }
        else{
            if(curr->chars[c-'a']== nullptr){
                return false;
            }
            curr = curr->chars[c-'a'];
        }
    }

    return (curr!=NULL && curr->isWord==true);
}

bool Dictionary::IsPrefix(string word) {
    Node* curr = new Node;
    curr = root;
    for(int i=0; i<word.length(); i++){
        char c = word[i];
        if((c-'a')<0 || ((int)c-(int)'z')>0){
            return false;
        }
        else{
            if(curr->chars[(int)c-(int)'a'] == nullptr){
                cout << "curr->isWord = " << curr->isWord << endl;
                return curr->isWord;
            }
            curr = curr->chars[c-'a'];
        }
    }
    cout << "curr->isWord = " << curr->isWord << endl;
    return curr->isWord;
}
void Dictionary::SaveDictionaryFile(string filename) {

    ofstream myfile;
    myfile.open(filename.c_str());
    if(!myfile){
        throw (filename + "failed to open");
    }

    Node *temp = root;
    string word;
    SaveDictionaryHelper(temp, word, myfile);
}



void Dictionary::SaveDictionaryHelper(Dictionary::Node *curr, string currPrefix, ofstream &outFile) {
    if(curr -> isWord){
        outFile << currPrefix;
        outFile << endl;
    }

    for(int i=0; i<26; i++){
        if(curr->chars[i] != nullptr){
            SaveDictionaryHelper(curr->chars[i], currPrefix+(char)(97+i), outFile);
        }
    }
}


void Dictionary ::test() {
    Node * curr = new Node();
    curr = root;
    string word = "                                                               ";
    for(int i=0; i<26; i++){
        if (curr->chars[i] != nullptr){
            word[i] = char ((int)i + (int)'a');

            if(curr->isWord){
                cout << word << endl;
            }
        }
    }

}

void MakeEmpty();
void Dictionary::destroyHelper(Dictionary::Node *thisTree) {
    if(thisTree->isWord){
        delete thisTree;
        numWords--;
        cout << numWords <<endl;
        return;
    }

    for(int i=0; i<26; i++){
        if(thisTree->chars[i] != nullptr) {
            cout << i << endl;
            cout << thisTree->chars[i] << endl;
            destroyHelper(thisTree->chars[i]);
        }
    }
}



int main(){
//    Dictionary text;
//    text.LoadDictionaryFile("dictionary.txt");
//    text.SaveDictionaryFile("text3.txt");
    string word;
    word = word + 'a';
    word = word + 'b';
    cout << word << endl;


    return 0;
}