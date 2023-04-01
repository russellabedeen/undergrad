#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "MS.h"
#include "MS.cpp"
#include "TextureManager.h"
#include "TextureManager.cpp"
using namespace std;
using namespace sf;

void LoadTextures()
{
	vector<string> imageNames = vector<string>{ "mine", "tile_hidden", "tile_revealed",
	"number_1", "number_2", "number_3", "number_4", "number_5",
	"number_6", "number_7", "number_8", "flag", "face_happy",
	"face_win.png", "face_lose", "digits", "debug",
	"test_1", "test_2", "test_3" };

	for (int i = 0; i < imageNames.size(); i++) {
		TextureManager::LoadTexture(imageNames[i]);
	}
}

void toTexture(vector<int>& field, vector<string>& output) {
	output.clear();
	vector<string> imageNames = vector<string>{ "mine", "tile_revealed",
	"number_1", "number_2", "number_3", "number_4", "number_5",
	"number_6", "number_7", "number_8", "flag", "tile_hidden", "face_happy",
	"face_win.png", "face_lose", "digits", "debug",
	"test_1", "test_2", "test_3" };

	for (int i = 0; i < field.size(); i++) {
		string imgName = imageNames[field[i] + 1];
		output.push_back(imgName);
	}
}

int main()
{
	MS obj = MS();
	RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");
	Color white = Color(255, 255, 255);
	while (window.isOpen())
	{
		Event event;
		int counter = 0;
		while (window.pollEvent(event))
		{
			switch (event.type) {
				case Event::Closed: {
					window.close();
				}
				case Event::MouseButtonReleased: {
					if (event.mouseButton.button == Mouse::Right) {
						int xPos = (Mouse::getPosition(window).x) / 32;
						int yPos = (Mouse::getPosition(window).y) / 32;
						int p = ((xPos) * 16) + yPos;
						if (xPos >= 0 && xPos < 25 && yPos >= 0 && yPos < 16) {
							obj.flag(p);
						}
					}
					else if (event.mouseButton.button == Mouse::Left) {
						int xPos = (Mouse::getPosition(window).x) / 32;
						int yPos = (Mouse::getPosition(window).y) / 32;
						int p = ((xPos) * 16) + yPos;
						if (xPos >= 0 && xPos < 25 && yPos >= 0 && yPos < 16) {
							obj.click(p);
						}
						if (xPos >= 11 && xPos <= 13 && yPos >= 16 && yPos <= 17) {
							obj.restart();
						}
						if (xPos >= 15 && xPos < 17 && yPos >= 16 && yPos <= 17) {
							obj.revealBombs(false);
						}
						if (xPos >= 17 && xPos < 19 && yPos >= 16 && yPos <= 17) {
							obj.loadFile("boards/testboard1.brd");
						}
						if (xPos >= 19 && xPos < 21 && yPos >= 16 && yPos <= 17) {
							obj.loadFile("boards/testboard2.brd");
						}
						if (xPos >= 21 && xPos < 23 && yPos >= 16 && yPos <= 17) {
							obj.loadFile("boards/testboard3.brd");
						}
					}
				}
			}
		}

		window.clear(white);

		vector<string> output;
		toTexture(obj.curFld, output);
		for (int i = 0; i < 25; i++) {
			for (int j = 0; j < 16; j++) {
				Sprite sp, bsp;
				if (obj.curFld[counter] == 9) {
					bsp.setTexture(TextureManager::GetTexture("tile_hidden"));
				}
				else {
					bsp.setTexture(TextureManager::GetTexture("tile_revealed"));
				}
				bsp.setPosition(i * 32, j * 32);
				sp.setTexture(TextureManager::GetTexture(output[counter]));
				sp.setPosition(i * 32, j * 32);

				window.draw(bsp);
				window.draw(sp);
				counter++;
			}
		}
		obj.victory();
		Sprite sp2, sp3, sp4, sp5, debug, test1, test2, test3;
		int t = obj.mineNo / 10;
		int o = obj.mineNo % 10;
		sp2.setTexture(TextureManager::GetTexture("digits"));
		if (obj.mineNo >= 0) {
			sp2.setTextureRect(IntRect(0, 0, 21, 32));
		}
		else {
			t *= -1;
			o *= -1;
			sp2.setTextureRect(IntRect(210, 0, 21, 32));
		}
		sp2.setPosition(0, 16 * 32);

		sp3.setTexture(TextureManager::GetTexture("digits"));
		sp3.setTextureRect(IntRect(21 * (t), 0, 21, 32));
		sp3.setPosition(21, 16 * 32);

		sp4.setTexture(TextureManager::GetTexture("digits"));
		sp4.setTextureRect(IntRect(21 * o, 0, 21, 32));
		sp4.setPosition(42, 16 * 32);
		
		sp5.setTexture(TextureManager::GetTexture(obj.smiley));
		sp5.setPosition(368, 16 * 32);
		
		debug.setTexture(TextureManager::GetTexture("debug"));
		debug.setPosition(16 * 32 - 16, 16 * 32);

		test1.setTexture(TextureManager::GetTexture("test_1"));
		test1.setPosition(17 * 32 + 16, 16 * 32);
		test2.setTexture(TextureManager::GetTexture("test_2"));
		test2.setPosition(19 * 32 + 16, 16 * 32);
		test3.setTexture(TextureManager::GetTexture("test_3"));
		test3.setPosition(21 * 32 + 16, 16 * 32);

		window.draw(sp2);
		window.draw(sp3);
		window.draw(sp4);
		window.draw(sp5);
		window.draw(debug);
		window.draw(test1);
		window.draw(test2);
		window.draw(test3);


		window.display();
	}
	TextureManager::Clear();
	return 0;
}