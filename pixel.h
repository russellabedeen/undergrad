#pragma once
#include <iostream>

using namespace std;

class pixel {
public:
	unsigned char R;
	unsigned char G;
	unsigned char B;

	pixel(unsigned char r, unsigned char g, unsigned char b);
	pixel();
	bool isTheSame(pixel& b);
};
