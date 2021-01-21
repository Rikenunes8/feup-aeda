#ifndef SRC_HOTEL_H_
#define SRC_HOTEL_H_

#include <vector>
#include <list>
#include <algorithm>

template <class Chamber>
class Hotel {
	std::vector<Chamber *> chambers;
	const unsigned int maxCapacity;
	const std::string city;
    std::list<Chamber> reservationsDone;
public:
	Hotel(int size, std::string municipality);
	~Hotel();
	std::vector<Chamber *> getChambers() const;
	void setChambers(std::vector<Chamber *> chambers);
	int getCapacity() const;
    std::list<Chamber> getReservationsDone() const;
	bool addChamber(Chamber *chamber);
    void addReservationDone(Chamber chamber);
    Chamber* removeChamber(std::string code, int floor);
	float avgArea(int floor) const;
	void sortChambers();
	bool doReservation(std::string code, int floor);
    std::list<Chamber> roomsNeverReserved() const;
};

class NoSuchChamberException {
public:
	NoSuchChamberException() { }
};

template <class Chamber>
Hotel<Chamber>::Hotel(int size, std::string municipality) : maxCapacity(size), city(municipality) {
}

template <class Chamber>
Hotel<Chamber>::~Hotel(){
	typename std::vector<Chamber *>::const_iterator it;
	for (it=chambers.begin(); it!=chambers.end(); it++) {
		delete *it;
	}
}

template<class Chamber>
std::vector<Chamber *> Hotel<Chamber>::getChambers() const {
	return chambers;
}

template<class Chamber>
void Hotel<Chamber>::setChambers(std::vector<Chamber*> chambers) {
	this->chambers = chambers;
}

template<class Chamber>
int Hotel<Chamber>::getCapacity() const {
	return maxCapacity;
}

template<class Chamber>
void Hotel<Chamber>::addReservationDone(Chamber chamber) {
    reservationsDone.push_back(chamber);
}

template<class Chamber>
std::list<Chamber> Hotel<Chamber>::getReservationsDone() const {
    return reservationsDone;
}

//------------------------------------------------------
//------------------------------------------------------
template<class Chamber>
bool alreadyExists(std::vector<Chamber*> chambers, Chamber* chamber) {
    for (auto c:chambers)
        if (*c == *chamber)
            return true;
    return false;
}

//TODO
template<class Chamber>
bool Hotel<Chamber>::addChamber(Chamber *chamber) {
    if (maxCapacity > chambers.size() && !alreadyExists(chambers, chamber)) {
        chambers.push_back(chamber);
        return true;
    }
    return false;
}


//TODO
template<class Chamber>
void Hotel<Chamber>::sortChambers() {
    std::sort(chambers.begin(), chambers.end(), [](Chamber* c1, Chamber* c2) {
       if (c1->getCode() == c2->getCode())
           return (c1->getFloor() > c2->getFloor());
       return (c1->getCode() < c2->getCode());
    });
}

//TODO
template<class Chamber>
Chamber* Hotel<Chamber>::removeChamber(std::string code, int floor) {

    typename std::vector<Chamber*>::iterator it = std::find_if(chambers.begin(), chambers.end(), [code, floor](Chamber* c){
       return (c->getCode() == code && c->getFloor() == floor);
    });
    if (it != chambers.end()) {
        Chamber* c = *it;
        chambers.erase(it);
        return c;
    }
    else
        throw NoSuchChamberException();
}


//TODO
class NoSuchFloorException {
private:
    int floor;
public:
    explicit NoSuchFloorException(int f) {floor=f;}
    int getFloor() const { return floor;}
};

//TODO
template<class Chamber>
float Hotel<Chamber>::avgArea(int floor) const {
    std::vector<Chamber*> temp;
    for (auto c:chambers)
        if (c->getFloor() == floor)
            temp.push_back(c);
    if (temp.empty())
        throw NoSuchFloorException(floor);
    else {
        double med = 0;
        for (auto c:temp)
            med += c->getArea();
        med /= temp.size();
        return med;
    }

}

//TODO
template<class Chamber>
bool Hotel<Chamber>::doReservation(std::string code, int floor){
    auto it = std::find_if(chambers.begin(), chambers.end(), [code, floor](Chamber* c){
        return (c->getCode() == code && c->getFloor() == floor);
        });
    if (it == chambers.end() || (*it)->getReservation()) {
        return false;
    }
    else {
        (*it)->setReservation(1);
        reservationsDone.push_back(*(*it));
        return true;
    }
}

template<class Chamber>
bool inList(const std::list<Chamber> &l, Chamber* &c) {
    return (std::find(l.begin(), l.end(), *c) != l.end());
}
//TODO
template<class Chamber>
std::list<Chamber> Hotel<Chamber>::roomsNeverReserved() const {
    std::list<Chamber> res;
    for (auto c:chambers)
        if (!inList(reservationsDone, c))
            res.push_back(*c);
    return res;
}





#endif /* SRC_HOTEL_H_ */
