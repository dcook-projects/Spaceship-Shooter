#pragma once

#include <string>
#include <SDL.h>
#include <SDL_image.h>

struct App;

class MyTexture
{
public:
	MyTexture();
	~MyTexture();

	//Loads image at specified path
	bool loadFromFile(App& app, std::string path);

	//Creates image from a string
	bool loadFromRenderedText(App& app, std::string textureText, SDL_Color textColor);

	void free();
	void setAlpha(unsigned int alpha) const;

	//Renders texture at given point or rect
	void render(App& app, int x, int y, SDL_Rect* clip = nullptr) const;
	void render(App& app, const SDL_Rect& renderQuad, SDL_Rect* clip = nullptr) const;

	int getWidth() const;
	int getHeight() const;
	
private:
	int width;
	int height;

	//The actual hardware texture
	SDL_Texture *texture;
};