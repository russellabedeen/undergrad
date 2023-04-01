#include "pixel.h"

pixel::pixel(unsigned char r, unsigned char g, unsigned char b) {
	R = r;
	G = g;
	B = b;
}

pixel::pixel() {
	R = 255;
	G = 255;
	B = 255;
}

bool pixel::isTheSame(pixel& b) {
	int subR = R;
	int subG = G;
	int subB = B;
	int subR2 = b.R;
	int subG2 = b.G;
	int subB2 = b.B;
	
	if (subR == subR2 && subB == subB2 && subG == subG) {
		//cout << subR << "and the next one is" << subR2 << endl;
		return true;
	}
	else {
		//cout << subR << " and the next one is " << subR2 << endl;
		return false;
	}
}

