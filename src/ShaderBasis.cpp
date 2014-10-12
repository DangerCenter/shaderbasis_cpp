//============================================================================
// Name        : ShaderBasis.cpp
// Author      : Lucas Teske
// Version     :
// Copyright   : 2014 - DangerCenter
// Description : ShaderBasis Emulator
//============================================================================

/**  ____  _               _           ____            _
 * / ___|| |__   __ _  __| | ___ _ __| __ )  __ _ ___(_)___
 * \___ \| '_ \ / _` |/ _` |/ _ \ '__|  _ \ / _` / __| / __|
 *  ___) | | | | (_| | (_| |  __/ |  | |_) | (_| \__ \ \__ \
 * |____/|_| |_|\__,_|\__,_|\___|_|  |____/ \__,_|___/_|___/
 */

#define __USE_SDL__

#include <iostream>
#include <map>
#include <cmath>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SDL.h>
#include <SDL/SDL.h>

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

#include "ShaderVal.h"
#include "ShaderFunctions.h"


#define WIDTH 640
#define HEIGHT 480
#define BPP 4
#define DEPTH 32


using namespace std;

float deltaFrame = 0;

#define DELTA_UPDATE_FPS 1.f

/*
// TESTING SHADER
Vec4 Shader(Vec2 &coord, map<string, ShaderVal> &ext)	{
	Vec4 color(1,1,1,1);
	Vec2 uv = coord;
    if(uv.x < 0.5 && uv.y < 0.5) {
        color.x = 1.0;
        color.y = 0.0;
        color.z = 0.0;
    }else if(uv.x > 0.5 && uv.y < 0.5) {
        color.x = 0.0;
        color.y = 1.0;
        color.z = 0.0;
    }else if(uv.x > 0.5 && uv.y > 0.5) {
        color.x = 0.0;
        color.y = 0.0;
        color.z = 1.0;
    }else if(uv.x < 0.5 && uv.y > 0.5) {
        color.x = 1.0;
        color.y = 1.0;
        color.z = 1.0;
    }
    return color;
}*/
Vec4 Shader(Vec2 &coord, map<string, ShaderVal> &ext)	{

	Vec2 position = coord - 0.5f;
	Vec3 colour = Vec3(0.0);
	float density = 0.15;
	float amplitude = 0.3;
	float frequency = 5.0;
	float scroll = 0.4;

	colour += Vec3(0.1f, 0.05f, 0.05f) * (1.0f / abs((position.y + (amplitude * sin(((position.x-0.0) + ext["time"].f * scroll) *frequency)))) * density);
	colour += Vec3(0.05f, 0.1f, 0.05f) * (1.0f / abs((position.y + (amplitude * sin(((position.x-0.3) + ext["time"].f * scroll) *frequency)))) * density);
	colour += Vec3(0.05f, 0.05f, 0.1f) * (1.0f / abs((position.y + (amplitude * sin(((position.x-0.6) + ext["time"].f * scroll) *frequency)))) * density);

	return Vec4( colour, 1.0f );
}

#ifndef __USE_SDL__

void UpdateBuffer(sf::Image &img, sf::Texture &tex, sf::Clock &time)	{
	map<string, ShaderVal> ext;
	ShaderVal timeval, res;
	timeval.f = time.getElapsedTime().asSeconds();
	deltaFrame = timeval.f;
	res.v2.x = img.getSize().x;
	res.v2.y = img.getSize().y;
	ext["time"] = timeval;
	ext["res"] = res;
	Vec2 coord;
	for(int y=0;y<res.v2.y;y++)	{
		for(int x=0;x<res.v2.x;x++)	{
			coord.x = (x / res.v2.x) * 2.f - 0.5f;
			coord.y = (y / res.v2.y) * 2.f - 0.5f;
			Vec4 data = Shader(coord, ext);
			clamp(data,1.f);
			img.setPixel(x,y, sf::Color(data.r*255,data.g*255,data.b*255,data.a*255));
		}
	}
	tex.update(img);
	deltaFrame = time.getElapsedTime().asSeconds() - deltaFrame;
}

#else
inline void setpixel(SDL_Surface *screen, int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
    Uint32 *pixmem32;
    Uint32 colour;

    colour = SDL_MapRGB( screen->format, r, g, b );

    pixmem32 = (Uint32*) screen->pixels  + y + x;
    *pixmem32 = colour;
}

void DrawScreen(SDL_Surface* screen, sf::Clock &time)	{
	int x, y, ytimesw;
	map<string, ShaderVal> ext;
	ShaderVal timeval, res;
	timeval.f = time.getElapsedTime().asSeconds();
	deltaFrame = timeval.f;
	res.v2.x = screen->w;
	res.v2.y = screen->h;
	ext["time"] = timeval;
	ext["res"] = res;
	Vec2 coord;

	if(SDL_MUSTLOCK(screen))
		if(SDL_LockSurface(screen) < 0) return;


	for(y = 0; y < screen->h; y++ )	{
		ytimesw = y*screen->pitch/BPP;
		for( x = 0; x < screen->w; x++ )	{
			coord.x = (x / res.v2.x) * 2.f - 0.5f;
			coord.y = (y / res.v2.y) * 2.f - 0.5f;
			Vec4 data = Shader(coord, ext);
			clamp(data,1.f);
			setpixel(screen, x, ytimesw, data.r*255, data.g*255, data.b*255);
		}
	}

	if(SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);

	SDL_Flip(screen);
	deltaFrame = time.getElapsedTime().asSeconds() - deltaFrame;
}



#endif


int main() {
	sf::Clock clock;
	float lastupdate = 0;
	stringstream ss;
#ifndef __USE_SDL__
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "ShaderBasis");
	sf::Image buffer;
	sf::Sprite sprite;
	sf::Texture texture;

	buffer.create(640, 640, sf::Color::Red);
	texture.loadFromImage(buffer);
	sprite.setTexture(texture);
	UpdateBuffer(buffer, texture, clock);

	while (window.isOpen())	{
		UpdateBuffer(buffer, texture, clock);

		if(lastupdate+DELTA_UPDATE_FPS < clock.getElapsedTime().asSeconds())	{
			lastupdate = clock.getElapsedTime().asSeconds();
			cout << "ShaderBasis - FPS: ";
			cout << 1.f / deltaFrame;
			cout << " - Delta: ";
			cout << deltaFrame << " ms" << endl;
		}
		sf::Event event;
		while (window.pollEvent(event))	{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);

		window.draw(sprite);
		window.display();
	}
#else
	SDL_Surface *screen;
	SDL_Event event;

	int keypress = 0;
	if (SDL_Init(SDL_INIT_VIDEO) < 0 ) return 1;

	if (!(screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_HWSURFACE)))	{
		SDL_Quit();
		return 1;
	}

	while(!keypress)	{
		if(lastupdate+DELTA_UPDATE_FPS < clock.getElapsedTime().asSeconds())	{
			lastupdate = clock.getElapsedTime().asSeconds();
			cout << "ShaderBasis - FPS: ";
			cout << 1.f / deltaFrame;
			cout << " - Delta: ";
			cout << deltaFrame << " ms" << endl;
		}
		DrawScreen(screen,clock);
		while(SDL_PollEvent(&event))	{
			switch (event.type)	{
				case SDL_QUIT:
				keypress = 1;
				break;
				case SDL_KEYDOWN:
				keypress = 1;
				break;
				}
		}
	}

	SDL_Quit();
#endif
	return 0;
}
