#include "Image.h"
#include <fstream>
using namespace std;


void Image::loadImage(string filename) {
  // open file
  ifstream File(filename, ios::binary);

  // read header
  File.read(&header.idLength, sizeof(header.idLength));
  File.read(&header.colorMapType, sizeof(header.colorMapType));
  File.read(&header.dataTypeCode, sizeof(header.dataTypeCode));

  File.read((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
  File.read((char*)&header.colorMapLength, sizeof(header.colorMapLength));
  File.read(&header.colorMapDepth, sizeof(header.colorMapDepth));
  
  // read specfications
  File.read((char*)&header.xOrigin, sizeof(header.xOrigin));
  File.read((char*)&header.yOrigin, sizeof(header.yOrigin));
  File.read((char*)&header.width, sizeof(header.width));
  File.read((char*)&header.height, sizeof(header.height));
  File.read(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
  File.read(&header.imageDescriptor, sizeof(header.imageDescriptor));

  // read pixels and add them to the newly created pixel vector
  unsigned int amountOfPixels = header.width * header.height;
  for (int i = 0; i < amountOfPixels; i++) {
    File.read((char*)&pixel.blue, sizeof(pixel.blue));
    File.read((char*)&pixel.green, sizeof(pixel.green));
    File.read((char*)&pixel.red, sizeof(pixel.red));
    
    pixel.blueChar = pixel.blue;
    pixel.greenChar = pixel.green;
    pixel.redChar = pixel.red;
    
    pixels.push_back(pixel);
  }

  // close file
  File.close();
}

void Image::writeToImage(string filename) {
  // open file
  ofstream File(filename, ios::binary);

  // write header
  File.write(&header.idLength, sizeof(header.idLength));
  File.write(&header.colorMapType, sizeof(header.colorMapType));
  File.write(&header.dataTypeCode, sizeof(header.dataTypeCode));

  File.write((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
  File.write((char*)&header.colorMapLength, sizeof(header.colorMapLength));
  File.write(&header.colorMapDepth, sizeof(header.colorMapDepth));
  
  // write specfications
  File.write((char*)&header.xOrigin, sizeof(header.xOrigin));
  File.write((char*)&header.yOrigin, sizeof(header.yOrigin));
  File.write((char*)&header.width, sizeof(header.width));
  File.write((char*)&header.height, sizeof(header.height));
  File.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
  File.write(&header.imageDescriptor, sizeof(header.imageDescriptor));

  // write pixels
  unsigned int amountOfPixels = header.width * header.height;
  for (int i = 0; i < amountOfPixels; i++) {
    File.write((char*)&pixels[i].blue, sizeof(pixels[i].blue));
    File.write((char*)&pixels[i].green, sizeof(pixels[i].green));
    File.write((char*)&pixels[i].red, sizeof(pixels[i].red));
  }

  // close file
  File.close();
}