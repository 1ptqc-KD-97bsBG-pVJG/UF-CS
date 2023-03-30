#include <iostream>
#include <map>
#include <random>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

mt19937 random_mt;
class State {
public:
    string name;
    int population, perCapitaIncome, medianHouseholdIncome, numHouseholds;

    State() : name(""), population(0), perCapitaIncome(0), medianHouseholdIncome(0), numHouseholds(0) {}

    State(string name, int population, int perCapitaIncome, int medianHouseholdIncome, int numHouseholds) {
        this->name = name;
        this->population = population;
        this->perCapitaIncome = perCapitaIncome;
        this->medianHouseholdIncome = medianHouseholdIncome;
        this->numHouseholds = numHouseholds;
    }

    void display() const {
        cout << name << endl;
        cout << "Population: " << population << endl;
        cout << "Per Capita Income: " << perCapitaIncome << endl;
        cout << "Median Household Income: " << medianHouseholdIncome << endl;
        cout << "Number of Households: " << numHouseholds << endl;
    }
};

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

int main(){
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
      map<string, State> states;
      string record;

      ifstream File("states.csv");

      while (getline(File, record)) {
          stringstream ss(record);
          State data;
          string tempStr;

          try {
            getline(ss, data.name, ',');
            getline(ss, tempStr, ',');
            data.perCapitaIncome = stoi(tempStr);
            getline(ss, tempStr, ',');
            data.population = stoi(tempStr);
            getline(ss, tempStr, ',');
            data.medianHouseholdIncome = stoi(tempStr);
            getline(ss, tempStr);
            data.numHouseholds = stoi(tempStr);
            states[data.name] = data;
          } catch (const std::invalid_argument &e) {
              cerr << "Invalid data format in the record: " << record << endl;
          }
      }
      File.close();

      cout << "1. Print all states" << endl;
      cout << "2. Search for a state" << endl;
      int input;
      cin >> input;

      if (input == 1) {
          for (const auto &pair : states)
          {
              pair.second.display();
          }
      } else if (input == 2) {
          string searchKey;
          cin >> searchKey;
          auto searchResult = states.find(searchKey);
          if (searchResult != states.end()) {
              searchResult->second.display();
          } else {
              cout << "No match found for " << searchKey << endl;
          }
      }
  }

  return 0;
}