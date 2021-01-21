#include "PropertyTypeItem.h"

PropertyTypeItem::PropertyTypeItem(string address, string postalCode, string typology, int maxPrice) {
	this->address = address;
	this->postalCode = postalCode;
	this->typology = typology;
	this->maxPrice = maxPrice;
}

string PropertyTypeItem::getAddress() const {
	return this->address;
}

string PropertyTypeItem::getPostalCode() const {
	return this->postalCode;
}

string PropertyTypeItem::getTypology() const {
	return this->typology;
}

int PropertyTypeItem::getMaxPrice() const {
	return this->maxPrice;
}

vector<Property*> PropertyTypeItem::getItems() const {
	return this->items;
}

void PropertyTypeItem::setItems(vector<Property*> properties) {
	items = properties;
}

void PropertyTypeItem::addItems(Property* property) {
	this->items.push_back(property);
}

//
// TODO
//
bool PropertyTypeItem::same(const Property &prop) const {
    return getAddress() == prop.getAddress() && getPostalCode() == prop.getPostalCode() && getTypology() == prop.getTypology();
}

bool PropertyTypeItem::operator<(const PropertyTypeItem &pti1) const {
    if (getAddress() == pti1.getAddress()) {
        if (getPostalCode() == pti1.getPostalCode()) {
            if (getTypology() == pti1.getTypology()) {
                return getMaxPrice() < pti1.getMaxPrice();
            }
            else {
                return getTypology() < pti1.getTypology();
            }
        }
        else {
            return getPostalCode() < pti1.getPostalCode();
        }
    }
    else {
        return getAddress() < pti1.getAddress();
    }
}

bool PropertyTypeItem::operator==(const PropertyTypeItem &pti1) const {
	return getAddress() == pti1.getAddress() && getPostalCode() < pti1.getPostalCode();
}
