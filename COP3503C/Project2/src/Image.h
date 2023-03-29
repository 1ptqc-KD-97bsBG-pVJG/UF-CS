#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Image {
  public:
    struct Pixel
      {
        unsigned int red;
        unsigned int green;
        unsigned int blue;

        unsigned char redChar;
        unsigned char greenChar;
        unsigned char blueChar;
      };

    struct Header {
      char idLength;
      char colorMapType;
      char dataTypeCode;
      short colorMapOrigin;
      short colorMapLength;
      char colorMapDepth;
      short xOrigin;
      short yOrigin;
      short width;
      short height;
      char bitsPerPixel;
      char imageDescriptor;
    };

    // image functions
    void loadImage(string filename);
    void writeToImage(string filename);

    // getters
    Header getHeader();
    vector<Pixel> getPixels();

    // setters
    void setHeader(Header header);
    void setPixels(vector<Pixel> pixels);

    

  
  private:
    Header header;
    vector<Pixel> pixels;
    Pixel pixel;
};