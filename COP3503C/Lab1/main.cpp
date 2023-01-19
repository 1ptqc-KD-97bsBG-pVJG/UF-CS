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
        if () {

        }
        // Split
        // Validate second half of input
        // If also valid...
             // Store separate pieces
    


   }

//    Print out data in table format
   
//    Print out data in chart format
   
   return 0;
}