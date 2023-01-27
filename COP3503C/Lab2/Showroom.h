#ifndef SHOWROOM_H
#define SHOWROOM_H
#include "Vehicle.h"
#include <iostream>
#include <vector>
using namespace std;

class Showroom {
    public:
        Showroom( std::string  name =  "Unnamed Showroom" , unsigned  int  capacity =  0);
        std::vector<Vehicle>  GetVehicleList(); 
        void  AddVehicle(Vehicle  v ); 
        void  ShowInventory(); 
        float  GetInventoryValue();

    private:
        std::string  name;
        unsigned  int  capacity;
        std::vector<Vehicle>  vehicleList;
};
#endif