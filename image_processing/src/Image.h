#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "pixel.h"
using namespace std;

class Image {
public:
	class Header {
	public:
		int idLength;
		int colorMapType;
		int dataTypeCode;
		short colorMapOrigin;
		short colorMapLength;
		int colorMapDepth;
		short xOrigin;
		short yOrigin;
		short width;
		short height;
		int bitsPerPixel;
		int imageDescriptor;

		//Header();
	};

	Header head;
	int area;
	//vector<pixel> pixels;
	ifstream file1;
	ofstream file2;
	vector<pixel> imgData;

	Image(string filename);
	void readHeader();
	void readImageData();

	void writeHeader();
	void writeHeader(ofstream& f);
	void writeImageData();
	void write(string output);
	bool compare(Image& im2);

	void Multiply(Image& im2, string output);
	void Subtract(Image& im2, string output);
	void Screen(Image& im2, string output);
	void Overlay(Image& im2, string output);
	void Add(int value, int color);
	void Scale(int value, int color);
	void LoadColor(int color, string output);
	void Combine(Image& green, Image& blue, string output);
	void WriteReverse(string output);

};
