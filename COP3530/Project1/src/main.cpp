#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include "AVLTree.h"
using namespace std;

/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/

bool checkId(string id)
{
	// Regex pattern for an ID of exactly 8 digits
	regex pattern("^\\d{8}$");

	return regex_match(id, pattern);
}

bool checkName(string name)
{
	// Regex pattern for a name consisting only of letters and spaces
	regex pattern("^[a-zA-Z\\s]*$");

	return regex_match(name, pattern);
}

int main(){
	AVLTree tree;

	// Get number of commands to execute
	int numCommands = 0;
	cin >> numCommands;
	cin.ignore();
	string line;

	// Execute commands
	for (int i = 0; i < numCommands; i++){
		// Read the whole commmand line
		getline(cin, line);
		stringstream ss(line);
		string command;
		ss >> command;

		// Determine which command and execute
		if (command == "insert") {
			string rawName, name, id;
			// Read from the first quote...
			getline(ss, rawName, '"');
			// ...until the next quote
			getline(ss, name, '"');
			// Assume whatever is left is the ID
			ss >> id;

			// Check if the name and ID are valid
			if (checkName(name) && checkId(id)) {
				// Insert the name and ID into the AVL tree
				tree.insertNode(name, id);
				cout << "successful" << endl;
			} else {
				cout << "unsuccessful" << endl;
			}

		} else if (command == "remove") {
			string id;
			getline(ss, id);
			ss >> id;
			// Trim leading and trailing spaces before and after id
			id.erase(0, id.find_first_not_of(" \t\n\r\f\v"));
			id.erase(id.find_last_not_of(" \t\n\r\f\v") + 1);
			if (checkId(id)) {
					tree.removeNode(id);
					cout << "successful" << endl;
			} else {
					cout << "unsuccessful" << endl;
			}

		} else if (command == "search") {
			// Extract the rest of the stringstream content as key
			string key = ss.str().substr(ss.tellg());

			// Remove leading whitespaces
			key.erase(0, key.find_first_not_of(" \t\n\r\f\v"));

			// Starts with a quote so searching for a name
			if (key.front() == '"') { 
					// Remove leading and trailing quotes
					key = key.substr(1, key.rfind('"') - 1);
					if (checkName(key)) {
							tree.searchName(key);
					} else {
							cout << "unsuccessful" << endl;
					}
			} else { 
					// Searching for an id
					// Trim leading and trailing spaces before and after id
					key.erase(0, key.find_first_not_of(" \t\n\r\f\v"));
					key.erase(key.find_last_not_of(" \t\n\r\f\v") + 1);
					if (checkId(key)) {
							tree.searchId(key);
					} else {
							cout << "unsuccessful" << endl;
					}
			}

		} else if (command == "printInorder") {
			tree.printInOrder();

		} else if (command == "printPreorder") {
			tree.printPreOrder();

		} else if (command == "printPostorder") {
			tree.printPostOrder();

		} else if (command == "printLevelCount") {
			tree.printLevelCount();

		} else if (command == "removeInorder") {
			int num;
			ss >> num;
			tree.removeInOrder(num);

		} else {
			// Invalid command (if it's not number of commands)
			if (i != 0) {
				cout << "unsuccessful" << endl;
			}
		}

	}
	return 0;
}

