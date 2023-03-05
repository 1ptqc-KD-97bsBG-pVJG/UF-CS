#include <iostream>
#include <vector>
#include <string>
using namespace std;
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