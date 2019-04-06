/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once


#include <string>
using std::string;

#include "imageNameSpace/PNG.h"
#include "imageNameSpace/HSLAPixel.h"

class Image: public imageNameSpace::PNG {
  public:
    void lighten();
    void lighten(double amount);
    void darken();
    void darken(double amount);
    void saturate();
    void saturate(double amount);
    void desaturate();
    void desaturate(double amount);
    void greyscale();
    void rotateColor(double degrees);
    void illinify();
    void scale(double factor);
    void scale(unsigned w, unsigned h);
  };
