/*** image.h  Javi Agenjo (javi.agenjo@gmail.com) 2013
	This file defines the class Image that allows to manipulate images.
	It defines all the need operators for Color and Image.
	It has a TGA loader and saver.
***/

#ifndef IMAGE_H
#define IMAGE_H

#include <string.h>
#include <stdio.h>
#include <iostream>
#include "framework.h"

//remove unsafe warnings
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

//Class Image: to store a matrix of pixels
class Image
{
	//a general struct to store all the information about a TGA file
	typedef struct sTGAInfo 
	{
		unsigned int width;
		unsigned int height;
		unsigned int bpp; //bits per pixel
		unsigned char* data; //bytes with the pixel information
	} TGAInfo;

public:
	unsigned int width;
	unsigned int height;
	Color* pixels;

	// CONSTRUCTORS 
	Image();
	Image(unsigned int width, unsigned int height);
	Image(const Image& c);
	Image& operator = (const Image& c); //assign operator

	//destructor
	~Image();

	//get the pixel at position x,y
	Color getPixel(unsigned int x, unsigned int y) const { return pixels[ y * width + x ]; }
	Color& getPixelRef(unsigned int x, unsigned int y)	{ return pixels[ y * width + x ]; }
	Color getPixelSafe(unsigned int x, unsigned int y) const {	
		x = clamp((unsigned int)x, 0, width-1); 
		y = clamp((unsigned int)y, 0, height-1); 
		return pixels[ y * width + x ]; 
	}

	//set the pixel at position x,y with value C
	inline void setPixel(unsigned int x, unsigned int y, const Color& c) { pixels[ y * width + x ] = c; }
	inline void setPixelSafe(unsigned int x, unsigned int y, const Color& c) const { x = clamp(x, 0, width-1); y = clamp(y, 0, height-1); pixels[ y * width + x ] = c; }

	void resize(unsigned int width, unsigned int height);
	void scale(unsigned int width, unsigned int height);
	
	void flipY(); //flip the image top-down
	void flipX(); //flip the image left-right

	//fill the image with the color C
	void fill(const Color& c) { for(unsigned int pos = 0; pos < width*height; ++pos) pixels[pos] = c; }

	//returns a new image with the area from (startx,starty) of size width,height
	Image getArea(unsigned int start_x, unsigned int start_y, unsigned int width, unsigned int height);

	//save or load images from the hard drive
	bool loadTGA(const char* filename);
	bool saveTGA(const char* filename);

	//basic functions
	void drawRectangle(int x0, int y0, int w, int h, Color color, bool fill);
	void drawCircle(int x, int y, int r, Color color, bool fill);
	void drawLine(int x1, int y1, int x2, int y2, Color color);

	// Utils
	float computeDistance(int x1, int y1, int x2, int y2);

	// Task 3.2
	void radialGradient(Color s_color, Color f_color, unsigned int x0, unsigned int y0);
	void gradient(Color s_color, Color f_color);

	// Task 3.3
	void inverseFilter();
	void channelSwap(int option);
	void greyScale();
	void nxnBlur(int n);

	//Task 4.2
	void rotate(int degree);

	//Task 4.2
	void scale(float s);

	void setPixelP(unsigned int x, unsigned int y, Color c);
	void Bresenham(int x0, int y0, int x1, int y1, Color c);
	void BresenhamCircle(int x0, int y0, int radius, Color c, bool fill);

	//used to easy code
	#ifndef IGNORE_LAMBDAS

	//applies an algorithm to every pixel in an image
	// you can use lambda sintax:   img.forEachPixel( [](Color c) { return c*2; });
	// or callback sintax:   img.forEachPixel( mycallback ); //the callback has to be Color mycallback(Color c) { ... }
	template <typename F>
	Image& forEachPixel( F callback )
	{
		for(unsigned int pos = 0; pos < width*height; ++pos)
			pixels[pos] = callback(pixels[pos]);
		return *this;
	}

	#endif


};

#endif