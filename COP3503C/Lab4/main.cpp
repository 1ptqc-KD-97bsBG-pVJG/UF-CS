#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "extrafile.h"
using namespace std;

  // function for loading file
  int LoadShipsFromFile(vector<Ship> &ships, string filePath, int counter) {
    ifstream ShipsFile(filePath, ios_base::binary);

    unsigned int amount;
    ShipsFile.read((char *)&amount, sizeof(amount));
    // loop through all ships in the file
    for (unsigned int i = 0; i < amount; i++) {
      // read name
      string name;
      unsigned int length;
      ShipsFile.read((char *)&length, sizeof(length));

      char *temp = new char[length];
      ShipsFile.read(temp, length);
      name = temp;
      delete[] temp;

      // read class
      string shipClass;
      ShipsFile.read((char *)&length, sizeof(length));

      temp = new char[length];
      ShipsFile.read(temp, length);
      shipClass = temp;
      delete[] temp;

      // read length, shield capacity, and max warp speed
      short shipLength;
      ShipsFile.read((char *)&shipLength, sizeof(shipLength));
      int shieldCapacity;
      ShipsFile.read((char *)&shieldCapacity, sizeof(shieldCapacity));
      float maxWarpSpeed;
      ShipsFile.read((char *)&maxWarpSpeed, sizeof(maxWarpSpeed));

      Ship shipFromFile(name, shipClass, shipLength, shieldCapacity, maxWarpSpeed);
      ships.push_back(shipFromFile);

      // read the inventory (weapons)
      unsigned int weaponCount;
      ShipsFile.read((char *)&weaponCount, sizeof(weaponCount));
      for (unsigned int j = 0; j < weaponCount; j++) {
        ShipsFile.read((char *)&length, sizeof(length));
        temp = new char[length];
        ShipsFile.read(temp, length);
        string weaponName = temp;
        delete[] temp;

        int powerRating;
        ShipsFile.read((char *)&powerRating, sizeof(powerRating));
        float powerConsumption;
        ShipsFile.read((char *)&powerConsumption, sizeof(powerConsumption));

        Ship::Weapons weaponsFromFile = Ship::Weapons(weaponName, powerRating, powerConsumption);
        ships[counter].GetWeapons().push_back(weaponsFromFile);
      }
      counter++;
    }
    return counter;
  }


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
  void PrintOverallLeastPowerfulShip(vector<Ship> &ships) {
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

  // create inital ships vector
  int counter = 0;
  vector<Ship> ships;
   /* Load files here */
  switch (option) {
    case 1:
      LoadShipsFromFile(ships, "friendlyships.shp", counter);
      break;
    case 2:
      LoadShipsFromFile(ships, "enemyships.shp", counter);
      break;
    case 3:
      counter = LoadShipsFromFile(ships, "friendlyships.shp", counter);
      LoadShipsFromFile(ships, "enemyships.shp", counter);
      break;
    default:
      break;
  }


	cout << "1. Print all ships" << endl;
	cout << "2. Starship with the strongest weapon" << endl;
	cout << "3. Strongest starship overall" << endl;
	cout << "4. Weakest ship (ignoring unarmed)" << endl;
	cout << "5. Unarmed ships" << endl;
	
	cin >> option;
	
	/* Work your magic here */
  switch (option) {
    case 1:
      PrintShips(ships);
      break;
    case 2:
      PrintMostPowerfulWeaponShip(ships);
      break;
    case 3:
      PrintOverallMostPowerfulShip(ships);
      break;
    case 4:
      PrintOverallLeastPowerfulShip(ships);
      break;
    case 5:
      PrintUnarmedShips(ships);
      break;
    default:
      break;
  }
   return 0;
}