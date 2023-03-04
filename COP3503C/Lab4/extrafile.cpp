#include "extrafile.h"
#include <iostream>
#include <vector>
using namespace std;

void Ship::PrintShip() {
  cout << "Name: " << name << endl;
  cout << "Class: " << className << endl;
  cout << "Length: " << length << endl;
  cout << "Shield capacity: " << shieldCapacity << endl;
  cout << "Maximum Warp: " << maxWarpSpeed << endl;

  // print weapons
  cout << "Araments: " << endl;

  if (weapons.size() == 0) {
    cout << "Unarmed" << endl;
  } else {
    // print "name, powerRating, powerConsumption" for each weapon
    // then print total firepower (sum of all powerRatings)
    int totalFirePower = 0;
    for (unsigned int i = 0; i < weapons.size(); i++) {
      cout << weapons[i].weaponName << ", " << weapons[i].powerRating << ", " << weapons[i].powerConsumption << endl;
      totalFirePower += weapons[i].powerRating;
    }
    cout << "Total Firepower: " << totalFirePower << endl;
  }
}