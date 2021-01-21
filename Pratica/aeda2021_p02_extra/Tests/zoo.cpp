#include "zoo.h"
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
using namespace std;

unsigned Zoo::numAnimals() const {
    return animals.size();
}

unsigned Zoo::numVeterinarians() const {
    return veterinarians.size();
}

void Zoo::addAnimal(Animal *a1) {
    animals.push_back(a1);
}

string Zoo::getInfo() const {
    string s;
    for (auto i:animals){
        s += i->getInfo() + '\n';
    }
    return s;
}

bool Zoo::isYoung(string nameA) {
    for (auto i: animals){
        if (i->getName() == nameA && i->isYoung())
            return true;
    }
    return false;
}

void Zoo::allocateVeterinarians(istream &isV) {
    string name;
    string cod;
    while (!isV.eof()){
        getline(isV, name);
        getline(isV, cod);
        Veterinary* v = new Veterinary(name, stol(cod));
        veterinarians.push_back(v);
    }

    for (size_t i = 0;i < animals.size(); i++){
        animals[i]->setVeterinary(veterinarians[i%3]);
        cout << animals[i]->getInfo() << endl;
    }

}

bool Zoo::removeVeterinary(string nameV) {
    for (size_t i = 0; i < veterinarians.size();i++){
        if (veterinarians[i]->getName() == nameV){
            for (auto animal:animals){
                if (animal->getVeterinary() == veterinarians[i])
                    if (i == veterinarians.size()-1)
                        animal->setVeterinary(veterinarians[0]);
                    else
                        animal->setVeterinary(veterinarians[i+1]);

            }
            veterinarians.erase(veterinarians.begin()+i);
            return true;
        }
    }
    return false;
}

bool Zoo::operator<(Zoo &zoo2) const {
    int sum1 = 0;
    int sum2 = 0;
    for(auto animal:animals){
        sum1 += animal->getAge();
    }
    for(auto animal:zoo2.animals){
        sum2 += animal->getAge();
    }
    return sum1 < sum2;
}

