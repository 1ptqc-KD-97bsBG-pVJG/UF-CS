#include "ImageFunctions.h"
#include "Image.h"
using namespace std;

float scale(float value) {
  value += 0.5f;
  return value;
}

unsigned int clamp(int value) {
  if (value < 0) {
      return 0;
  }
  else if (value > 255) {
      return 255;
  }
  else {
      return value;
  }
}

float screenFunction(float factor, unsigned int A, unsigned int B) {
  float temp = 1.0f - factor * ((1.0f - (((float)(A) / 255.0f))) * ((1.0f - ((float)(B) / 255.0f))));
  return temp;
}

bool backgroundColor(unsigned int value) {
  if (value < (unsigned int)(127)) {
      return true;
  }
  else {
      return false;
  }
}


// image actions

Image Multiply(Image& firstImage, Image& secondImage) {
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

Image Subtract(Image& firstImage, Image& secondImage) {
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

Image Screen(Image& firstImage, Image& secondImage) {
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

Image Overlay(Image& A, Image& B) {
  Image postOverlay;

  Image::Header header = A.getHeader();
  postOverlay.setHeader(header);
  A.setUnsignedInts();
  B.setUnsignedInts();

  vector<Image::Pixel> Apixels = A.getPixels();
  vector<Image::Pixel> Bpixels = B.getPixels();
  vector<Image::Pixel> postOverlayPixels;

  for (unsigned int i = 0; i < Apixels.size(); i++) {
    Image::Pixel PostOverlayPixel;
    unsigned int redInt;
    unsigned int greenInt;
    unsigned int blueInt;

      if (backgroundColor(Apixels[i].redInt)) {
        redInt = (unsigned int)(2.0f * scale(Apixels[i].redInt * Bpixels[i].redInt / 255.0f));
      }
      else {
        float redFloat = screenFunction(2.0f, Apixels[i].redInt, Bpixels[i].redInt);
        redInt = (unsigned int)scale(redFloat * 255.0f);
      }
      unsigned char red = A.ConvertIntToChar(redInt);
      PostOverlayPixel.red = red;

      if (backgroundColor(Apixels[i].greenInt)) {
          greenInt = (unsigned int)(2.0f * scale(Apixels[i].greenInt * Bpixels[i].greenInt / 255.0f));
      }
      else {
        float greenFloat = screenFunction(2.0f, Apixels[i].greenInt, Bpixels[i].greenInt);
        greenInt = (unsigned int)scale(greenFloat * 255.0f);
      }
      unsigned char green = A.ConvertIntToChar(greenInt);
      PostOverlayPixel.green = green;

      if (backgroundColor(Apixels[i].blueInt)) {
          blueInt = (unsigned int)(2.0f * scale(Apixels[i].blueInt * Bpixels[i].blueInt / 255.0f));
      }
      else {
        float blueFloat = screenFunction(2.0f, Apixels[i].blueInt, Bpixels[i].blueInt);
        blueInt = (unsigned int)scale(blueFloat * 255.0f);
      }
      unsigned char blue = A.ConvertIntToChar(blueInt);
      PostOverlayPixel.blue = blue;

      postOverlayPixels.push_back(PostOverlayPixel);
  }

  postOverlay.setPixels(postOverlayPixels);
  return postOverlay;
}

Image addRed(Image& firstImage, int value) {
  Image imageResult;
  vector <Image::Pixel> firstPixels = firstImage.getPixels();

  Image::Header header = firstImage.getHeader();
  imageResult.setHeader(header);

  vector <Image::Pixel> resultPixels;

  int redValue;
  for (unsigned int i = 0; i < firstPixels.size(); i++) {
    Image::Pixel resultPixel;

    redValue = firstPixels[i].redInt + value;
    unsigned int redInt = clamp(redValue);
    unsigned char redChar = firstImage.ConvertIntToChar(redInt);
    resultPixel.red = redChar;

    resultPixel.green = firstPixels[i].green;
    resultPixel.blue = firstPixels[i].blue;
    resultPixels.push_back(resultPixel);
  }
  imageResult.setPixels(resultPixels);

  return imageResult;
}

Image addGreen(Image& firstImage, int value) {
  Image imageResult;
  vector <Image::Pixel> firstPixels = firstImage.getPixels();

  Image::Header header = firstImage.getHeader();
  imageResult.setHeader(header);

  vector <Image::Pixel> resultPixels;

  int greenValue;
  for (unsigned int i = 0; i < firstPixels.size(); i++) {
    Image::Pixel resultPixel;

    greenValue = firstPixels[i].greenInt + value;
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

Image addBlue(Image& firstImage, int value) {
  Image imageResult;
  vector <Image::Pixel> firstPixels = firstImage.getPixels();

  Image::Header header = firstImage.getHeader();
  imageResult.setHeader(header);

  vector <Image::Pixel> resultPixels;

  int blueValue;
  for (unsigned int i = 0; i < firstPixels.size(); i++) {
    Image::Pixel resultPixel;

    blueValue = firstPixels[i].blueInt + value;
    unsigned int blueInt = clamp(blueValue);
    unsigned char blueChar = firstImage.ConvertIntToChar(blueInt);
    resultPixel.blue = blueChar;

    resultPixel.red = firstPixels[i].red;
    resultPixel.green = firstPixels[i].green;
    resultPixels.push_back(resultPixel);
  }
  imageResult.setPixels(resultPixels);

  return imageResult;
}

Image scaleRed(Image& firstImage, float value) {
  Image imageResult;

  Image::Header header = firstImage.getHeader();
  imageResult.setHeader(header);
  firstImage.setUnsignedInts();

  vector<Image::Pixel> firstPixels = firstImage.getPixels();
  vector<Image::Pixel> resultPixels;

  for (unsigned int i = 0; i < firstPixels.size(); i++) {
    Image::Pixel resultPixel;

    unsigned int redPixelInt = (unsigned int)(scale(firstPixels[i].redInt));
    float redFloat = ((float)redPixelInt / 255.0f) * value;
    redPixelInt = (unsigned int)scale(redFloat * 255.0f);
    redPixelInt = clamp(redPixelInt);
    unsigned char redChar = firstImage.ConvertIntToChar(redPixelInt);
    resultPixel.red = redChar;

    unsigned int greenPixelInt = (unsigned int)(scale(firstPixels[i].greenInt));
    unsigned char greenPixelChar = firstImage.ConvertIntToChar(greenPixelInt);
    resultPixel.green = greenPixelChar;

    resultPixel.blue = 0;

    resultPixels.push_back(resultPixel);
  }
  imageResult.setPixels(resultPixels);

  return imageResult;
}

Image scaleBlue(Image& firstImage, float value) {
  Image imageResult;

  Image::Header header = firstImage.getHeader();
  imageResult.setHeader(header);
  firstImage.setUnsignedInts();

  vector<Image::Pixel> firstPixels = firstImage.getPixels();
  vector<Image::Pixel> resultPixels;

  for (unsigned int i = 0; i < firstPixels.size(); i++) {
    Image::Pixel resultPixel;

    unsigned int redPixelInt = (unsigned int)(scale(firstPixels[i].redInt));
    unsigned char redPixelChar = firstImage.ConvertIntToChar(redPixelInt);
    resultPixel.red = redPixelChar;

    unsigned int greenPixelInt = (unsigned int)(scale(firstPixels[i].greenInt));
    unsigned char greenPixelChar = firstImage.ConvertIntToChar(greenPixelInt);
    resultPixel.green = greenPixelChar;

    unsigned int bluePixelInt = (unsigned int)(scale(firstPixels[i].blueInt));
    float blueFloat = ((float)bluePixelInt / 255.0f) * value;
    bluePixelInt = (unsigned int)scale(blueFloat * 255.0f);
    bluePixelInt = clamp(bluePixelInt);
    unsigned char bluePixelChar = firstImage.ConvertIntToChar(bluePixelInt);
    resultPixel.blue = bluePixelChar;

    resultPixels.push_back(resultPixel);
  }
  imageResult.setPixels(resultPixels);

  return imageResult;
}

Image scaleGreen(Image& firstImage, float value) {
  Image imageResult;

  Image::Header header = firstImage.getHeader();
  imageResult.setHeader(header);
  firstImage.setUnsignedInts();

  vector<Image::Pixel> firstPixels = firstImage.getPixels();
  vector<Image::Pixel> resultPixels;

  for (unsigned int i = 0; i < firstPixels.size(); i++) {
    Image::Pixel resultPixel;

    unsigned int redPixelInt = (unsigned int)(scale(firstPixels[i].redInt));
    unsigned char redPixelChar = firstImage.ConvertIntToChar(redPixelInt);
    resultPixel.red = redPixelChar;

    unsigned int greenPixelInt = (unsigned int)(scale(firstPixels[i].greenInt));
    float greenFloat = ((float)greenPixelInt / 255.0f) * value;
    greenPixelInt = (unsigned int)scale(greenFloat * 255.0f);
    greenPixelInt = clamp(greenPixelInt);
    unsigned char greenPixelChar = firstImage.ConvertIntToChar(greenPixelInt);
    resultPixel.green = greenPixelChar;

    unsigned int bluePixelInt = (unsigned int)(scale(firstPixels[i].blueInt));
    unsigned char bluePixelChar = firstImage.ConvertIntToChar(bluePixelInt);
    resultPixel.blue = bluePixelChar;

    resultPixels.push_back(resultPixel);
  }
  imageResult.setPixels(resultPixels);

  return imageResult;
}

Image splitChannels(string rgb, Image& firstImage) {
  Image imageResult;
  vector <Image::Pixel> firstPixels = firstImage.getPixels();

  Image::Header header = firstImage.getHeader();
  imageResult.setHeader(header);

  vector <Image::Pixel> resultPixels;

  for (unsigned int i = 0; i < firstPixels.size(); i++) {
      Image::Pixel resultPixel;
      if (rgb == "red" || rgb == "onlyred") {
          resultPixel.red = firstPixels[i].red;
          resultPixel.green = firstPixels[i].red;
          resultPixel.blue = firstPixels[i].red;
      }
      else if (rgb == "green" || rgb == "onlygreen") {
          resultPixel.red = firstPixels[i].green;
          resultPixel.green = firstPixels[i].green;
          resultPixel.blue = firstPixels[i].green;
      }
      else if (rgb == "blue" || rgb == "onlyblue") {
          resultPixel.red = firstPixels[i].blue;
          resultPixel.green = firstPixels[i].blue;
          resultPixel.blue = firstPixels[i].blue;
      }
      resultPixels.push_back(resultPixel);
  }
  imageResult.setPixels(resultPixels);

  return imageResult;
}

Image combineChannels(Image& firstImage, Image& secondImage, Image& thirdImage) {
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

Image Rotate(Image& inputImage) {
    Image resultImage;

    Image::Header header = inputImage.getHeader();
    resultImage.setHeader(header);

    vector<Image::Pixel> inputPixels = inputImage.getPixels();

    vector<Image::Pixel> resultPixels;

    // Fix the off-by-one error by starting with i = inputPixels.size() - 1
    for (unsigned int i = inputPixels.size() - 1; ; i--) {
        Image::Pixel resultPixel;
        resultPixel.red = inputPixels[i].red;
        resultPixel.green = inputPixels[i].green;
        resultPixel.blue = inputPixels[i].blue;
        resultPixels.push_back(resultPixel);

        // Stop the loop when i becomes 0
        if (i == 0) {
            break;
        }
    }

    resultImage.setPixels(resultPixels);

    return resultImage;
}
