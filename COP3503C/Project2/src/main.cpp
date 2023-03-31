#include "Image.h"
#include "ImageFunctions.h"
#include <filesystem>
#include <iostream>
#include <string>


int main(int argc, char* argv[]) {
    // check for --help argument
    if (argc == 2 && string(argv[1]) == "--help") {
        cout << "Usage: ./ImageEditor <input file> <output file> <operation> <operation arguments>" << endl;
        cout << "Operations:" << endl;
        cout << "multiply <image 1> <image 2>" << endl;
        cout << "subtract <image 1> <image 2>" << endl;
        cout << "screen <image 1> <image 2>" << endl;
        cout << "overlay <image 1> <image 2>" << endl;
        cout << "addGreen <image>" << endl;
        cout << "scaleRed <image>" << endl;
        cout << "splitChannels <image> <r|g|b>" << endl;
        cout << "combineChannels <image 1> <image 2> <image 3>" << endl;
        cout << "rotate <image>" << endl;
        return 0;
    }

}