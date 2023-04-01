#include <iostream>
#include <fstream>
#include <vector>
#include "Image.h"
#include "pixel.h"
Image::Image(string filename) {
	file1.open(filename, ios_base::binary);
	readHeader();
	area = head.height * head.width;
	readImageData();
}

void Image::readHeader() {
	char holder;
	file1.read(&holder, 1);
	head.idLength = holder;

	char holder2;
	file1.read(&holder2, 1);
	head.colorMapType = holder2;

	char holder3;
	file1.read(&holder3, 1);
	head.dataTypeCode = holder3;

	short holder4;
	file1.read((char *)&holder4, 2);
	head.colorMapOrigin = holder4;

	short holder5;
	file1.read((char*) &holder5, 2);
	head.colorMapLength = holder5;

	char holder6;
	file1.read(&holder6, 1);
	head.colorMapDepth = holder6;

	short holder7;
	file1.read((char*)&holder7, 2);
	head.xOrigin = holder7;

	short holder8;
	file1.read((char* )&holder8, 2);
	head.yOrigin = holder8;

	short holder9;
	file1.read((char*) &holder9, 2);
	head.width = holder9;

	short holder10;
	file1.read((char*) &holder10, 2);
	head.height = holder10;

	char holder11;
	file1.read(&holder11, 1);
	head.bitsPerPixel = holder11;

	char holder12;
	file1.read(&holder12, 1);
	head.imageDescriptor = holder12;
}

void Image::readImageData() {
	imgData.reserve(area);
	for (int i = 0; i < area; i++) {
		char holder;
		file1.read(&holder, 1);
		int B = holder;

		file1.read(&holder, 1);
		int G = holder;

		file1.read(&holder, 1);
		int R = holder;

		pixel p = pixel(R, G, B);
		imgData.push_back(p);
	}
}

void Image::writeHeader() {
	file2.write((char *)&head.idLength, 1);
	file2.write((char*)&head.colorMapType, 1);
	file2.write((char*)&head.dataTypeCode, 1);
	file2.write((char*)&head.colorMapOrigin, 2);
	file2.write((char*)&head.colorMapLength, 2);
	file2.write((char*)&head.colorMapDepth, 1);
	file2.write((char*)&head.xOrigin, 2);
	file2.write((char*)&head.yOrigin, 2);
	file2.write((char*)&head.width, 2);
	file2.write((char*)&head.height, 2);
	file2.write((char*)&head.bitsPerPixel, 1);
	file2.write((char*)&head.imageDescriptor, 1);
}

void Image::writeHeader(ofstream& f) {
	f.write((char*)&head.idLength, 1);
	f.write((char*)&head.colorMapType, 1);
	f.write((char*)&head.dataTypeCode, 1);
	f.write((char*)&head.colorMapOrigin, 2);
	f.write((char*)&head.colorMapLength, 2);
	f.write((char*)&head.colorMapDepth, 1);
	f.write((char*)&head.xOrigin, 2);
	f.write((char*)&head.yOrigin, 2);
	f.write((char*)&head.width, 2);
	f.write((char*)&head.height, 2);
	f.write((char*)&head.bitsPerPixel, 1);
	f.write((char*)&head.imageDescriptor, 1);
}

void Image::writeImageData() {
	for (int i = 0; i < area; i++) {
		int wB = imgData[i].B;
		int wG = imgData[i].G;
		int wR = imgData[i].R;
		file2.write((char*)&wB, 1);
		file2.write((char*)&wG, 1);
		file2.write((char*)&wR, 1);
	}
}

void Image::write(string output) {
	file2.open(output, ios_base::binary);
	writeHeader();
	writeImageData();
}

bool Image::compare(Image& im2) {
	for (int i = 0; i < area; i++) {
		if (!imgData[i].isTheSame(im2.imgData[i])) {
			return false;
		}
	}
	return true;
}

void Image::Multiply(Image& im2, string output) {
	ofstream out(output, ios_base::binary);
	writeHeader(out);
	for (int i = 0; i < area; i++) {
		float B1 = ((float) this->imgData[i].B)/255.f;
		float B2 = ((float) im2.imgData[i].B)/255.f;
		char newB = (((B1 * B2) * 255) + 0.5);
		out.write((char*)&newB, 1);

		float G1 = ((float) this->imgData[i].G)/255;
		float G2 = ((float) im2.imgData[i].G)/255.f;
		char newG = (((G1 * G2) * 255) + 0.5);
		out.write((char*)&newG, 1);

		float R1 = ((float) this->imgData[i].R)/255.f;
		float R2 = ((float) im2.imgData[i].R) / 255.f;
		char newR = (((R1 * R2) * 255) + 0.5);
		out.write((char*)&newR, 1);

	}
}

void Image::Subtract(Image& im2, string output) {
	ofstream out(output, ios_base::binary);
	writeHeader(out);

	for (int i = 0; i < area; i++) {
		int newB = imgData[i].B - im2.imgData[i].B;
		if (newB < 0) {
			newB = 0;
		}
		
		int newG = imgData[i].G - im2.imgData[i].G;
		if (newG < 0) {
			newG = 0;
		}

		int newR = imgData[i].R - im2.imgData[i].R;
		if (newR < 0) {
			newR = 0;
		}

		out.write((char*)&newB, 1);
		out.write((char*)&newG, 1);
		out.write((char*)&newR, 1);
	}
}

void Image::Screen(Image& im2, string output) {
	ofstream out(output, ios_base::binary);
	writeHeader(out);
	for (int i = 0; i < area; i++) {
		float B1 = ((float)this->imgData[i].B) / 255.f;
		float B2 = ((float)im2.imgData[i].B) / 255.f;
		B1 = 1 - B1;
		B2 = 1 - B2;
		char newB = (((1 - (B1 * B2)) * 255) + 0.5);
		out.write((char*)&newB, 1);

		float G1 = ((float)this->imgData[i].G) / 255;
		float G2 = ((float)im2.imgData[i].G) / 255.f;
		G1 = 1 - G1;
		G2 = 1 - G2;
		char newG = (((1 - (G1 * G2)) * 255) + 0.5);
		out.write((char*)&newG, 1);

		float R1 = ((float)this->imgData[i].R) / 255.f;
		float R2 = ((float)im2.imgData[i].R) / 255.f;
		R1 = 1 - R1;
		R2 = 1 - R2;
		char newR = (((1 - (R1 * R2)) * 255)) + 0.5;
		out.write((char*)&newR, 1);
	}
}

void Image::Overlay(Image& im2, string output) {
	ofstream out(output, ios_base::binary);
	writeHeader(out);

	for (int i = 0; i < area; i++) {
		float B1 = ((float)this->imgData[i].B) / 255.f;
		float B2 = ((float)im2.imgData[i].B) / 255.f;
		
		char newB;
		if (B1 < 0.5) {
			newB = (((B1 * B2) * 2 * 255) + 0.5);
		}
		else {
			B1 = 1 - B1;
			B2 = 1 - B2;
			newB = (((1 - (2 * B1 * B2)) * 255) + 0.5);
		}
		out.write((char*)&newB, 1);

		float G1 = ((float)this->imgData[i].G) / 255;
		float G2 = ((float)im2.imgData[i].G) / 255.f;
		char newG;
		if (G1 < 0.5) {
			newG = (((G1 * G2 * 2) * 255) + 0.5);
		}
		else {
			G1 = 1 - G1;
			G2 = 1 - G2;
			newG = (((1 - (2 * G1 * G2)) * 255) + 0.5);
		}
		out.write((char*)&newG, 1);

		float R1 = ((float)this->imgData[i].R) / 255.f;
		float R2 = ((float)im2.imgData[i].R) / 255.f;
		char newR;
		if (R1 < 0.5) {
			newR = (((R1 * R2 * 2) * 255) + 0.5);
		}
		else {
			R1 = 1 - R1;
			R2 = 1 - R2;
			newR = (((1 - (2 * R1 * R2)) * 255) + 0.5);
		}
		out.write((char*)&newR, 1);

	}
}

void Image::Add(int value, int color) {
	int temp;
	if (color == 1) { //red
		for (int i = 0; i < area; i++) {
			temp = imgData[i].R;
			temp += value;
			if (temp > 255) {
				temp = 255;
			}
			imgData[i].R = (char)temp;

		}
	}
	else if (color == 2) { //green
		for (int i = 0; i < area; i++) {
			temp = imgData[i].G;
			temp += value;
			if (temp > 255) {
				temp = 255;
			}
			imgData[i].G = (char)temp;
		}
	}
	else if (color == 3) { // blue
		for (int i = 0; i < area; i++) {
			temp = imgData[i].B;
			temp += value;
			if (temp > 255) {
				temp = 255;
			}
			imgData[i].B = (char)temp;
		}
	}
}

void Image::Scale(int value, int color) {
	float temp;
	if (color == 1) { //red
		for (int i = 0; i < area; i++) {
			temp = imgData[i].R;
			temp *= value;
			temp += 0.5;
			if (temp > 255) {
				temp *= value;
				temp = 255;
			}
			imgData[i].R = (char)temp;
		}
	}
	else if (color == 2) { //green
		for (int i = 0; i < area; i++) {
			temp = imgData[i].G;
			temp *= value;
			temp += 0.5;
			if (temp > 255) {
				temp *= value;
				temp = 255;
			}
			imgData[i].G = (char)temp;
		}
	}
	else if (color == 3) {
		for (int i = 0; i < area; i++) {
			temp = imgData[i].B;
			temp *= value;
			temp += 0.5;
			if (temp > 255) {
				temp *= value;
				temp = 255;
			}
			imgData[i].B = (char)temp;
		}
	}
}

void Image::LoadColor(int color, string output) {
	ofstream out(output, ios_base::binary);
	writeHeader(out);
	if (color == 1) { //red
		for (int i = 0; i < area; i++) {
			int a = imgData[i].R;
			out.write((char*)&a, 1);
			out.write((char*)&a, 1);
			out.write((char*)&a, 1);
		}
	}
	if (color == 2) { //green
		for (int i = 0; i < area; i++) {
			int a = imgData[i].G;
			out.write((char*)&a, 1);
			out.write((char*)&a, 1);
			out.write((char*)&a, 1);
		}
	}
	if (color == 3) { //blue
		for (int i = 0; i < area; i++) {
			int a = imgData[i].B;
			out.write((char*)&a, 1);
			out.write((char*)&a, 1);
			out.write((char*)&a, 1);
		}
	}
}

void Image::Combine(Image& green, Image& blue, string output) {
	ofstream out(output, ios_base::binary);
	writeHeader(out);
	for (int i = 0; i < area; i++) {
		out.write((char*)&blue.imgData[i].B, 1);
		out.write((char*)&green.imgData[i].G, 1);
		out.write((char*)&imgData[i].R, 1);
	}
}

void Image::WriteReverse(string output) {
	ofstream out(output, ios_base::binary);
	writeHeader(out);
	for (int i = area - 1; i >= 0; i--) {
		out.write((char*)&imgData[i].B, 1);
		out.write((char*)&imgData[i].G, 1);
		out.write((char*)&imgData[i].R, 1);
	}
}
