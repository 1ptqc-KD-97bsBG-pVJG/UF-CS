#include <iostream>
#include <map>
#include <random>
#include <ctime>
using namespace std;

mt19937 random_mt;

int Random(int min, int max)
{
	uniform_int_distribution<int> dist(min, max);
	return dist(random_mt);
}

void RollDice(int numRolls, int numSides) {
  // map to store the number of times each side was rolled
  // key = side number, value = number of times rolled
  map<int, int> diceRolls;

  // initialize values
  for (int i = 1; i <= numSides; i++)
  {
    diceRolls[i] = 0;
  }

  for (int i = 0; i < numRolls; i++){
    int rollValue = Random(1, numSides);
    diceRolls[rollValue]++;
  }

  // print out the results
  for (const auto &pair : diceRolls)
  {
    cout << pair.first << ": " << pair.second << endl;
  }
}



int main()
{
	cout << "1. Random Numbers\n";
	cout << "2. State Info\n";

	int option;
	cin >> option;

	if (option == 1)
	{
		int randomSeed, numRolls, numSides;
		cout << "Random seed value: ";
		cin >> randomSeed;
		random_mt.seed(randomSeed);


		cout << "Number of times to roll the die: ";
    cin >> numRolls;

		cout << "Number of sides on this die: ";
    cin >> numSides;

		// Roll Dice
    RollDice(numRolls, numSides);
	}
	else if (option == 2)
	{
	   // Load the states
	   
	   // Get input for option 1 (show all states) or 2 (do a search for a particular state)

	}

	return 0;
}
