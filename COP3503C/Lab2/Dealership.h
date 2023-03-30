#ifndef DEALERSHIP_H
#define DEALERSHIP_H
#include "Showroom.h"
#include <iostream>
#include <vector>
using namespace std;

class Dealership {
    public:
        Dealership( std::string name = "Generic Dealership", unsigned  int  capacity = 0); 
        std::vector<Showroom> GetShowroomList(); 
        void  AddShowroom( Showroom s ); 
        float  GetAveragePrice(); 
        void  ShowInventory(); 

    private:
        std::string  name;
        unsigned  int  capacity;
        std::vector<Showroom>  showroomList;
};
#endif