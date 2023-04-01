// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream> 

using namespace std;
#include "Image.h"


void TaskOne() {
	Image im = Image("input/layer1.tga");
	Image im2 = Image("input/pattern1.tga");
	im.Multiply(im2, "output/part1.tga");

	Image check1 = Image("output/part1.tga");
	Image check2 = Image("examples/EXAMPLE_part1.tga");
	if (check1.compare(check2)) {
		cout << "Task One Completed Successfully!" << endl;
	}
	else {
		cout << ":((";
	}

}

void TaskTwo() {
	Image im = Image("input/car.tga");
	Image im2 = Image("input/layer2.tga");
	im.Subtract(im2, "output/part2.tga");

	Image check1 = Image("output/part2.tga");
	Image check2 = Image("examples/EXAMPLE_part2.tga");
	if (check1.compare(check2)) {
		cout << "Task Two Completed Successfully!" << endl;
	}
	else {
		cout << ":((";
	}
}

void TaskThree() {
	Image im = Image("input/layer1.tga");
	Image im2 = Image("input/pattern2.tga");
	im.Multiply(im2, "output/part3.tga");
	Image im3 = Image("output/part3.tga");
	Image im4 = Image("input/text.tga");

	im3.Screen(im4, "output/part3.tga");

	Image check1 = Image("output/part3.tga");
	Image check2 = Image("examples/EXAMPLE_part3.tga");
	if (check1.compare(check2)) {
		cout << "Task Three Completed Successfully!" << endl;
	}
	else {
		cout << ":((";
	}

}

void TaskFour() {
	Image im = Image("input/layer2.tga");
	Image im2 = Image("input/circles.tga");
	Image im3 = Image("input/pattern2.tga");

	im.Multiply(im2, "output/part4.tga");
	Image im4 = Image("output/part4.tga");
	im4.Subtract(im3, "output/part4.tga");

	Image check1 = Image("output/part4.tga");
	Image check2 = Image("examples/EXAMPLE_part4.tga");
	if (check1.compare(check2)) {
		cout << "Task Four Completed Successfully!" << endl;
	}
	else {
		cout << ":((";
	}
}

void TaskFive() {
	Image im = Image("input/layer1.tga");
	Image im2 = Image("input/pattern1.tga");
	im2.Overlay(im, "output/part5.tga");

	Image check1 = Image("output/part5.tga");
	Image check2 = Image("examples/EXAMPLE_part5.tga");
	if (check1.compare(check2)) {
		cout << "Task Five Completed Successfully!" << endl;
	}
	else {
		cout << ":((";
	}
}

void TaskSix() {
	Image im = Image("input/car.tga");
	im.Add(200, 2); //add 200 to green
	im.write("output/part6.tga");

	Image check2 = Image("examples/EXAMPLE_part6.tga");
	if (im.compare(check2)) {
		cout << "Task Six Completed Successfully!" << endl;
	}
	else {
		cout << ":((" << endl;
	}
}

void TaskSeven() {
	Image im = Image("input/car.tga");
	im.Scale(4, 1); //scaling red
	im.Scale(0, 3); //scalingblue
	im.write("output/part7.tga");

	Image check2 = Image("examples/EXAMPLE_part7.tga");

	if (im.compare(check2)) {
		cout << "Task Seven Completed Successfully!" << endl;
	}
	else {
		cout << ":((" << endl;
	}
}

void TaskEight() {
	Image im = Image("input/car.tga");
	//Image im2 = Image("C:/Users/Russell/Documents/Semester ONE/ImageProcessing/examples/EXAMPLE_part8_r.tga");
	im.LoadColor(1, "output/part8_r.tga");
	im.LoadColor(2, "output/part8_g.tga");
	im.LoadColor(3, "output/part8_b.tga");

	Image check1r = Image("output/part8_r.tga");
	Image check1b = Image("output/part8_b.tga");
	Image check1g = Image("output/part8_g.tga");

	Image check2r = Image("examples/EXAMPLE_part8_r.tga");
	Image check2g = Image("examples/EXAMPLE_part8_g.tga");
	Image check2b = Image("examples/EXAMPLE_part8_b.tga");
	if (check1r.compare(check2r) && check1b.compare(check2b) && check1g.compare(check2g)) {
		cout << "Task Eight Completed Successfully!" << endl;
	}
	else {
		cout << ":((" << endl;
	}
}

void TaskNine() {
	Image red = Image("input/layer_red.tga");
	Image green = Image("input/layer_green.tga");
	Image blue = Image("input/layer_blue.tga");
	red.Combine(green, blue, "output/part9.tga");

	Image check1 = Image("output/part9.tga");
	Image check2 = Image("examples/EXAMPLE_part9.tga");
	if (check1.compare(check2)) {
		cout << "Task Nine Completed Successfully!" << endl;
	}
	else {
		cout << ":((";
	}
}

void TaskTen() {
	Image im = Image("input/text2.tga");
	im.WriteReverse("output/part10.tga");

	Image check1 = Image("output/part10.tga");
	Image check2 = Image("examples/EXAMPLE_part10.tga");
	if (check1.compare(check2)) {
		cout << "Task Ten Completed Successfully!" << endl;
	}
	else {
		cout << ":((";
	}
}

int main()
{
	TaskOne();
	TaskTwo();
	TaskThree();
	TaskFour();
	TaskFive();
	TaskSix();
	TaskSeven();
	TaskEight();
	TaskNine();
	TaskTen();
	return 0;

}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
