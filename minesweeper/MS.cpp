MS::MS() {
	mineNo = 50;
	dim1 = 25;
	dim2 = 16;
	area = dim1 * dim2;
	inDebug = false;
	smiley = "face_happy";
	for (int i = 0; i < dim1; i++) {
		for (int j = 0; j < dim2; j++) {
			field.push_back(0);
			curFld.push_back(10);
		}
	}
	seedMine();
	addNumbers();
}

void MS::click(int pos) {
	if (curFld[pos] == 10 && smiley != "face_lose" && smiley != "face_win") {
		if (curFld[pos] == 9) {
			cout << "You can't click something you've flagged!" << endl;
		}
		else if (field[pos] == -1) {
			revealBombs(true);
		}
		else {
			curFld[pos] = field[pos];
			revealAdjacents(pos);
		}
	}
}

void MS::flag(int pos) {
	if (smiley != "face_lose" && smiley != "face_win") {
		if (curFld[pos] != 9) {
			curFld[pos] = 9;
			mineNo--;
			
		}
		else {
			curFld[pos] = 10;
			mineNo++;
		}
	}
}

void MS::seedMine() {
	vector<int> mines;
	int count = mineNo;
	bool reuse = false;
	while (count > 0) {
		int temp = rand() % area;
		for (int i = 0; i < mines.size(); i++) {
			if (temp == mines[i]) {
				reuse = true;
			}
		}
		if (!reuse) {
			count--;
			field[temp] = -1;
			mines.push_back(temp);
		}
		else {
			reuse = false;
		}
	}
}

void MS::addNumbers() {
	for (int i = 0; i < area; i++) {
		if (field[i] != -1) {
			int newVal = checkAdjacent(i);
			field[i] = newVal;
		}
	}
}

int MS::checkAdjacent(int pos) {
	//first: the four corners
	int count = 0;
	if (pos == 0) {
		if (field[pos + 1] == -1) { //below
			count++;
		}
		if (field[pos + dim2] == -1) { //right
			count++;
		}
		if (field[pos + dim2 + 1] == -1) { //lower right
			count++;
		}
	}
	else if (pos == dim2 - 1) {
		if (field[pos - 1] == -1) { //above
			count++;
		}
		if (field[pos + dim2] == -1) { //right
			count++;
		}
		if (field[pos + dim2 - 1] == -1) { //upper right
			count++;
		}
	}
	else if (pos == area - dim2) {
		if (field[pos - dim2] == -1) { //left
			count++;
		}
		if (field[pos + 1] == -1) { //below
			count++;
		}
		if (field[pos - dim2 + 1] == -1) { //lower left
			count++;
		}
	}
	else if (pos == area - 1) {
		if (field[pos - dim2] == -1) { //left
			count++;
		}
		if (field[pos - 1] == -1) { //above
			count++;
		}
		if (field[pos - dim2 - 1] == -1) { //upper left
			count++;
		}
	}
	else if (pos < dim2) { //left side
		if (field[pos - 1] == -1) {
			count++;
		}
		if (field[pos + 1] == -1) {
			count++;
		}
		if (field[pos + dim2 - 1] == -1) {
			count++;
		}
		if (field[pos + dim2] == -1) {
			count++;
		}
		if (field[pos + dim2 + 1] == -1) {
			count++;
		}
	}
	else if (pos > 384) {
		if (field[pos - 1] == -1) {
			count++;
		}
		if (field[pos + 1] == -1) {
			count++;
		}
		if (field[pos - dim2 - 1] == -1) {
			count++;
		}
		if (field[pos - dim2] == -1) {
			count++;
		}
		if (field[pos - dim2 + 1] == -1) {
			count++;
		}
	}
	else if (pos % dim2 == 0) {
		if (field[pos - dim2] == -1) {
			count++;
		}
		if (field[pos + dim2] == -1) {
			count++;
		}
		if (field[pos + 1] == -1) {
			count++;
		}
		if (field[pos - dim2 + 1] == -1) {
			count++;
		}
		if (field[pos + dim2 + 1] == -1) {
			count++;
		}
	}
	else if ((pos + 1) % dim2 == 0) {
		if (field[pos - dim2] == -1) {
			count++;
		}
		if (field[pos + dim2] == -1) {
			count++;
		}
		if (field[pos - 1] == -1) {
			count++;
		}
		if (field[pos - dim2 - 1] == -1) {
			count++;
		}
		if (field[pos + dim2 - 1] == -1) {
			count++;
		}
	}
	else { //the normal ones
		if (field[pos + 1] == -1) {
			count++;
		}
		if (field[pos - 1] == -1) {
			count++;
		}
		if (field[pos + dim2] == -1) {
			count++;
		}
		if (field[pos - dim2] == -1) {
			count++;
		}
		if (field[pos + dim2 + 1] == -1) {
			count++;
		}
		if (field[pos + dim2 - 1] == -1) {
			count++;
		}
		if (field[pos - dim2 - 1] == -1) {
			count++;
		}
		if (field[pos - dim2 + 1] == -1) {
			count++;
		}
	}
	return count;
}

void MS::revealBombs(bool loss) {
	for (int i = 0; i < field.size(); i++) {
		if (field[i] == -1) {
			curFld[i] = -1;
		}
	}
	if (loss) {
		smiley = "face_lose";
	}
	else if (inDebug) {
		for (int i = 0; i < field.size(); i++) {
			if (field[i] == -1) {
				curFld[i] = 10;
			}
		}
		inDebug = false;
	}
	else {
		inDebug = true;
	}

}

void MS::reveal(int pos) {
	if (field[pos] != -1 && field[pos] != 9 && curFld[pos] == 10) {
		curFld[pos] = field[pos];
		if (field[pos] == 0) {
			revealAdjacents(pos);
		}
	}
}

void MS::revealAdjacents(int pos) {
	//first: the four corners
	if (pos == 0) {
		reveal(pos + 1); //below
		reveal(pos + dim2); //right
		reveal(pos + dim2 + 1); //lower right
	}
	else if (pos == dim2 - 1) {
		reveal(pos - 1); //above
		reveal(pos + dim2); //right
		reveal(pos + dim2 - 1); //upper right
	}
	else if (pos == area - dim2) {
		reveal(pos - dim2); //left
		reveal(pos + 1); //below
		reveal(pos - dim2 + 1); //lower left
	}
	else if (pos == area - 1) {
		reveal(pos - dim2); //left
		reveal(pos - 1); //above
		reveal(pos - dim2 - 1); //upper left
	}
	else if (pos < dim2) { //left side
		reveal(pos - 1);
		reveal(pos + 1);
		reveal(pos + dim2 - 1);
		reveal(pos + dim2);
		reveal(pos + dim2 + 1);
	}
	else if (pos > 384) {
		reveal(pos - 1);
		reveal(pos + 1);
		reveal(pos - dim2 - 1);
		reveal(pos - dim2);
		reveal(pos - dim2 + 1);
	}
	else if (pos % dim2 == 0) {
		reveal(pos - dim2);
		reveal(pos + dim2);
		reveal(pos + 1);
		reveal(pos - dim2 + 1);
		reveal(pos + dim2 + 1);
	}
	else if ((pos + 1) % dim2 == 0) {
		reveal(pos - dim2);
		reveal(pos + dim2);
		reveal(pos - 1);
		reveal(pos - dim2 - 1);
		reveal(pos + dim2 - 1);
	}
	else { //the normal ones
		reveal(pos + 1);
		reveal(pos - 1);
		reveal(pos + dim2);
		reveal(pos - dim2);
		reveal(pos + dim2 + 1);
		reveal(pos + dim2 - 1);
		reveal(pos - dim2 - 1);
		reveal(pos - dim2 + 1);
	}

}

void MS::revealSquares(int pos) {
	if (field[pos] == 0) {
		curFld[pos] = field[pos];
		//Reveal the adjacents
		revealAdjacents(pos);

	}
	else if (field[pos] != -1 && field[pos] != 9) {
		curFld[pos] = field[pos];
	}

}

void MS::loadFile(string filename) {
	smiley = "face_happy";
	field.clear();
	curFld.clear();
	int counter = 0;
	ifstream f1(filename);
	for (int i = 0; i < dim2; i++) {
		for (int j = 0; j < dim1; j++) {
			field.push_back(0);
			curFld.push_back(10);
		}
	}
	for (int i = 0; i < 16; i++) {
		for (int j = i; j < 400; j += 16) {
			char a;
			f1 >> a;
			int b = a - '0';
			if (b == 1) {
				b -= 2;
			}
			field[j] = b;
			if (b == -1) {
				counter++;
			}
		}
	}
	mineNo = counter;
	addNumbers();
}

void MS::restart() {
	mineNo = 50;
	smiley = "face_happy";
	field.clear();
	curFld.clear();
	for (int i = 0; i < dim1; i++) {
		for (int j = 0; j < dim2; j++) {
			field.push_back(0);
			curFld.push_back(10);
		}
	}
	seedMine();
	addNumbers();
}

void MS::victory() {
	bool win = true;
	for (int i = 0; i < area; i++) {
		if (field[i] != -1) {
			if (field[i] != curFld[i]) {
				win = false;
			}
		}
	}

	if (win) {
		smiley = "face_win";
	}
}