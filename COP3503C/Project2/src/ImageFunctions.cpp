#include "ImageFunctions.h"
#include "Image.h"
using namespace std;

float scale(float value) {
  value += 0.5f;
  return value;
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

float screenFunction(float factor, unsigned int A, unsigned int B) {
    float temp = 1.0f - factor * ((1.0f - (((float)(A) / 255.0f))) * ((1.0f - ((float)(B) / 255.0f))));
    return temp;
}

bool backgroundColor(unsigned int color) {
    if (color < (unsigned int)(127)) {
        return true;
    }
    else {
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

Image Overlay(Image& A, Image& B) {


    // Make postOverlay image object
    Image postOverlay;


    // Get header for first image and set that header to the header of the post overlay
    Image::Header header = A.getHeader();
    postOverlay.setHeader(header);


    // Set ints of the input images
    A.setUnsignedInts();
    B.setUnsignedInts();


    // Set input image vectors
    vector<Image::Pixel> Apixels = A.getPixels();
    vector<Image::Pixel> Bpixels = B.getPixels();


    // Create output post overlay pixel vector
    vector<Image::Pixel> postOverlayPixels;


    // For every pixel, adjust rbg values then amend it to the post screen vector
    for (unsigned int i = 0; i < Apixels.size(); i++) {


        // Make pixel object with respective int values
        Image::Pixel PostOverlayPixel;
        unsigned int redInt;
        unsigned int greenInt;
        unsigned int blueInt;


        // Overlay is a conditional function and therefore will need to be implimented using if/else
        // Use background function to see what the background image's color is. Based on that adjust red.
        if (backgroundColor(Apixels[i].redInt)) {
            redInt = (unsigned int)(2.0f * scale(Apixels[i].redInt * Bpixels[i].redInt / 255.0f));
        }
        else {
            float redFloat = screenFunction(2.0f, Apixels[i].redInt, Bpixels[i].redInt);
            redInt = (unsigned int)scale(redFloat * 255.0f);
        }
        unsigned char red = A.ConvertIntToChar(redInt);
        PostOverlayPixel.red = red;


        // Ditto for green
        if (backgroundColor(Apixels[i].greenInt)) {
            greenInt = (unsigned int)(2.0f * scale(Apixels[i].greenInt * Bpixels[i].greenInt / 255.0f));
        }
        else {
            float greenFloat = screenFunction(2.0f, Apixels[i].greenInt, Bpixels[i].greenInt);
            greenInt = (unsigned int)scale(greenFloat * 255.0f);
        }
        unsigned char green = A.ConvertIntToChar(greenInt);
        PostOverlayPixel.green = green;


        // Ditto for blue
        if (backgroundColor(Apixels[i].blueInt)) {
            blueInt = (unsigned int)(2.0f * scale(Apixels[i].blueInt * Bpixels[i].blueInt / 255.0f));
        }
        else {
            float blueFloat = screenFunction(2.0f, Apixels[i].blueInt, Bpixels[i].blueInt);
            blueInt = (unsigned int)scale(blueFloat * 255.0f);
        }
        unsigned char blue = A.ConvertIntToChar(blueInt);
        PostOverlayPixel.blue = blue;


        // Add overlayed pixel to the greater pixel vector
        postOverlayPixels.push_back(PostOverlayPixel);
    }


    postOverlay.setPixels(postOverlayPixels);
    return postOverlay;
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
    firstImage.setUnsignedInts();

    vector<Image::Pixel> firstPixels = firstImage.getPixels();
    vector<Image::Pixel> resultPixels;

    for (unsigned int i = 0; i < firstPixels.size(); i++) {
        Image::Pixel resultPixel;

        unsigned int redPixelInt = (unsigned int)(scale(firstPixels[i].redInt));
        float redFloat = ((float)redPixelInt / 255.0f) * 4.0f;
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