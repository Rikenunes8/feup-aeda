#include "vehicle.h"
#include <iostream>

using namespace std;

Vehicle::Vehicle(string b, int m, int y) {
    brand = b;
    month = m;
    year = y;
}
int Vehicle::getYear() const { return year;}
string Vehicle::getBrand() const {return brand;}
int Vehicle::info() const {
    cout << brand << ", " << month << ", " << year;
    return 3;
}
bool Vehicle::operator<(const Vehicle &v) const {
    if (year < v.year)
        return true;
    else if (year > v.year)
        return false;
    else {
        return month < v.month;
    }
}



MotorVehicle::MotorVehicle(string b, int m, int y, string f, int cyl):Vehicle(b, m, y) {
    fuel = f;
    cylinder = cyl;
}
string MotorVehicle::getFuel() const {return fuel;}
int MotorVehicle::info() const {
    int n = Vehicle::info();
    cout << ", " << fuel << ", " << cylinder;
    return n+2;
}
float MotorVehicle::calculateTax() const {
    float y1995[] = {14.56, 29.06, 45.15, 113.98, 181.17, 320.89};
    float Y1995[] = {8.10, 14.56, 22.65, 54.89, 87.13, 148.37};
    if (getYear()>1995){
        if (fuel == "gas") {
            if (cylinder <= 1000)
                return y1995[0];
            else if (cylinder <= 1300)
                return y1995[1];
            else if (cylinder <= 1750)
                return y1995[2];
            else if (cylinder <= 2600)
                return y1995[3];
            else if (cylinder <= 3500)
                return y1995[4];
            else
                return y1995[5];
        }
        else {
            if (cylinder <= 1500)
                return y1995[0];
            else if (cylinder <= 2000)
                return y1995[1];
            else if (cylinder <= 3000)
                return y1995[2];
            else
                return y1995[3];
        }
    }
    else {
        if (fuel == "gas") {
            if (cylinder <= 1000)
                return Y1995[0];
            else if (cylinder <= 1300)
                return Y1995[1];
            else if (cylinder <= 1750)
                return Y1995[2];
            else if (cylinder <= 2600)
                return Y1995[3];
            else if (cylinder <= 3500)
                return Y1995[4];
            else
                return Y1995[5];
        }
        else {
            if (cylinder <= 1500)
                return Y1995[0];
            else if (cylinder <= 2000)
                return Y1995[1];
            else if (cylinder <= 3000)
                return Y1995[2];
            else
                return Y1995[3];
        }
    }

}



Car::Car(string b, int m, int y, string f, int cyl):MotorVehicle(b, m, y, f, cyl) {}
int Car::info() const {
    int n = MotorVehicle::info();
    cout << endl;
    return n;
}




Truck::Truck(string b, int m, int y, string f, int cyl, int ml):MotorVehicle(b, m, y, f, cyl) {
    maximumLoad = ml;
}
int Truck::info() const {
    int n = MotorVehicle::info();
    cout << ", " << maximumLoad << endl;
    return n+1;
}



Bicycle::Bicycle(string b, int m, int y, string t):Vehicle(b, m, y) {
    type = t;
}
int Bicycle::info() const {
    int n = Vehicle::info();
    cout << ", " << type << endl;
    return n+1;
}

float Bicycle::calculateTax() const {
    return 0;
}