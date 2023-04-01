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
Image Multiply(Image& firstImage, Image& secondImage);

Image Subtract(Image& firstImage, Image& secondImage);

Image Screen(Image& firstImage, Image& secondImage);

Image Overlay(Image& firstImage, Image& secondImage);

Image addRed(Image& image, int amount = 200);

Image addGreen(Image& image, int amount = 200);

Image addBlue(Image& image, int amount = 200);

Image scaleRed(Image& image, float amount = 4.0f);

Image scaleBlue(Image& image, float amount = 4.0f);

Image scaleGreen(Image& image, float amount = 4.0f);

Image splitChannels(string rgbValue, Image& image);

Image combineChannels(Image& firstImage, Image& secondImage, Image& thirdImage);

Image Rotate(Image& image);