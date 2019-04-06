#include "Image.h"

#include <iostream>
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <cassert>
#include <algorithm>
#include <functional>

#include "imageNameSpace/lodepng/lodepng.h"
#include "imageNameSpace/PNG.h"
#include "imageNameSpace/HSLAPixel.h"
using imageNameSpace::HSLAPixel;


  void Image::lighten(){
    unsigned width = this->width();
    unsigned height = this->height();
    // Go over the whole image and copy pixels from one image to another
    for (unsigned y = 0; y < height; y++) {
      for (unsigned x = 0; x < width; x++) {
        // Recieve values for current pixel
        HSLAPixel& currPixel = this->getPixel(x, y);

        // checks curr luminance
        if (currPixel.l >= 0.9){
          currPixel.l = 1.0;
        } else {
          currPixel.l = currPixel.l + 0.1;
        }
      }
    }
  }
  void Image::lighten(double amount){
    unsigned width = this->width();
    unsigned height = this->height();
    // Go over the whole image and copy pixels from one image to another
    for (unsigned y = 0; y < height; y++) {
      for (unsigned x = 0; x < width; x++) {
        // Recieve values for current pixel
        HSLAPixel& currPixel = this->getPixel(x, y);

        // checks curr luminance
        if (currPixel.l >= (1.0 - amount)){
          currPixel.l = 1.0;
        } else {
          currPixel.l = currPixel.l + amount;
        }
      }
    }
  }
  void Image::darken(){
    unsigned width = this->width();
    unsigned height = this->height();
    // Go over the whole image and copy pixels from one image to another
    for (unsigned y = 0; y < height; y++) {
      for (unsigned x = 0; x < width; x++) {
        // Recieve values for current pixel
        HSLAPixel& currPixel = this->getPixel(x, y);

        // checks curr luminance
        if (currPixel.l <= 0.1){
          currPixel.l = 0.0;
        } else {
          currPixel.l = currPixel.l - 0.1;
        }
      }
    }
  }
  void Image::darken(double amount){
    unsigned width = this->width();
    unsigned height = this->height();
    // Go over the whole image and copy pixels from one image to another
    for (unsigned y = 0; y < height; y++) {
      for (unsigned x = 0; x < width; x++) {
        // Recieve values for current pixel
        HSLAPixel& currPixel = this->getPixel(x, y);

        // checks curr luminance
        if (currPixel.l <= (amount)){
          currPixel.l = 0.0;
        } else {
          currPixel.l = currPixel.l - amount;
        }
      }
    }
  }
  void Image::saturate(){
    unsigned width = this->width();
    unsigned height = this->height();
    // Go over the whole image and copy pixels from one image to another
    for (unsigned y = 0; y < height; y++) {
      for (unsigned x = 0; x < width; x++) {
        // Recieve values for current pixel
        HSLAPixel& currPixel = this->getPixel(x, y);

        // checks curr saturation
        if (currPixel.s >= 0.9){
          currPixel.s = 1.0;
        } else {
          currPixel.s = currPixel.s + 0.1;
        }
      }
    }
  }
  void Image::saturate(double amount){
    unsigned width = this->width();
    unsigned height = this->height();
    // Go over the whole image and copy pixels from one image to another
    for (unsigned y = 0; y < height; y++) {
      for (unsigned x = 0; x < width; x++) {
        // Recieve values for current pixel
        HSLAPixel& currPixel = this->getPixel(x, y);

        // checks curr saturation
        if (currPixel.s >= (1.0 - amount)){
          currPixel.s = 1.0;
        } else {
          currPixel.s = currPixel.s + amount;
        }
      }
    }
  }
  void Image::desaturate(){
    unsigned width = this->width();
    unsigned height = this->height();
    // Go over the whole image and copy pixels from one image to another
    for (unsigned y = 0; y < height; y++) {
      for (unsigned x = 0; x < width; x++) {
        // Recieve values for current pixel
        HSLAPixel& currPixel = this->getPixel(x, y);

        // checks curr saturation
        if (currPixel.s <= 0.1){
          currPixel.s = 0.0;
        } else {
          currPixel.s = currPixel.s - 0.1;
        }
      }
    }
  }
  void Image::desaturate(double amount){
    unsigned width = this->width();
    unsigned height = this->height();
    // Go over the whole image and copy pixels from one image to another
    for (unsigned y = 0; y < height; y++) {
      for (unsigned x = 0; x < width; x++) {
        // Recieve values for current pixel
        HSLAPixel& currPixel = this->getPixel(x, y);

        // checks curr saturation
        if (currPixel.s <= (amount)){
          currPixel.s = 0.0;
        } else {
          currPixel.s = currPixel.s - amount;
        }
      }
    }
  }
  void Image::greyscale(){
    unsigned width = this->width();
    unsigned height = this->height();
    // Go over the whole image and copy pixels from one image to another
    for (unsigned y = 0; y < height; y++) {
      for (unsigned x = 0; x < width; x++) {
        // Recieve values for current pixel
        HSLAPixel& currPixel = this->getPixel(x, y);

        // sets saturation to 0
        currPixel.s = 0.0;
      }
    }
  }
  void Image::rotateColor (double degrees){
    unsigned width = this->width();
    unsigned height = this->height();
    // Go over the whole image and copy pixels from one image to another
    for (unsigned y = 0; y < height; y++) {
      for (unsigned x = 0; x < width; x++) {
        // Recieve values for current pixel
        HSLAPixel& currPixel = this->getPixel(x, y);
        currPixel.h = currPixel.h + degrees;
        if (currPixel.h > 360){
          currPixel.h = currPixel.h - 360;
        }
        if (currPixel.h < 0){
          currPixel.h = currPixel.h + 360;
        }
      }
    }
  }
  void Image::illinify(){
    unsigned width = this->width();
    unsigned height = this->height();
    for (unsigned x = 0; x < width; x++) {
      for (unsigned y = 0; y < height; y++) {
        HSLAPixel & currPixel = this->getPixel(x, y);

        //adjusts color based off hue
        if (currPixel.h < 113.5 || currPixel.h >= 293.5){
          currPixel.h = 11;
        } else {
          currPixel.h = 216;
        }
      }
    }
  }
  void Image::scale(unsigned w, unsigned h){
    Image* output = new Image();
    output->resize(w, h);
    unsigned width = this->width();
    unsigned height = this->height();
    double ratioW = (double)width / (double)w;
    double ratioH = (double)height / (double)h;
    for (unsigned x = 0; x < w; x++) {
      for (unsigned y = 0; y < h; y++) {
        HSLAPixel & currPixel = output->getPixel(x, y);
        HSLAPixel & ratioPixel = this->getPixel((unsigned)((double)x * ratioW), (unsigned)((double)y * ratioH));
        //changes pixel values
        currPixel.h = ratioPixel.h;
        currPixel.s = ratioPixel.s;
        currPixel.l = ratioPixel.l;
        currPixel.a = ratioPixel.a;
      }
    }
    this->resize(w, h);
    for (unsigned x = 0; x < w; x++) {
      for (unsigned y = 0; y < h; y++) {
        HSLAPixel & ratioPixel = output->getPixel(x, y);
        HSLAPixel & currPixel = this->getPixel(x, y);
        //changes pixel values
        currPixel.h = ratioPixel.h;
        currPixel.s = ratioPixel.s;
        currPixel.l = ratioPixel.l;
        currPixel.a = ratioPixel.a;
      }
    }
    delete output;
  }
  void Image::scale(double factor){
    unsigned width = this->width();
    unsigned height = this->height();
    unsigned w = (unsigned)((double)width * factor);
    unsigned h = (unsigned)((double)height * factor);
    this->scale(w, h);
  }
