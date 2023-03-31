#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Image.h"
using namespace std;

float scale(float scale);

unsigned int clamp(int preClampValue);

// image actions
Image Multiply(Image &firstImage, Image &secondImage);

Image Subtract(Image &firstImage, Image &secondImage);

Image Screen(Image &firstImage, Image &secondImage);

Image Overlay(Image &firstImage, Image &secondImage);

Image addGreen(Image &image, unsigned int amount = 200);

Image scaleRed(Image &image, unsigned int amount = 200);

Image splitChannels(string rgbValue, Image &image);

Image combineChannels(Image &firstImage, Image &secondImage, Image &thirdImage);

Image Rotate(Image &image);