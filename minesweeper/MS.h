#pragma once
#include "Box.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
using namespace sf;

class MS {
public:
	vector<int> field;
	vector<int>curFld;
	int mineNo;
	int dim1;
	int dim2;
	int area;
	bool inDebug;
	string smiley;

	MS();
	void click(int pos);
	void flag(int pos);
	void seedMine();
	void addNumbers();
	int checkAdjacent(int pos);
	void revealBombs(bool loss);
	void reveal(int pos);
	void revealAdjacents(int pos);
	void revealSquares(int pos);
	void loadFile(string filename);
	void restart();
	void victory();
};