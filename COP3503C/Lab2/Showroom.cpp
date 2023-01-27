#include "Showroom.h"
#include <iostream>
#include <vector>
using namespace std;

Showroom::Showroom(std::string name, unsigned int capacity) {
    this->name = name;
    this->capacity = capacity;
}

vector<Vehicle> Showroom::GetVehicleList() {
    return vehicleList;
}

void Showroom::AddVehicle(Vehicle v) {
    if (vehicleList.size() < this->capacity) {
        vehicleList.push_back(v);
    }
    else {
        cout << "Showroom is full! Cannot add " << v.GetYearMakeModel() << endl;
    }    
}

void Showroom::ShowInventory() {
    if (vehicleList.size() == 0) {
        cout << "Unnamed Showroom is empty!" << endl;
    } else {
        cout << "Vehicles in " << this->name << endl;
        for (unsigned int i = 0; i < vehicleList.size(); i++) {
            vehicleList[i].Display();
        }
    }
}

float Showroom::GetInventoryValue() {
    float total = 0;
    for (unsigned int i = 0; i < vehicleList.size(); i++) {
        total += vehicleList[i].GetPrice();
    }
    return total;
}