#include <iostream>
#include <fstream>
using namespace std;

int main()
{
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
}