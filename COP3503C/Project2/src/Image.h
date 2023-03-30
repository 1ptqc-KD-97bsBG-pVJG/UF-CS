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
        unsigned char red;
        unsigned char green;
        unsigned char blue;

        unsigned int redInt;
        unsigned int greenInt;
        unsigned int blueInt;
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

    unsigned int ConvertCharToInt(unsigned char charValue);
    unsigned int ConvertIntToChar(unsigned int intValue);

    // getters
    Header getHeader();
    vector<Pixel> getPixels();

    // setters
    void setHeader(Header &header);
    void setPixels(vector<Pixel> &pixels);
    void setUnsignedInts();

    // might not be const
    bool operator==(const Image &image) const;
    

  private:
    Header header;
    Pixel pixel;
    vector<Pixel> pixels;
};