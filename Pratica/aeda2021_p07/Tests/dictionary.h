#ifndef _DIC
#define _DIC
#include <string>
#include <fstream>
#include "bst.h"


class WordMeaning {
        string word;
        string meaning;
        public:
        WordMeaning(string w, string m): word(w), meaning(m) {}
        string getWord() const { return word; }
        string getMeaning() const { return meaning; }
        void setWord(string w) {word=w; }
        void setMeaning(string m) { meaning=m; }
        bool operator < (const WordMeaning &wm1) const;
};


class Dictionary
{
    BST<WordMeaning> words;
public:
    Dictionary(): words(WordMeaning("","")){};
    BST<WordMeaning> getWords() const;
    void readDictionary(ifstream &f);
    string searchFor(string word) const;
    bool correct(string word, string newMeaning);
    void print() const;
};


//TODO
class WordInexistent
{
    WordMeaning before;
    WordMeaning after;
public:
    WordInexistent(BST<WordMeaning> words, string word);
    string getWordBefore() const { return before.getWord(); }
    string getMeaningBefore() const { return before.getMeaning(); }
    string getWordAfter() const { return after.getWord(); }
    string getMeaningAfter() const { return after.getMeaning(); }
};

#endif