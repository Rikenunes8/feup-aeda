#include "Warehouse.h"
#include <algorithm>

Warehouse::Warehouse()  {
}

queue<ThinTallBox> Warehouse::getBoxes() {
	return boxes;
}

queue<Object> Warehouse::getObjects() {
    return objects;
}

void Warehouse::setBoxes(queue<ThinTallBox> q) {
    while (!q.empty()) {
        boxes.push(q.front());
        q.pop();
    }
}

void Warehouse::addObject(Object o1) {
    objects.push(o1);
}


int Warehouse::InsertObjectsInQueue(vector <Object> obj){
    sort(obj.begin(), obj.end());
    for (auto o:obj)
        addObject(o);
    return obj.size();
}

Object Warehouse::RemoveObjectQueue(int maxSize){
    Object o;
    bool flag = true;
    int size=objects.size();
    for (size_t i = 0; i<size;i++) {
        if (objects.front().getSize() <= maxSize && flag) {
            o = objects.front();
            objects.pop();
            flag = false;
        }
        else {
            objects.push(objects.front());
            objects.pop();
        }
    }
    if (objects.size() == size) {
        o.setName("dummy");
        o.setSize(maxSize);
        return o;
    }
    else {
        return o;
    }
}

int Warehouse::addPackOfBoxes(vector <ThinTallBox> boV) {
    for (auto box:boV)
        boxes.push(box);
    return boxes.size();
}


vector<ThinTallBox> Warehouse::DailyProcessBoxes(){
    vector<ThinTallBox> res;
    int n = boxes.size();
    for (int i = 0; i < n;i++) {
        if (boxes.front().getContentSize() == boxes.front().getCapacity()) {
            res.push_back(boxes.front());
            boxes.pop();
        }
        else if (boxes.front().getDays() == 0) {
            processBox(boxes.front());
            res.push_back(boxes.front());
            boxes.pop();
        }
        else {
            processBox(boxes.front());
            boxes.front().setDaysToSend(boxes.front().getDays()-1);
            boxes.push(boxes.front());
            boxes.pop();
        }

    }
    return res;
}

void Warehouse::processBox(ThinTallBox &box) {
    box.insert(RemoveObjectQueue(box.getCapacity()-box.getContentSize()));
}

