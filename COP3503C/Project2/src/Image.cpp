#include "Image.h"
#include <fstream>
#include <stdexcept>
using namespace std;


void Image::loadImage(string filename) {
  // open file
  ifstream File(filename, ios::binary);

    if (!File.is_open()) {
      throw std::runtime_error("File does not exist.");
    }

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
  for (unsigned int i = 0; i < amountOfPixels; i++) {
    File.read((char*)&pixel.blue, sizeof(pixel.blue));
    File.read((char*)&pixel.green, sizeof(pixel.green));
    File.read((char*)&pixel.red, sizeof(pixel.red));
    
    pixel.blueInt = ConvertCharToInt(pixel.blue);
    pixel.greenInt = ConvertCharToInt(pixel.green);
    pixel.redInt = pixel.red;
    
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
  for (unsigned int i = 0; i < amountOfPixels; i++) {
    File.write((char*)&pixels[i].blue, sizeof(pixels[i].blue));
    File.write((char*)&pixels[i].green, sizeof(pixels[i].green));
    File.write((char*)&pixels[i].red, sizeof(pixels[i].red));
  }

  // close file
  File.close();
}

unsigned int Image::ConvertCharToInt(unsigned char charValue) {
  // Converts unsigned char to unsigned int by removing null terminator and type casting
  unsigned int intValue = (unsigned int)(charValue - '\0');
  return intValue;

}



unsigned char Image::ConvertIntToChar(unsigned int integer) {
    return (unsigned char)(integer);
}


Image::Header Image::getHeader() {
  return header;
}

vector<Image::Pixel> Image::getPixels() {
  return pixels;
}

void Image::setHeader(Header &data) {
  header.idLength = data.idLength;
  header.colorMapType = data.colorMapType;
  header.dataTypeCode = data.dataTypeCode;
  header.colorMapOrigin = data.colorMapOrigin;
  header.colorMapLength = data.colorMapLength;
  header.colorMapDepth = data.colorMapDepth;
  header.xOrigin = data.xOrigin;
  header.yOrigin = data.yOrigin;
  header.width = data.width;
  header.height = data.height;
  header.bitsPerPixel = data.bitsPerPixel;
  header.imageDescriptor = data.imageDescriptor;
}

void Image::setPixels(vector<Pixel> &data) {
  for (unsigned int i = 0; i < data.size(); i++){
    pixels.push_back(data[i]);            
  }
}

void Image::setUnsignedInts() {
  for (unsigned int i = 0; i < pixels.size(); i++) {
    pixels[i].blue = pixels[i].blueInt;
    pixels[i].green = pixels[i].greenInt;
    pixels[i].red = pixels[i].redInt;
  }
}

bool Image::operator==(Image &other) {
  for (unsigned int i = 0; i < pixels.size(); i++) {
    if (
      pixels[i].blue != other.pixels[i].blue ||
      pixels[i].green != other.pixels[i].green ||
      pixels[i].red != other.pixels[i].red
    ) {
      return false;
    } else {
      return true;
    } 
  }
}