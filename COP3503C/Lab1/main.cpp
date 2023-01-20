#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

int main()
{
   string title;
   string column1Title;
   string column2Title;

    vector<string> column1;
    vector<int> column2;
    // Overall flow of the program:
    // Get some input for the title
    cout << "Enter a title for the data: " << endl;
    getline(cin, title);
    cout << "You entered: " << title << endl;

    // Get some input for column header #1
    cout << "Enter the column 1 header: " << endl;
    getline(cin, column1Title);
    cout << "You entered: " << column1Title << endl;

    // Get some input for column header #2
    cout << "Enter the column 2 header: " << endl;
    getline(cin, column2Title);
    cout << "You entered: " << column2Title << endl;
   
    string userDataInput;
    // Until the user types "-1":
    while (userDataInput != "-1") {
    // Get input for a string
    cout << "Enter a data point (-1 to stop input): " << endl;
    getline(cin, userDataInput);
    // Validate input
    // If valid...
        if (userDataInput.find(",") != string::npos) {
            // comma found, good
            // check if there are multiple commas
            if (userDataInput.find(",", userDataInput.find(",") + 1) != string::npos) { 
                cout << "Too many commas in input." << endl;
            } else {
                // only one comma, now split string on comma and space
                string first = userDataInput.substr(0, userDataInput.find(","));
                string second = userDataInput.substr(userDataInput.find(",") + 2);

                // check if second is a number
                try
                {
                    int second_num = stoi(second);
                    // add to vectors
                    column1.push_back(first);
                    column2.push_back(second_num);

                    cout << "Data string: " << first << endl;
                    cout << "Data integer: " << second_num << endl;
                }
                // second is not a number
                catch(const std::exception& e)
                {
                    cout << "Comma not followed by an integer." << endl;
                }
            }
        } else {
            // no comma found, bad
            if (userDataInput != "-1") {
                cout << "No comma in string." << endl;
            }
        }
   }

    // Print out data in table format
    cout << setw(33) << right << title << endl;
    cout << setw(20) << left << column1Title << " | " << setw(23) << right << column2Title << endl;
    cout << "--------------------------------------------" << endl;
    for (int i = 0; i < column1.size() - 1; i++ ) {
        cout << setw(20) << left << column1[i] << " | " << setw(23) << right << column2[i] << endl;
    }
    
    // Print out data in chart format
    for (int i = 0; i < column1.size() - 1; i++ ) {
        string dotsDisplay;
        for (int j = 0; j < column2[i]; j++) {
            dotsDisplay += "*";
        }
        cout << setw(20) << right << column1[i] << " " << dotsDisplay << endl;
    }
   
   return 0;
}