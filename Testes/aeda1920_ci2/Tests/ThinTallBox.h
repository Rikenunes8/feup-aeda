#ifndef SRC_THINTALLBOX_H_
#define SRC_THINTALLBOX_H_

#include <stack>
#include "Box.h"

using namespace std;

class ThinTallBox : public Box {
	stack<Object> objects;
public:
	ThinTallBox(double capacity);
	ThinTallBox(double capacity, stack<Object> objects, double content_size);
    stack<Object> getObjects() const;
    void insert(Object object);
	void remove(Object object);
	const Object& next() const;
	void sortObjects();
};

#endif /* SRC_THINTALLBOX_H_ */
