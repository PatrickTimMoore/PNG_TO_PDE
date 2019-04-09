#include "Image.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
using namespace imageNameSpace;

/*
 * int MAIN()
 *    returns 0 on success, -1 on failure
 *
 *    Only works on PNG images
 *
 *    to run, type "make" -> "./mosaic"
 *
 *    Your edits go on lines:
 *        28, 34, 40, 47, and 51
 */


// EDIT HERE
// 0 = Image Blur Mosaic
// 1 = Gradient Flip Mosaic
// 2 = Basic Mosaic
// 3 = Pointillism w/ White Background
// 4 = Pointillism w/ Black Background
// 5 = Scaled effect
#define IMAGE_CONVERT 0 // EDIT HERE

// EDIT HERE
// 0 = Square Image
// 1 = Wide Image
// 2 = Tall Image
#define CUSTOM_STEPS 0 // EDIT HERE

int main() {
  // File to write Processing code to
  // Change to .txt or modify name below
  ofstream myfile;
  myfile.open ("sketch.pde"); // EDIT HERE
  // EDIT HERE
  // MUST BE .PNG EXTENTION
  // Image MUST be in same folder as C++ code
  //     Otherwise, use folder extentions
  // Imports image to immitate
  Image myImg;
  myImg.readFromFile("example.png"); // EDIT HERE
  // Rescales image to fit current memory constraints
  // Add image subroutines here for extra effects
  // soubroutines can be found in Image.h
  // EDIT HERE
  // Example:
  // myImg.illinify();
  // END EDITS
  if(myImg.width() > 1000 || myImg.height() > 1000){
    if(myImg.width() > myImg.height()){
      myImg.scale(1000 / (double)myImg.width());
    } else {
      myImg.scale(1000 / (double)myImg.height());
    }
  }
  int imgWidth = myImg.width()-1;
  int imgHeight = myImg.height()-1;
  // Steps modify image quality, determined by CUSTOM_STEPS
  // If illegal term, CUSTOM_STEPS inherits 0.
  int stepsW;
  int stepsH;
  if(CUSTOM_STEPS == 1){
      stepsW = 90;
      stepsH = 60;
  }else if(CUSTOM_STEPS == 2){
      stepsW = 60;
      stepsH = 90;
  }else{
      int steps = 80;
      stepsW = steps;
      stepsH = steps;
  }
  int stepWidth = imgWidth/stepsW;
  int stepHeight = imgHeight/stepsH;
  int tileCounter = 0;
  // Begins writing the Processing code
  printf("Initializeing the canvas\n");
  // Canvas is set to be equal size to resized image
  myfile << "// Initializing the canvas\n";
  myfile << "void setup() {\n";
  myfile << "    size(" << (stepWidth * stepsW) << ", " << (stepHeight * stepsH) << ", P3D);\n";
  myfile << "}\n\n";
  // Creates an array of pixels that will be used to creat mosaics
  vector<HSLAPixel> tilePixels;
  for (int y = 0; y <= (stepHeight * stepsH); y += stepHeight){
    for (int x = 0; x <= (stepWidth * stepsW); x += stepWidth){
      tilePixels.push_back(myImg.getPixel(x, y));
      tileCounter++;
    }
  }
  // Error catch if malfunction or .PNG is too small.
  if(tileCounter != (stepsH + 1) * (stepsW + 1)){
    printf("ERROR: Steps and tiles do not match!!!\n steps = %u, tiles = %u\n Image may be too small.\n Terminating run...\n", (stepsH+1)*(stepsW+1), tileCounter);
    return -1;
  }
  // Prints new image size to user
  printf("Translated size: \n%ux%u to %ux%u\n", imgWidth, imgHeight, (stepWidth * stepsW), (stepHeight * stepsH));
  myfile << "// Initializing the draw functions\n";
  // begin writing code depending on what mosaic you want
  switch(IMAGE_CONVERT){
      case 0: // Image Blur
          printf("Initializing 'Image Blur'\n");
          myfile << "void draw() {\n";
          myfile << "    noStroke();\n";
          myfile << "    colorMode(HSB, 360, 1, 1);\n";
          myfile << "    int tileResolution = " << tileCounter << ";\n";
          myfile << "    int stepsW = " << stepsW << ";\n";
          myfile << "    int stepsH = " << stepsH << ";\n";
          myfile << "    // Initialize place holders\n";
          myfile << "    float[] hue = hBackgroundTile(tileResolution);\n";
          myfile << "    float[] saturation = sBackgroundTile(tileResolution);\n";
          myfile << "    float[] luminance = lBackgroundTile(tileResolution);\n";
          myfile << "    int[] coord = coordBackgroundTile(tileResolution);\n";
          printf("Making print statements\n");
          myfile << "    float[] hueA = new float[4];\n";
          myfile << "    float[] saturationA = new float[4];\n";
          myfile << "    float[] luminanceA = new float[4];\n";
          myfile << "    // Iterates through each tile\n";
          myfile << "    for(int i = 0; i < stepsH; i++){\n";
          myfile << "        for(int j = 0; j < stepsW; j++){\n";
          myfile << "            hueA[0] = hue[j + i*(stepsW+1)];\n";
          myfile << "            hueA[1] = hue[j + i*(stepsW+1)+1];\n";
          myfile << "            hueA[2] = hue[j + (i+1)*(stepsW+1)+1];\n";
          myfile << "            hueA[3] = hue[j + (i+1)*(stepsW+1)];\n";
          myfile << "            saturationA[0] = saturation[j + i*(stepsW+1)];\n";
          myfile << "            saturationA[1] = saturation[j + i*(stepsW+1)+1];\n";
          myfile << "            saturationA[2] = saturation[j + (i+1)*(stepsW+1)+1];\n";
          myfile << "            saturationA[3] = saturation[j + (i+1)*(stepsW+1)];\n";
          myfile << "            luminanceA[0] = luminance[j + i*(stepsW+1)];\n";
          myfile << "            luminanceA[1] = luminance[j + i*(stepsW+1)+1];\n";
          myfile << "            luminanceA[2] = luminance[j + (i+1)*(stepsW+1)+1];\n";
          myfile << "            luminanceA[3] = luminance[j + (i+1)*(stepsW+1)];\n";
          myfile << "            drawBackgroundTile(hueA, saturationA, luminanceA, coord[0]*j, coord[0]*(j+1), coord[1]*i, coord[1]*(i+1));\n";
          myfile << "        }\n";
          myfile << "    }\n";
          myfile << "    save(\"output1.png\");\n";
          myfile << "}\n\n";
          break;
      case 1: // Gradient Flip
          printf("Initializing 'Gradient Flip'\n");
          myfile << "void draw() {\n";
          myfile << "    noStroke();\n";
          myfile << "    colorMode(HSB, 360, 1, 1);\n";
          myfile << "    int tileResolution = " << tileCounter << ";\n";
          myfile << "    int stepsW = " << stepsW << ";\n";
          myfile << "    int stepsH = " << stepsH << ";\n";
          myfile << "    // Initialize place holders\n";
          myfile << "    float[] hue = hBackgroundTile(tileResolution);\n";
          myfile << "    float[] saturation = sBackgroundTile(tileResolution);\n";
          myfile << "    float[] luminance = lBackgroundTile(tileResolution);\n";
          myfile << "    int[] coord = coordBackgroundTile(tileResolution);\n";
          printf("Making print statements\n");
          myfile << "    float[] hueA = new float[4];\n";
          myfile << "    float[] saturationA = new float[4];\n";
          myfile << "    float[] luminanceA = new float[4];\n";
          myfile << "    // Iterates through each tile\n";
          myfile << "    for(int i = 0; i < stepsH; i++){\n";
          myfile << "        for(int j = 0; j < stepsW; j++){\n";
          myfile << "            hueA[0] = hue[j + (i+1)*(stepsW+1)];\n";
          myfile << "            hueA[1] = hue[j + i*(stepsW+1)];\n";
          myfile << "            hueA[2] = hue[j + (i+1)*(stepsW+1)+1];\n";
          myfile << "            hueA[3] = hue[j + i*(stepsW+1)+1];\n";
          myfile << "            saturationA[0] = saturation[j + (i+1)*(stepsW+1)];\n";
          myfile << "            saturationA[1] = saturation[j + i*(stepsW+1)];\n";
          myfile << "            saturationA[2] = saturation[j + (i+1)*(stepsW+1)+1];\n";
          myfile << "            saturationA[3] = saturation[j + i*(stepsW+1)+1];\n";
          myfile << "            luminanceA[0] = luminance[j + (i+1)*(stepsW+1)];\n";
          myfile << "            luminanceA[1] = luminance[j + i*(stepsW+1)];\n";
          myfile << "            luminanceA[2] = luminance[j + (i+1)*(stepsW+1)+1];\n";
          myfile << "            luminanceA[3] = luminance[j + i*(stepsW+1)+1];\n";
          myfile << "            drawBackgroundTile(hueA, saturationA, luminanceA, coord[0]*j, coord[0]*(j+1), coord[1]*i, coord[1]*(i+1));\n";
          myfile << "        }\n";
          myfile << "    }\n";
          myfile << "    save(\"output2.png\");\n";
          myfile << "}\n\n";
          break;
      case 2: // Basic Mosaic
          printf("Initializing 'Basic Mosaic'\n");
          myfile << "void draw() {\n";
          myfile << "    noStroke();\n";
          myfile << "    colorMode(HSB, 360, 1, 1);\n";
          myfile << "    int tileResolution = " << tileCounter << ";\n";
          myfile << "    int stepsW = " << stepsW << ";\n";
          myfile << "    int stepsH = " << stepsH << ";\n";
          myfile << "    // Initialize place holders\n";
          myfile << "    float[] hue = hBackgroundTile(tileResolution);\n";
          myfile << "    float[] saturation = sBackgroundTile(tileResolution);\n";
          myfile << "    float[] luminance = lBackgroundTile(tileResolution);\n";
          myfile << "    int[] coord = coordBackgroundTile(tileResolution);\n";
          printf("Making print statements\n");
          myfile << "    float[] hueA = new float[4];\n";
          myfile << "    float[] saturationA = new float[4];\n";
          myfile << "    float[] luminanceA = new float[4];\n";
          myfile << "    // Iterates through each tile\n";
          myfile << "    for(int i = 0; i < stepsH; i++){\n";
          myfile << "        for(int j = 0; j < stepsW; j++){\n";
          myfile << "            hueA[0] = hue[j + i*(stepsW+1)];\n";
          myfile << "            hueA[1] = hue[j + i*(stepsW+1)+1];\n";
          myfile << "            hueA[2] = hue[j + (i+1)*(stepsW+1)+1];\n";
          myfile << "            hueA[3] = hue[j + (i+1)*(stepsW+1)];\n";
          myfile << "            saturationA[0] = saturation[j + i*(stepsW+1)];\n";
          myfile << "            saturationA[1] = saturation[j + i*(stepsW+1)+1];\n";
          myfile << "            saturationA[2] = saturation[j + (i+1)*(stepsW+1)+1];\n";
          myfile << "            saturationA[3] = saturation[j + (i+1)*(stepsW+1)];\n";
          myfile << "            luminanceA[0] = luminance[j + i*(stepsW+1)];\n";
          myfile << "            luminanceA[1] = luminance[j + i*(stepsW+1)+1];\n";
          myfile << "            luminanceA[2] = luminance[j + (i+1)*(stepsW+1)+1];\n";
          myfile << "            luminanceA[3] = luminance[j + (i+1)*(stepsW+1)];\n";
          myfile << "            drawBackgroundTile(hueA, saturationA, luminanceA, coord[0]*j, coord[0]*(j+1), coord[1]*i, coord[1]*(i+1));\n";
          myfile << "        }\n";
          myfile << "    }\n";
          myfile << "    save(\"output3.png\");\n";
          myfile << "}\n\n";
          break;
      case 3: // Pointillism w/ White Background
          printf("Initializing 'Pointillism'\n");
          myfile << "void draw() {\n";
          myfile << "    noStroke();\n";
          myfile << "    colorMode(HSB, 360, 1, 1);\n";
          myfile << "    int tileResolution = " << tileCounter << ";\n";
          myfile << "    int stepsW = " << stepsW << ";\n";
          myfile << "    int stepsH = " << stepsH << ";\n";
          myfile << "    // Initialize place holders\n";
          myfile << "    float[] hue = hBackgroundTile(tileResolution);\n";
          myfile << "    float[] saturation = sBackgroundTile(tileResolution);\n";
          myfile << "    float[] luminance = lBackgroundTile(tileResolution);\n";
          myfile << "    int[] coord = coordBackgroundTile(tileResolution);\n";
          myfile << "    float diameter;\n";
          myfile << "    if(coord[0] > coord[1]){\n";
          myfile << "        diameter = coord[1] * 0.8;\n";
          myfile << "    } else {\n";
          myfile << "        diameter = coord[0] * 0.8;\n";
          myfile << "    }\n";
          printf("Making print statements\n");
          myfile << "    // Sets background to white\n";
          myfile << "    beginShape();\n";
          myfile << "    fill(0, 0, 1);\n";
          myfile << "    rect(0, 0, " << (stepWidth * stepsW) << ", " << (stepHeight * stepsH) << ");\n";
          myfile << "    endShape();\n";
          myfile << "    // Iterates through each tile\n";
          myfile << "    for(int i = 0; i <= stepsH; i++){\n";
          myfile << "        for(int j = 0; j <= stepsW; j++){\n";
          myfile << "            beginShape();\n";
          myfile << "            // color of circle\n";
          myfile << "            fill(hue[i*(stepsW+1) + j], saturation[i*(stepsW+1) + j], luminance[i*(stepsW+1) + j]);\n";
          myfile << "            // draw circle\n";
          myfile << "            circle(coord[0]*j, coord[1]*i, diameter);\n";
          myfile << "            endShape();\n";
          myfile << "        }\n";
          myfile << "    }\n";
          myfile << "    save(\"output4.png\");\n";
          myfile << "}\n\n";
          break;
      case 4: // Pointillism w/ Black Background
          printf("Initializing 'Pointillism'\n");
          myfile << "void draw() {\n";
          myfile << "    noStroke();\n";
          myfile << "    colorMode(HSB, 360, 1, 1);\n";
          myfile << "    int tileResolution = " << tileCounter << ";\n";
          myfile << "    int stepsW = " << stepsW << ";\n";
          myfile << "    int stepsH = " << stepsH << ";\n";
          myfile << "    // Initialize place holders\n";
          myfile << "    float[] hue = hBackgroundTile(tileResolution);\n";
          myfile << "    float[] saturation = sBackgroundTile(tileResolution);\n";
          myfile << "    float[] luminance = lBackgroundTile(tileResolution);\n";
          myfile << "    int[] coord = coordBackgroundTile(tileResolution);\n";
          myfile << "    float diameter;\n";
          myfile << "    if(coord[0] > coord[1]){\n";
          myfile << "        diameter = coord[1] * 0.8;\n";
          myfile << "    } else {\n";
          myfile << "        diameter = coord[0] * 0.8;\n";
          myfile << "    }\n";
          printf("Making print statements\n");
          myfile << "    // Sets background to white\n";
          myfile << "    beginShape();\n";
          myfile << "    fill(0, 0, 0);\n";
          myfile << "    rect(0, 0, " << (stepWidth * stepsW) << ", " << (stepHeight * stepsH) << ");\n";
          myfile << "    endShape();\n";
          myfile << "    // Iterates through each tile\n";
          myfile << "    for(int i = 0; i <= stepsH; i++){\n";
          myfile << "        for(int j = 0; j <= stepsW; j++){\n";
          myfile << "            beginShape();\n";
          myfile << "            // color of circle\n";
          myfile << "            fill(hue[i*(stepsW+1) + j], saturation[i*(stepsW+1) + j], luminance[i*(stepsW+1) + j]);\n";
          myfile << "            // draw circle\n";
          myfile << "            circle(coord[0]*j, coord[1]*i, diameter);\n";
          myfile << "            endShape();\n";
          myfile << "        }\n";
          myfile << "    }\n";
          myfile << "    save(\"output5.png\");\n";
          myfile << "}\n\n";
          break;
      case 5: // Paint Stroke
          printf("Initializing 'Pointillism'\n");
          myfile << "void draw() {\n";
          myfile << "    noStroke();\n";
          myfile << "    colorMode(HSB, 360, 1, 1);\n";
          myfile << "    int tileResolution = " << tileCounter << ";\n";
          myfile << "    int stepsW = " << stepsW << ";\n";
          myfile << "    int stepsH = " << stepsH << ";\n";
          myfile << "    // Initialize place holders\n";
          myfile << "    float[] hue = hBackgroundTile(tileResolution);\n";
          myfile << "    float[] saturation = sBackgroundTile(tileResolution);\n";
          myfile << "    float[] luminance = lBackgroundTile(tileResolution);\n";
          myfile << "    int[] coord = coordBackgroundTile(tileResolution);\n";
          myfile << "    float diameter;\n";
          myfile << "    if(coord[0] > coord[1]){\n";
          myfile << "        diameter = coord[1] * 2;\n";
          myfile << "    } else {\n";
          myfile << "        diameter = coord[0] * 2;\n";
          myfile << "    }\n";
          printf("Making print statements\n");
          myfile << "    // Iterates through each tile\n";
          myfile << "    for(int i = 0; i <= stepsH; i++){\n";
          myfile << "        for(int j = 0; j <= stepsW; j++){\n";
          myfile << "            beginShape();\n";
          myfile << "            // color of circle\n";
          myfile << "            fill(hue[i*(stepsW+1) + j], saturation[i*(stepsW+1) + j], luminance[i*(stepsW+1) + j]);\n";
          myfile << "            // draw circle\n";
          myfile << "            circle(coord[0]*j, coord[1]*i, diameter);\n";
          myfile << "            endShape();\n";
          myfile << "        }\n";
          myfile << "    }\n";
          myfile << "    save(\"output6.png\");\n";
          myfile << "}\n\n";
          break;
  }


  // Tile Sub Routines
  printf("Making coord sub routines\n");
  myfile << "\n// COORDINATE TILE SUB-ROUTINE\n";
  myfile << "int[] coordBackgroundTile(int tileNum){\n";
  myfile << "    int[] coord = new int[2];\n";
  myfile << "    coord[0] = " <<  stepWidth << ";\n";
  myfile << "    coord[1] = " <<  stepHeight << ";\n";
  myfile << "return coord;\n";
  myfile << "}\n\n";

  printf("Making hue sub routines\n");
  myfile << "\n// HUE TILE SUB-ROUTINE\n";
  myfile << "float[] hBackgroundTile(int tileNum){\n";
  myfile << "    float[] h = new float[tileNum];\n";
  for(int i = 0; i < tileCounter; i++){
    myfile << "    h[" << i << "] = " <<  (float)tilePixels[i].h << ";\n";
  }
  myfile << "return h;\n";
  myfile << "}\n\n";

  printf("Making brightness sub routines\n");
  myfile << "\n// BRIGHTNESS TILE SUB-ROUTINE\n";
  myfile << "float[] lBackgroundTile(int tileNum){\n";
  myfile << "    float[] l = new float[tileNum];\n";
  vector<float> brightness;
  vector<float> t;
  for(int i = 0; i < tileCounter; i++){
      t.push_back(((float)tilePixels[i].s*( (float)tilePixels[i].l < 0.5 ? (float)tilePixels[i].l : 1-(float)tilePixels[i].l)));
      brightness.push_back((float)tilePixels[i].l + t[i]);
      myfile << "    l[" << i << "] = " <<  brightness[i] << ";\n";
  }
  myfile << "return l;\n";
  myfile << "}\n\n";

printf("Making saturation sub routines\n");
  myfile << "\n// SATURATION TILE SUB-ROUTINE\n";
  myfile << "float[] sBackgroundTile(int tileNum){\n";
  myfile << "    float[] s = new float[tileNum];\n";
  float temp;
  for(int i = 0; i < tileCounter; i++){
      temp = (float)tilePixels[i].l>0 ? 2*t[i]/brightness[i] : (float)tilePixels[i].s;
      myfile << "    s[" << i << "] = " << temp << ";\n";
  }
  myfile << "return s;\n";
  myfile << "}\n\n";

printf("Making draw sub routine\n");
  if(IMAGE_CONVERT == 2){
    myfile << "\n// BACKGROUND TILE DRAWING SUB-ROUTINE\n";
    myfile << "void drawBackgroundTile(float[] h, float[] s, float[] l, int x_low, int x_high, int y_low, int y_high){\n";
    myfile << "    beginShape();\n";
    myfile << "    // regular tile drawing\n";
    myfile << "    fill((h[0] + h[1] + h[2] + h[3])/4, (s[0] + s[1] + s[2] + s[3])/4, (l[0] + l[1] + l[2] + l[3])/4);\n";
    myfile << "    rect(x_low, y_low, x_high - x_low, y_high - y_low);\n";
    myfile << "    endShape();\n";
    myfile << "}\n\n";
  } else {
    myfile << "\n// BACKGROUND TILE DRAWING SUB-ROUTINE\n";
    myfile << "void drawBackgroundTile(float[] h, float[] s, float[] l, int x_low, int x_high, int y_low, int y_high){\n";
    myfile << "    beginShape();\n";
    myfile << "    // top-left corner of tile\n";
    myfile << "    fill(h[0], s[0], l[0]);\n";
    myfile << "    vertex(x_low, y_low);\n";
    myfile << "    // top-right corner of tile\n";
    myfile << "    fill(h[1], s[1], l[1]);\n";
    myfile << "    vertex(x_high, y_low);\n";
    myfile << "    // bottom-right corner of tile\n";
    myfile << "    fill(h[2], s[2], l[2]);\n";
    myfile << "    vertex(x_high, y_high);\n";
    myfile << "    // bottom-right corner of tile\n";
    myfile << "    fill(h[3], s[3], l[3]);\n";
    myfile << "    vertex(x_low, y_high);\n";
    myfile << "    endShape();\n";
    myfile << "}\n\n";
  }
  myfile.close();
  return 0;
}
