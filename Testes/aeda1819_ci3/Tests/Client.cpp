#include "Client.h"

Client::Client(string name, string eMail) {
	this->name = name;
	this->eMail = eMail;
}

string Client::getName() const {
	return this->name;
}

void Client::setEmail(string eMail) {
	this->eMail = eMail;
}

string Client::getEMail() const {
	return this->eMail;
}

tuple<string, string, string, string> Client::getVisiting() const {
	return this->propertyListing;
}

vector<tuple<string, string, string, string> > Client::getVisitedProperties() const {
	return this->visitedProperties;
}

void Client::addVisiting(string address, string postalCode, string typology, string price) {
	//if visiting is blank, set it
		if(get<0>(this->propertyListing) == "" && get<2>(this->propertyListing) == "" && get<3>(this->propertyListing) == "" && get<3>(this->propertyListing) == "") {
			this->propertyListing = make_tuple(address, postalCode, typology, price);
		}
		//replace current visiting, and add previous to visited list
		else {
			this->visitedProperties.push_back(this->propertyListing);
			this->propertyListing = make_tuple(address, postalCode, typology, price);
		}
}

void Client::addVisited(string address, string postalCode, string typology, string price) {
    this->visitedProperties.push_back(make_tuple(address, postalCode, typology, price));
}
//
// TODO:
//

bool Client::operator<(const Client& c1) const {
	return get<3>(propertyListing) < get<3>(c1.getVisiting());
}
