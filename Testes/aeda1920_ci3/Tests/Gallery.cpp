#include "Gallery.h"
#include <ostream>
using namespace std;

Gallery::Gallery(vector<Paint*> c): catalog(PaintCatalogItem("", "", 0, 0.00)), collection(c) {

}

vector<Paint*> Gallery::getCollection() const {
    return collection;
}

void Gallery::setCollection(vector<Paint*> c) {
    collection = c;
}

priority_queue<ExhibitionItem> Gallery::getPaintsToShow() const {
    return paintsToShow;
}
HashTableAuthorRecord Gallery::getAuthorRecords () const {
    return  authorRecords;
}

void Gallery::addAuthorRecord(AuthorRecord ar) {
    authorRecords.insert(ar);
}

void Gallery::generateCatalog() {
    catalog.makeEmpty();
    for(int i = 0; i < collection.size(); i++) {
        catalog.insert(collection[i]);
    }
}

BST<PaintCatalogItem> Gallery::getCatalog() const {
    return catalog;
}


void Gallery::prepareExhibition() {
    while( !paintsToShow.empty())
        paintsToShow.pop();
    for(int i = 0; i < collection.size(); i++) {
        ExhibitionItem ei(collection[i]);
        paintsToShow.push(ei);
    }
}

//-------------------------------------------------------------------------------

//TODO
vector<Paint*> Gallery::getPaintsBy(string a) const {
    vector<Paint*> tmp;
    for (iteratorBST<PaintCatalogItem> it = catalog.begin(); it != catalog.end(); it++) {
        if (it.operator*().getAuthor() == a)
            tmp.push_back(it.operator*().getPaint());
    }
    return tmp;
}

//TODO
vector<Paint*> Gallery::getPaintsBetween(int y1, int y2) const {
    vector<Paint*> tmp;
    for (iteratorBST<PaintCatalogItem> it = catalog.begin(); it != catalog.end(); it++) {
        if (it.operator*().getYear() >= y1 && it.operator*().getYear() <= y2)
            tmp.push_back(it.operator*().getPaint());
    }
    return tmp;
}

//TODO
bool Gallery::updateTitle(Paint* p, string tnew) {
    bool rem = false;
    for (iteratorBST<PaintCatalogItem> it = catalog.begin(); it != catalog.end(); it++) {
        if (it.operator*().getPaint()->getAuthor() == p->getAuthor() && it.operator*().getPaint()->getTitle() == p->getTitle()) {
            catalog.remove(it.operator*());
            p->setTitle(tnew);
            catalog.insert(PaintCatalogItem(p));
            rem = true;
        }
    }
    return rem;
}


//TODO
int Gallery::recordAvailablePainters() { //carrega a tabela de dispersao com AuthorRecords
    pair<HashTableAuthorRecord::iterator, bool> p;
    AuthorRecord a("");
    for (vector<Paint*>::iterator it = collection.begin(); it != collection.end(); it++) {
        p = authorRecords.insert(AuthorRecord((*it)->getAuthor()));
        if(!p.second) {
            a = *(p.first);
            a.addAvaliablePaint();
            authorRecords.erase(p.first);
            authorRecords.insert(a);
        }
    }
    return authorRecords.size();
}

//TODO
double Gallery::totalSells() const {
    double sell = 0;
    for (auto& elem:authorRecords) {
        sell += elem.getTotalSells();
    }
    return sell;
}
//TODO
double Gallery::sellPaint(string a, string t) {
    AuthorRecord tmp("");
    double sell = 0;
    for (vector<Paint*>::iterator it = collection.begin(); it != collection.end(); it++) {
        if ((*it)->getAuthor() == a && (*it)->getTitle() == t) {
            sell = (*it)->getPrice();
            tmp = *authorRecords.find(a);
            tmp.subAvailablePaint();
            tmp.setTotalSells(tmp.getTotalSells()+sell);
            authorRecords.erase(authorRecords.find(a));
            authorRecords.insert(tmp);
            collection.erase(it);
            break;
        }
    }
    return sell;
}

//TODO
vector<Paint*> Gallery::nBestExibition(int n, int maxPerYear) {  //escolhe as N mais caras pinturas, dos anos mais antigos, para realizar uma exposição
    vector<Paint*> tmpV;
    priority_queue<ExhibitionItem> tmpQ;
    int currentYear = 0, nYears = 0;
    while (n > 0 && !paintsToShow.empty()) {
        if (paintsToShow.top().getYear() == currentYear) {
            nYears++;
        }
        else {
            nYears = 0;
            currentYear = paintsToShow.top().getYear();
        }
        if (nYears < maxPerYear) {
            tmpV.push_back(paintsToShow.top().getPaint());
            paintsToShow.pop();
            n--;
        }
        else {
            tmpQ.push(paintsToShow.top());
            paintsToShow.pop();
        }
    }
    while (!tmpQ.empty()) {
        paintsToShow.push(tmpQ.top());
        tmpQ.pop();
    }
    return tmpV;
}

//TODO
int Gallery::itemExibitionOrder(string a, string t) {
    int pos = 1;
    priority_queue<ExhibitionItem> tmp = paintsToShow;
    while (!tmp.empty()) {
        if (tmp.top().getAuthor() == a && tmp.top().getTitle() == t)
            return pos;
        pos++;
        tmp.pop();
    }
    return 0;
}

