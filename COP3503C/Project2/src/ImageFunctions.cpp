#include "ImageFunctions.h"
#include "Image.h"
using namespace std;

float scale(float value) {
  return value += 0.5;
}

unsigned int clamp (int preClampValue) {
  if (preClampValue < 0) {
    return 0;
  } else if (preClampValue > 255) {
    return 255;
  } else {
    return preClampValue;
  }
}

// image actions

Image Multiply(Image &firstImage, Image &secondImage) {
  Image imageResult;

  Image::Header header = firstImage.getHeader();
  imageResult.setHeader(header);
  firstImage.setUnsignedInts();
  secondImage.setUnsignedInts();

  vector<Image::Pixel> firstPixels = firstImage.getPixels();
  vector<Image::Pixel> secondPixels = secondImage.getPixels();
  vector<Image::Pixel> resultPixels;

  for (unsigned int i = 0; i < firstPixels.size(); i++) {
    Image::Pixel resultPixel;
    
    unsigned int redPixelInt = (unsigned int)(scale(firstPixels[i].redInt * secondPixels[i].redInt / 255.0f));
    unsigned char redPixelChar = firstImage.ConvertIntToChar(redPixelInt);
    resultPixel.red = redPixelChar;

    unsigned int greenPixelInt = (unsigned int)(scale(firstPixels[i].greenInt * secondPixels[i].greenInt / 255.0f));
    unsigned char greenPixelChar = firstImage.ConvertIntToChar(greenPixelInt);
    resultPixel.green = greenPixelChar;

    unsigned int bluePixelInt = (unsigned int)(scale(firstPixels[i].blueInt * secondPixels[i].blueInt / 255.0f));
    unsigned char bluePixelChar = firstImage.ConvertIntToChar(bluePixelInt);
    resultPixel.blue = bluePixelChar;

    resultPixels.push_back(resultPixel);
  }
  imageResult.setPixels(resultPixels);

  return imageResult;
}





Image Rotate(Image &inputImage) {
  Image resultImage;

  Image::Header header = inputImage.getHeader();
  resultImage.setHeader(header);

  vector<Image::Pixel> inputPixels = inputImage.getPixels();

  vector<Image::Pixel> resultPixels;

  for (unsigned int i = inputPixels.size(); i > 0; i--) {
    Image::Pixel resultPixel;

    resultPixel.red = inputPixels[i].red;
    resultPixel.green = inputPixels[i].green;
    resultPixel.blue = inputPixels[i].blue;

    resultPixels.push_back(resultPixel);
  }
  resultImage.setPixels(&resultPixels);

  return resultImage;
}