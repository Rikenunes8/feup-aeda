#include <iostream>
#include <string>
#include <fstream>
#include "dictionary.h"
#include "bst.h"

using namespace std;

BST<WordMeaning> Dictionary::getWords() const {
    return words;
}

//TODO
bool WordMeaning::operator < (const WordMeaning &wm1) const {
    return word < wm1.getWord();
}

//TODO
void Dictionary::readDictionary(ifstream &f)
{
    string word;
    string meaning;
    while (!f.eof()) {
        getline(f, word);
        getline(f, meaning);
        words.insert(WordMeaning(word, meaning));
    }
}

//TODO
string Dictionary::searchFor(string word) const
{
    WordMeaning wm(word, "");
    wm = words.find(wm);
    if (wm.getWord() == "") {
        throw WordInexistent(words, word);
    }
    else {
        return wm.getMeaning();
    }

}

//TODO
bool Dictionary::correct(string word, string newMeaning)
{
    WordMeaning wm(word, newMeaning);
    WordMeaning aux("", "");
    aux = words.find(wm);
    if (aux.getWord() == "") {
        words.insert(wm);
        return false;
    }
    else {
        words.remove(wm);
        words.insert(wm);
        return true;
    }

}

//TODO
void Dictionary::print() const
{
    BST<WordMeaning> copy = words;
    WordMeaning wm("", "");
    while (!copy.isEmpty()) {
        wm = copy.findMin();
        cout << wm.getWord() << endl;
        cout << wm.getMeaning() << endl;
        copy.remove(wm);
    }
}

WordInexistent::WordInexistent(BST<WordMeaning> words, string word):before("", ""), after("", "") {
    cout << word << endl;
    iteratorBST<WordMeaning> it = words.begin();
    while (it.operator*().getWord() < word) {
        before = it.operator*();
        it++;
        if (it == words.end()) break;
        after = it.operator*();
    }

}

