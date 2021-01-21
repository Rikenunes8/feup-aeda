#ifndef FLEET_H_
#define FLEET_H_

#include <vector>
#include "vehicle.h"
using namespace std;

class Fleet {
	vector<Vehicle *> vehicles;
public:
    vector<Vehicle *> getVehicles() const;
    void addVehicle(Vehicle *v1);
    int numVehicles() const;
    int lowestYear() const;
    vector<Vehicle *> operator()(int y1) const;
    float totalTax() const;
    unsigned removeOldVehicles(int y1);
	friend ostream & operator<<(ostream & o, const Fleet & f);
};


#endif /*FLEET_H_*/
