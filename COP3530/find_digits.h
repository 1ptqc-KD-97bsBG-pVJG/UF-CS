#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string findTheDigits(string x, string y) {
    // sort strings
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());

    string result;
    int i = 0, j = 0; // pointers for current character in x and y

    // iterate over strings
    while (j < y.size()) {
        if (i < x.size() && x[i] == y[j]) {
            // if characters are same, move both pointers
            i++;
            j++;
        } else {
            // if characters are different, new digit in y
            result += y[j];
            j++; // move pointer in y to next character
        }
    }

    // sort the result
    sort(result.begin(), result.end());
    return result;
}