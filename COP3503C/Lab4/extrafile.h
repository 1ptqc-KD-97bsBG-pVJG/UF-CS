#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Given data example:
// Name: UFS Programming  2 
// Class:  Science 
// Length: 1286 
// Shield  capacity: 2139 
// Maximum Warp: 5.8 
// Armaments: 
// Laser, 140,  6.3 
// Neutron Bomb, 1200,  1.7 
// Total  firepower: 1340
// 1) A string for the name of the vessel 
// 2) A string for the class of ship 
// 3) The length of the ship, stored as a short 
// 4) The shield capacity, stored as an integer 
// 5) The maximum warp speed of the ship, stored as a float 
// 6) An inventory containing a variable number of weapons, each of which contain a string, integer, and float. If a ship 
// doesn’t have any weapons, the file will still have to indicate a 0. Output-wise, you can just print out “Unarmed”

class Ship {
  public:
    struct Weapons {
      string weaponName;
      int powerRating;
      float powerConsumption;

      // default constructor
      Weapons(string weaponName, int powerRating, float powerConsumption) {
        this->weaponName = weaponName;
        this->powerRating = powerRating;
        this->powerConsumption = powerConsumption;
      }
    };

    string name;
    string className;
    short length;
    int shieldCapacity;
    float maxWarpSpeed;
    vector<Weapons> weapons;

    // default constructor
    Ship(string name, string className, short length, int shieldCapacity, float maxWarpSpeed) {
      this->name = name;
      this->className = className;
      this->length = length;
      this->shieldCapacity = shieldCapacity;
      this->maxWarpSpeed = maxWarpSpeed;
    }

    // functions
    void PrintShip();

    int TotalFirePower();

    vector<Weapons> &GetWeapons();

};