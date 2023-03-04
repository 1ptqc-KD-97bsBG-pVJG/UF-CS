#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "extrafile.h"
using namespace std;

  // function for loading file



  // function for printing ships
  void PrintShips(vector<Ship> &ships) {
    for (unsigned int i = 0; i < ships.size(); i++) {
      ships[i].PrintShip();
    }
  }

  void PrintMostPowerfulWeaponShip(vector<Ship> &ships) {
    int mostPowerfulWeaponShipIndex;
    int highestPowerRating = 0;

    for (unsigned int i = 0; i < ships.size(); i++) {
      for (unsigned int j = 0; j < ships[i].GetWeapons().size(); j++) {
        if (ships[i].GetWeapons()[j].powerRating > highestPowerRating) {
          highestPowerRating = ships[i].GetWeapons()[j].powerRating;
          mostPowerfulWeaponShipIndex = i;
        }
      }
    }
    ships[mostPowerfulWeaponShipIndex].PrintShip();
  }

  // print the ship which has the most firepower
  void PrintOverallMostPowerfulShip(vector<Ship> &ships) {
    int mostFirePower = 0;
    int mostPowerfulShipIndex;

    for (unsigned int i = 0; i < ships.size(); i++) {
      if (ships[i].TotalFirePower() > mostFirePower) {
        mostFirePower = ships[i].TotalFirePower();
        mostPowerfulShipIndex = i;
      }
    }

    ships[mostPowerfulShipIndex].PrintShip();
  }

  // print the ship which has the least firepower
  void PrintOverallMostPowerfulShip(vector<Ship> &ships) {
    int leastFirePower = ships[0].TotalFirePower();
    int leastPowerfulShipIndex = 0;

    for (unsigned int i = 0; i < ships.size(); i++) {
      if (ships[i].weapons.size() > 0) {
        if (ships[i].TotalFirePower() < leastFirePower) {
          leastFirePower = ships[i].TotalFirePower();
          leastPowerfulShipIndex = i;
        }
      }
    }

    ships[leastPowerfulShipIndex].PrintShip();
  }

  // print all unarmed ships
  void PrintUnarmedShips(vector<Ship> &ships) {
    for (unsigned int i = 0; i < ships.size(); i++) {
      if (ships[i].weapons.size() == 0) {
        ships[i].PrintShip();
      }
    }
  }



int main() {
	cout << "Which file(s) to open?\n";
	cout << "1. friendlyships.shp" << endl;
	cout << "2. enemyships.shp" << endl;
	cout << "3. Both files" << endl;
	int option;
	cin >> option;

   /* Load files here */
  if (option == 3) {
    ifstream friendlyships("friendlyships.shp");
    ifstream enemyships("enemyships.shp");
    if (!friendlyships || !enemyships) {
      cout << "Error opening file" << endl;
      return 1;
    }
  } else if (option == 1) {
    ifstream friendlyships("friendlyships.shp");
    if (!friendlyships) {
      cout << "Error opening file" << endl;
      return 1;
    }
  } else if (option == 2) {
    ifstream enemyships("enemyships.shp");
    if (!enemyships) {
      cout << "Error opening file" << endl;
      return 1;
    }
  } else {
    cout << "Invalid option" << endl;
    return 1;
  }


	cout << "1. Print all ships" << endl;
	cout << "2. Starship with the strongest weapon" << endl;
	cout << "3. Strongest starship overall" << endl;
	cout << "4. Weakest ship (ignoring unarmed)" << endl;
	cout << "5. Unarmed ships" << endl;
	
	cin >> option;
	
	/* Work your magic here */
	
   return 0;
};