#ifndef SRC_WAREHOUSE_H_
#define SRC_WAREHOUSE_H_

#include <queue>
#include "Box.h"
#include "Object.h"
#include "ThinTallBox.h"

using namespace std;

class Warehouse {
	queue<ThinTallBox> boxes;
	queue<Object> objects;
public:
    Warehouse();
	queue<ThinTallBox> getBoxes();
	queue<Object> getObjects();
    void setBoxes(queue<ThinTallBox> q);
    void addObject(Object o1);
    int InsertObjectsInQueue(vector <Object> objects);
    Object RemoveObjectQueue(int maxSize);
    int addPackOfBoxes(vector <ThinTallBox> boV);
    vector<ThinTallBox> DailyProcessBoxes();
    void processBox(ThinTallBox &box);
};

#endif /* SRC_WAREHOUSE_H_ */
