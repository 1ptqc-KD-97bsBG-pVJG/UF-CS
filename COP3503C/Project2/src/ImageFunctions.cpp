#include "ImageFunctions.h"
#include "Image.h"
using namespace std;

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
  

}