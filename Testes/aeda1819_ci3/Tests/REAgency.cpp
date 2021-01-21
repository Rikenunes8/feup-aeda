#include "REAgency.h"

REAgency::REAgency(): catalogItems(PropertyTypeItem("", "","", 0)) {
	//do nothing!
}

REAgency::REAgency(vector<Property*> properties): catalogItems(PropertyTypeItem("", "","", 0)) {
	this->properties = properties;
}

void REAgency::addProperty(Property* property) {
	this->properties.push_back(property);
}

void REAgency::addProperties(vector<Property*> properties) {
	this->properties = properties;
}

vector<Property*> REAgency::getProperties() const{
	return this->properties;
}

PropertyTypeItem REAgency::getTypeItem(string address, string postalCode, string typology) {
	PropertyTypeItem itemNotFound("", "", "", 0);
	BSTItrIn<PropertyTypeItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getAddress() == address && it.retrieve().getPostalCode() == postalCode && it.retrieve().getTypology() == typology) {
			PropertyTypeItem pti(it.retrieve().getAddress(), it.retrieve().getPostalCode(), it.retrieve().getTypology(), 0);
			pti.setItems(it.retrieve().getItems());
			return pti;
		}
		it.advance();
	}
	return itemNotFound;
}

void REAgency::addTypeItem(Property* property) {
	PropertyTypeItem itemNotFound("", "","", 0);
	PropertyTypeItem pti(property->getAddress(), property->getPostalCode(), property->getTypology(), property->	getPrice());
	PropertyTypeItem ptiX = catalogItems.find(pti);
	if(ptiX == itemNotFound) {
		pti.addItems(property);
		this->catalogItems.insert(pti);
	}
	else {
		this->catalogItems.remove(ptiX);
		ptiX.addItems(property);
		this->catalogItems.insert(ptiX);
	}
	properties.push_back(property);
}

BST<PropertyTypeItem> REAgency::getTypeItems() const {
	return this->catalogItems;
}

vector<ClientRecord> REAgency::getClientRecords() const {
	vector<ClientRecord> records;
	HashTabClientRecord::const_iterator it1 = this->listingRecords.begin();
	HashTabClientRecord::const_iterator it2 = this->listingRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void REAgency::setClientRecords(vector<ClientRecord>& crs) {
	for(unsigned int i = 0; i < crs.size(); i++) {
		listingRecords.insert(crs[i]);
	}

}

priority_queue<Client> REAgency::getClientProfiles() const {
	return clientProfiles;
}
void REAgency::setClientProfiles(priority_queue<Client>& profiles) {
	clientProfiles = profiles;
}

//
// TODO: Part I   - BST
//
void REAgency::generateCatalog() {
    bool insert = false;
    PropertyTypeItem tmp("", "", "", 0);
	for (auto prop:properties) {
        insert = false;
        BSTItrIn<PropertyTypeItem> it(catalogItems);
        while (!it.isAtEnd()) {
            if (it.retrieve().same(*prop)) {
                tmp = it.retrieve();
                catalogItems.remove(it.retrieve());
                tmp.addItems(prop);
                catalogItems.insert(tmp);
                insert = true;
                break;
            }
            it.advance();
        }
        if (!insert) {
            tmp = PropertyTypeItem(prop->getAddress(), prop->getPostalCode(), prop->getTypology(), prop->getPrice());
            tmp.addItems(prop);
            catalogItems.insert(tmp);
        }
	}
}

vector<Property*> REAgency::getAvailableProperties(Property* property) const {
	vector<Property*> temp;

    for (auto& p:properties) {
        if (p->getAddress() == property->getAddress() && p->getPostalCode() == property->getPostalCode() &&
            p->getTypology() == property->getTypology() && p->getReservation() == tuple<Client*, int>())
            temp.push_back(p);
    }

	return temp;
}

bool REAgency::reservePropertyFromCatalog(Property* property, Client* client, int percentage) {
    /*BSTItrIn<PropertyTypeItem> it(catalogItems);
	while (!it.isAtEnd()) {
	    if (it.retrieve().same(*property)) {
	        for (auto& elem:it.retrieve().getItems()) {

	        }
	    }
	    it.advance();
	}*/
	vector<Property*> tmp;
	tmp = getAvailableProperties(property);
	if (tmp.empty())
	    return false;
	tmp[0]->setReservation(tuple<Client*, int>(client, tmp[0]->getPrice()*(100-percentage)/100));
    return true;
}

//
// TODO: Part II  - Hash Table
//
void REAgency::addClientRecord(Client* client) {
    ClientRecord c(client);
	listingRecords.insert(c);

}

void REAgency::deleteClients() {
    bool noMore = false;
    while (!noMore) {
        noMore = true;
        HashTabClientRecord::iterator it = listingRecords.begin();
        while (it != listingRecords.end()) {
            if(it->getClientPointer()->getVisitedProperties().empty()) {
                listingRecords.erase(it);
                noMore = false;
                break;
            }
            it++;
        }
    }

}

//
// TODO: Part III - Priority Queue
//
void REAgency::addBestClientProfiles(const vector<Client>candidates, int min) {
    int res;
    for (auto& client:candidates) {
        res = 0;
        for (auto& p:properties) {
            if (client.getEMail() == get<0>(p->getReservation())->getEMail()) {
                res++;
            }
        }
        if (res/(client.getVisitedProperties().size()+1) >= min)
            clientProfiles.push(client);
    }

}

vector<Property*> REAgency::suggestProperties() {
	vector<Property*> tempProperties;
    priority_queue<Client> tmpQ = clientProfiles;

	while (!tmpQ.empty()) {
	    Client c = tmpQ.top();
	    tmpQ.pop();
	    if (c.getVisiting() == tuple<string, string, string, string>()) continue;
	    Property* suggestion;
	    int min = 99999999;
	    for (auto& p:properties) {
	        int val = abs(stoi(get<1>(c.getVisiting())) - stoi(p->getPostalCode()));
	        if (get<0>(p->getReservation()) == nullptr && val < min && val != 0) {
                min = val;
                suggestion = p;
	        }
	    }
        tempProperties.push_back(suggestion);
	}

	return tempProperties;
}
