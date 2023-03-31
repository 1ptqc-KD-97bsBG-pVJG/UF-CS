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

float screenFunction(float factor, unsigned int firstPixel, unsigned int secondPixel) {
  float result = 1.0f - factor * ((1.0f - (((float)(firstPixel) / 255.0f))) * ((1.0f - ((float)(secondPixel) / 255.0f))));
  return result;
}

bool backgroundColor(unsigned int color) {
  if (color < (unsigned int)(127)) {
    return true;
  } else {
    return false;
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

Image Subtract(Image &firstImage, Image &secondImage) {
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
    
    unsigned int redPixelInt = (unsigned int)(scale(firstPixels[i].redInt - secondPixels[i].redInt));
    unsigned char redPixelChar = firstImage.ConvertIntToChar(redPixelInt);
    resultPixel.red = redPixelChar;

    unsigned int greenPixelInt = (unsigned int)(scale(firstPixels[i].greenInt - secondPixels[i].greenInt));
    unsigned char greenPixelChar = firstImage.ConvertIntToChar(greenPixelInt);
    resultPixel.green = greenPixelChar;

    unsigned int bluePixelInt = (unsigned int)(scale(firstPixels[i].blueInt - secondPixels[i].blueInt));
    unsigned char bluePixelChar = firstImage.ConvertIntToChar(bluePixelInt);
    resultPixel.blue = bluePixelChar;

    resultPixels.push_back(resultPixel);
  }
  imageResult.setPixels(resultPixels);

  return imageResult;
}

Image Screen(Image &firstImage, Image &secondImage) {
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
    
    float redPixelFloat = screenFunction(1.0f, firstPixels[i].redInt, secondPixels[i].redInt);
    unsigned int redPixelInt = (unsigned int)scale(redPixelFloat * 255.0f);
    unsigned char redPixelChar = firstImage.ConvertIntToChar(redPixelInt);
    resultPixel.red = redPixelChar;

    float greenPixelFloat = screenFunction(1.0f, firstPixels[i].greenInt, secondPixels[i].greenInt);
    unsigned int greenPixelInt = (unsigned int)scale(greenPixelFloat * 255.0f);
    unsigned char greenPixelChar = firstImage.ConvertIntToChar(greenPixelInt);
    resultPixel.green = greenPixelChar;

    float bluePixelFloat = screenFunction(1.0f, firstPixels[i].blueInt, secondPixels[i].blueInt);
    unsigned int bluePixelInt = (unsigned int)scale(bluePixelFloat * 255.0f);
    unsigned char bluePixelChar = firstImage.ConvertIntToChar(bluePixelInt);
    resultPixel.blue = bluePixelChar;

    resultPixels.push_back(resultPixel);
  }
  imageResult.setPixels(resultPixels);

  return imageResult;
}

Image Overlay(Image &firstImage, Image &secondImage) {
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
    unsigned int redPixelInt;
    unsigned int greenPixelInt;
    unsigned int bluePixelInt;

    if (backgroundColor(firstPixels[i].redInt)) {
      redPixelInt = (unsigned int)(2.0f * scale(firstPixels[i].redInt * secondPixels[i].redInt / 255.0f));
    } else {
      float redPixelFloat = screenFunction(2.0f, firstPixels[i].redInt, secondPixels[i].redInt);
      redPixelInt = (unsigned int)scale(redPixelFloat * 255.0f);
    }
    unsigned char red = firstImage.ConvertIntToChar(redPixelInt);
    resultPixel.red = red;

    if (backgroundColor(firstPixels[i].greenInt)) {
      greenPixelInt = (unsigned int)(2.0f * scale(firstPixels[i].greenInt * secondPixels[i].greenInt / 255.0f));
    } else {
      float greenPixelFloat = screenFunction(2.0f, firstPixels[i].greenInt, secondPixels[i].greenInt);
      greenPixelInt = (unsigned int)scale(greenPixelFloat * 255.0f);
    }
    unsigned char green = firstImage.ConvertIntToChar(greenPixelInt);
    resultPixel.green = green;

    if (backgroundColor(firstPixels[i].blueInt)) {
      bluePixelInt = (unsigned int)(2.0f * scale(firstPixels[i].blueInt * secondPixels[i].blueInt / 255.0f));
    } else {
      float bluePixelFloat = screenFunction(2.0f, firstPixels[i].blueInt, secondPixels[i].blueInt);
      bluePixelInt = (unsigned int)scale(bluePixelFloat * 255.0f);
    }
    unsigned char blue = firstImage.ConvertIntToChar(bluePixelInt);
    resultPixel.blue = blue;

    resultPixels.push_back(resultPixel);
  }
  imageResult.setPixels(resultPixels);

  return imageResult;
}

Image addGreen(Image &firstImage) {
  Image imageResult;
  vector <Image::Pixel> firstPixels = firstImage.getPixels();

  Image::Header header = firstImage.getHeader();
  imageResult.setHeader(header);

  vector <Image::Pixel> resultPixels;

  int greenValue;
  for (unsigned int i = 0; i < firstPixels.size(); i++) {
    Image::Pixel resultPixel;
    
    
    greenValue = firstPixels[i].greenInt + 200;
    unsigned int greenInt = clamp(greenValue);
    unsigned char greenChar = firstImage.ConvertIntToChar(greenInt);
    resultPixel.green = greenChar;

    resultPixel.red = firstPixels[i].red;
    resultPixel.blue = firstPixels[i].blue;
    resultPixels.push_back(resultPixel);
  }
  imageResult.setPixels(resultPixels);

  return imageResult;
}

Image scaleRed(Image &firstImage) {
  Image imageResult;
  
  Image::Header header = firstImage.getHeader();
  imageResult.setHeader(header);

  vector <Image::Pixel> firstPixels = firstImage.getPixels();
  vector <Image::Pixel> resultPixels;

  for (unsigned int i = 0; i < firstPixels.size(); i++) {
    Image::Pixel resultPixel;

    unsigned int redInt;
    float redFloat = ((float)firstPixels[i].redInt / 255.0f) * 4.0f;
    redInt = (unsigned int)scale(redFloat * 255.0f);
    redInt = clamp(redInt);
    unsigned char redChar = firstImage.ConvertIntToChar(redInt);
    resultPixel.red = redChar;

    resultPixel.green = firstPixels[i].green;

    // remove all blue
    resultPixel.blue = 0;
    resultPixels.push_back(resultPixel);
  }
  imageResult.setPixels(resultPixels);
  imageResult.setUnsignedInts();

  return imageResult;
}

Image splitChannels(string rgb, Image &firstImage) {
  Image imageResult;
  vector <Image::Pixel> firstPixels = firstImage.getPixels();

  Image::Header header = firstImage.getHeader();
  imageResult.setHeader(header);

  vector <Image::Pixel> resultPixels;

  for (unsigned int i = 0; i < firstPixels.size(); i++) {
    Image::Pixel resultPixel;
    if (rgb == "red") {
      resultPixel.red = firstPixels[i].red;
      resultPixel.green = firstPixels[i].red;
      resultPixel.blue = firstPixels[i].red;
    } else if (rgb == "green") {
      resultPixel.red = firstPixels[i].green;
      resultPixel.green = firstPixels[i].green;
      resultPixel.blue = firstPixels[i].green;
    } else if (rgb == "blue") {
      resultPixel.red = firstPixels[i].blue;
      resultPixel.green = firstPixels[i].blue;
      resultPixel.blue = firstPixels[i].blue;
    }
    resultPixels.push_back(resultPixel);
  }
  imageResult.setPixels(resultPixels);

  return imageResult;
}

Image combineChannels(Image &firstImage, Image &secondImage, Image &thirdImage) {
  Image imageResult;
  vector <Image::Pixel> firstPixels = firstImage.getPixels();
  vector <Image::Pixel> secondPixels = secondImage.getPixels();
  vector <Image::Pixel> thirdPixels = thirdImage.getPixels();

  Image::Header header = firstImage.getHeader();
  imageResult.setHeader(header);

  vector <Image::Pixel> resultPixels;

  for (unsigned int i = 0; i < firstPixels.size(); i++) {
    Image::Pixel resultPixel;
    resultPixel.red = firstPixels[i].red;
    resultPixel.green = secondPixels[i].green;
    resultPixel.blue = thirdPixels[i].blue;
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

  // rotate the input image 90 degrees clockwise and store the result in resultImage
  for (unsigned int i = 0; i < header.width; i++) {
    for (unsigned int j = 0; j < header.height; j++) {
      Image::Pixel resultPixel;
      resultPixel.blue = inputPixels[(header.width * (header.height - j - 1)) + i].blue;
      resultPixel.green = inputPixels[(header.width * (header.height - j - 1)) + i].green;
      resultPixel.red = inputPixels[(header.width * (header.height - j - 1)) + i].red;
      resultPixels.push_back(resultPixel);
    }
  }


  resultImage.setPixels(resultPixels);

  return resultImage;
}