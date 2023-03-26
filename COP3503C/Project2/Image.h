#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Functions.h"
using namespace std;

class Image {
  public:
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
  
  private:
    Header header;
};