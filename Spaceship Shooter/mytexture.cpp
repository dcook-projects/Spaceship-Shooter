#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "mytexture.h"
#include "app.h"

MyTexture::MyTexture() {
	texture = nullptr;
	width = 0;
	height = 0;
}

MyTexture::~MyTexture() {
	free();
}

void MyTexture::setAlpha(unsigned int alpha) {
	SDL_SetTextureAlphaMod(texture, alpha);
}

bool MyTexture::loadFromFile(App& app, std::string path) {
	free();

	//The final texture
	SDL_Texture* newTexture = nullptr;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {

		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(app.renderer, loadedSurface);
		if (newTexture == nullptr) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else {
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	texture = newTexture;
	return texture != nullptr;
}

bool MyTexture::loadFromRenderedText(App& app, std::string textureText, SDL_Color textColor) {
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(app.font, textureText.c_str(), textColor);
	if (textSurface != nullptr) {

		//Create texture from surface pixels
		texture = SDL_CreateTextureFromSurface(app.renderer, textSurface);
		if (texture == nullptr) {
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else {
			width = textSurface->w;
			height = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}
	else {
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}

	//Return success
	return texture != nullptr;
}

void MyTexture::free() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
		width = 0;
		height = 0;
	}
}

void MyTexture::render(App& app, int x, int y, SDL_Rect* clip) 
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, width, height };

	//Set clip rendering dimensions
	if (clip != nullptr)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy(app.renderer, texture, clip, &renderQuad);
}

void MyTexture::render(App& app, const SDL_Rect& renderQuad, SDL_Rect* clip)
{
	//Render to screen
	SDL_RenderCopy(app.renderer, texture, clip, &renderQuad);
}

int MyTexture::getWidth()
{
	return width;
}

int MyTexture::getHeight()
{
	return height;
}