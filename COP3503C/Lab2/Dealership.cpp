#include "Dealership.h"
#include <iostream>
#include <vector>
using namespace std;

Dealership::Dealership(std::string name, unsigned int capacity) {
    this->name = name;
    this->capacity = capacity;
}

void Dealership::AddShowroom(Showroom s) {
    if (showroomList.size() < this->capacity) {
        showroomList.push_back(s);
    }
    else {
        cout << "Dealership is full, can't add another showroom!" << endl;
    }    
}

float Dealership::GetAveragePrice() {
    float totalCost = 0;
    int totalVehicles = 0;
    for (unsigned int i = 0; i < showroomList.size(); i++) {
        for (unsigned int j = 0; j < showroomList[i].GetVehicleList().size(); j++) {
            totalCost += showroomList[i].GetVehicleList()[j].GetPrice();
            totalVehicles++;
        }
    }
    return totalCost / totalVehicles;
}

void Dealership::ShowInventory() {
    if (showroomList.size() == 0) {
        cout << this->name << " is empty!" << endl;
        cout << "Average car price: $0.00";
    } else {
        for (unsigned int i = 0; i < showroomList.size(); i++) {
            showroomList[i].ShowInventory();
            cout << endl;
        }
        cout << "Average car price: $" << GetAveragePrice();
    }
}
