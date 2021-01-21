#include "fleet.h"
#include <string>

using namespace std;

vector<Vehicle *> Fleet::getVehicles() const {
    return vehicles;
}
void Fleet::addVehicle(Vehicle *v1) {
    vehicles.push_back(v1);
}
int Fleet::numVehicles() const {
    return vehicles.size();
}
int Fleet::lowestYear() const {
    if (vehicles.empty())
        return 0;
    else {
        int low = vehicles[0]->getYear();
        for (auto it = vehicles.begin()+1; it != vehicles.end();it++){
            if ((*it)->getYear() < low)
                low = (*it)->getYear();
       }
        return low;
    }

}

vector<Vehicle *> Fleet::operator()(int y1) const {
    vector<Vehicle *> v;
    for (auto it = vehicles.begin(); it != vehicles.end(); it++)
        if ((*it)->getYear() == y1)
            v.push_back(*it);
    return v;
}

float Fleet::totalTax() const{
    float sum = 0;
    for (auto it = vehicles.begin(); it != vehicles.end(); it++)
        sum += (*it)->calculateTax();
    return sum;
}

unsigned Fleet::removeOldVehicles(int y1) {
    unsigned rem = 0;
    auto it = vehicles.begin();
    while (it != vehicles.end()){
        if ((*it)->getYear() <= y1){
            vehicles.erase(it);
            it = vehicles.begin();
            rem++;
        }
        else
            it++;
    }
    return rem;
}

ostream& operator<< (ostream& o, const Fleet& f){
    for (auto it = f.vehicles.begin(); it != f.vehicles.end(); it++){
        (*it)->info();
    }
    return o;
}

