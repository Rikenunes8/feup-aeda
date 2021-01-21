#include "packagingMachine.h"
#include <sstream>

PackagingMachine::PackagingMachine(int boxCap): boxCapacity(boxCap)
{}

unsigned PackagingMachine::numberOfBoxes() {
    return boxes.size();
}

unsigned PackagingMachine::addBox(Box& b1) {
    boxes.push(b1);
    return boxes.size();
}

HeapObj PackagingMachine::getObjects() const {
    return this->objects;
}

HeapBox PackagingMachine::getBoxes() const {
    return this->boxes;
}


// TODO
unsigned PackagingMachine::loadObjects(vector<Object> &objs) {
    unsigned nObjsLoaded = 0;
	vector<Object>::iterator it = objs.begin();
	while (it != objs.end()){
	    if (it->getWeight()<=boxCapacity) {
	        objects.push(*it);
	        it = objs.erase(it);
	        nObjsLoaded++;
	    }
	    else {
	        it++;
	    }
	}
	return nObjsLoaded;
}

// TODO
Box PackagingMachine::searchBox(Object& obj) {
    bool found = false;
	Box b("");
	priority_queue<Box> auxQueue;

	while (!boxes.empty()) {
	    b = boxes.top();
	    if (b.getFree() >= obj.getWeight()) {
	        boxes.pop();
	        found = true;
	        break;
	    }
	    else {
	        auxQueue.push(b);
	        boxes.pop();
	    }
	}
	while(!auxQueue.empty()) {
	    boxes.push(auxQueue.top());
	    auxQueue.pop();
	}
	if (found) return b;
	else return Box(boxCapacity);
}

bool inVector(vector<unsigned> &v, unsigned id) {
    for (auto e:v)
        if (e == id)
            return true;
    return false;
}
// TODO
unsigned PackagingMachine::packObjects() {
    vector<unsigned> ids;
    Object o(1, 0);
    Box b("");
    unsigned n = 0;
	while (!objects.empty()) {
	    o = objects.top();
	    b = searchBox(o);
	    if (!inVector(ids, b.getID())) {
	        ids.push_back(b.getID());
            n++;
	    }

	    objects.pop();
	    b.addObject(o);
	    boxes.push(b);
	}
	return n;
}

// TODO
string PackagingMachine::printObjectsNotPacked() const {
    priority_queue<Object> objs  = objects;
	if (objs.empty())
	    return "No objects!\n";
	stringstream ss;
	for (int _ = 0; _ < objects.size(); _++) {
        ss << objs.top() << endl;
        objs.pop();
	}
	return ss.str();
}

// TODO
Box PackagingMachine::boxWithMoreObjects() const {
	Box b(""), max("");
	int n = 0;
	if (boxes.empty())
	    throw MachineWithoutBoxes();
	HeapBox bxs = boxes;
    for (int i = 0; i < boxes.size(); i++) {
        b = bxs.top();
        bxs.pop();
        if (b.getSize() > n) {
            max = b;
            n = max.getSize();
        }
    }
	return max;
}

string PackagingMachine::printBoxesContent() const {
    priority_queue<Box> bxs  = boxes;
    if (boxes.empty())
        return "No objects!\n";
    stringstream ss;
    for (int _ = 0; _ < boxes.size(); _++) {
        ss << bxs.top().printContent() << endl;
        bxs.pop();
    }
    return ss.str();
}