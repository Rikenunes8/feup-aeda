#include "animal.h"
#include <sstream>
using namespace std;


/* --------- ANIMAL ---------- */
int Animal::youngest = 1000;

Animal::Animal(string name, int age) {
    this->name = name;
    this->age = age;
    if (age < youngest)
        youngest = age;
}

string Animal::getName() const {
	return name;
}

int Animal::getAge() const {
    return age;
}

void Animal::setVeterinary(Veterinary *vet) {
    this->vet = vet;
}

Veterinary *Animal::getVeterinary() const {
    return vet;
}

int Animal::getYoungest() {
    return youngest;
}

string Animal::getInfo() const {
    string s = name + ", " + to_string(age) + ", ";
    if (vet != NULL)
        s += vet->getInfo();
    return s;
}
/* ------------- DOG -----------*/
Dog::Dog(string name, int age, string breed) : Animal(name, age){
    this->breed = breed;
}

bool Dog::isYoung() const {return age < 5;}

string Dog::getInfo() const {
    return Animal::getInfo() + breed;
}
/* ----------- FLYING ---------- */

Flying::Flying(int maxv, int maxa) {
    maxVelocity = maxv;
    maxAltitude = maxa;
}

string Flying::getInfo() const {
    return to_string(maxVelocity) + ", " + to_string(maxAltitude);
}

/* ------------ BAT ---------- */
Bat::Bat(string name, int age, int maxv, int maxa) : Animal(name, age), Flying(maxv, maxa){}

bool Bat::isYoung() const {return age < 4;}

string Bat::getInfo() const {
    return Animal::getInfo() + Flying::getInfo();
}


