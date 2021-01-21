#include "ThinTallBox.h"
#include "WideFlatBox.h"

ThinTallBox::ThinTallBox(double capacity) : Box(capacity) {
}

ThinTallBox::ThinTallBox(double capacity, stack<Object> objects, double content_size) : Box(capacity) {
	this->objects = objects;
	this->setContentSize(content_size);
}

stack<Object> ThinTallBox::getObjects() const {
    return objects;
}

void ThinTallBox::remove(Object object) {
	Object next_object = next();
	if(!(next_object == object)) {
		throw InaccessibleObjectException(object);
	} else {
		setContentSize(getContentSize()-next_object.getSize());
		objects.pop();
	}
}

const Object& ThinTallBox::next() const {
	return objects.top();
}


void ThinTallBox::insert(Object object) {
    if (object.getSize()+getContentSize() > getCapacity() ) {
        throw ObjectDoesNotFitException();
    }
    else {
        setContentSize(getContentSize()+object.getSize());
        objects.push(object);
    }
}

void ThinTallBox::sortObjects() {
	WideFlatBox help(getContentSize());
	while (!empty()) {
	    help.insert(objects.top());
	    remove(objects.top());
	}
	help.sortObjects();
    while (!help.empty()) {
        insert(help.next());
        help.remove(help.next());
    }
}
