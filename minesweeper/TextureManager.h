#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
using std::string;
using std::map;

class TextureManager
{
	// static == one and only one of this thing
	static map<string, sf::Texture> textures;
public:
	static void LoadTexture(string textureName);
	static sf::Texture& GetTexture(string textureName);
	static void Clear() { textures.clear(); }
};

