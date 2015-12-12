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

#include <iostream>     // std::cout
#include <functional>   // std::bind
#include <map>
#include <cmath>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SDL.h>

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

#include "ShaderVal.h"
#include "ShaderFunctions.h"
#include "ShaderThreadArgs.h"


#define WIDTH 640
#define HEIGHT 480
#define BPP 4
#define DEPTH 32


using namespace std;

float deltaFrame = 0;

#define DELTA_UPDATE_FPS 1.f
#define THREADS 8

// https://www.shadertoy.com/view/Xd33D7

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

void ShaderAction(ShaderThreadArgs &args) {
  int x,y;
  Vec2 coord;
  ShaderVal res = (*args.ext)["res"];

  for(y=args.startLine;y<args.endLine;y++) {
    for(x=0;x<args.width;x++) {
      coord.x = (x / res.v2.x) * 2.f - 0.5f;
      coord.y = (y / res.v2.y) * 2.f - 0.5f;
      Vec4 data = Shader(coord, *args.ext);
      clamp(data, 1.f);
      args.pixels[x + y * args.width] = 255 << 24 | (uint32_t)(data.r * 255) << 16 | (uint32_t)(data.g * 255) << 8 | (uint32_t)(data.b * 255) << 0;
    }
  }
}

void DrawScreen(SDL_Renderer *renderer, Uint32 * pixels, SDL_Texture * texture, int width, int height, sf::Clock &time)	{
	int x, y, ytimesw;
	map<string, ShaderVal> ext;
	ShaderVal timeval, res;
	timeval.f = time.getElapsedTime().asSeconds();
	deltaFrame = timeval.f;
	res.v2.x = width;
	res.v2.y = height;
	ext["time"] = timeval;
	ext["res"] = res;
	Vec2 coord;
  sf::Thread *threads[THREADS];

  for(int i=0;i<THREADS;i++) {
    ShaderThreadArgs args;
    args.width = width;
    args.height = height;
    args.startLine = (height / THREADS) * i;
    args.endLine = (height / THREADS) * ( i + 1);
    args.ext = &ext;
    args.pixels = pixels;

    threads[i] = new sf::Thread(&ShaderAction, args);
    threads[i]->launch();
  }

  for(int i=0;i<THREADS;i++) {
    threads[i]->wait();
  }

  SDL_UpdateTexture(texture, NULL, pixels, 640 * sizeof(Uint32));
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);

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
	SDL_Event event;

	int keypress = 0;
  Uint32 * pixels = new Uint32[640 * 480];

  SDL_Window *sdlWindow;
  SDL_Renderer *sdlRenderer;
  SDL_CreateWindowAndRenderer(640, 480,  SDL_WINDOW_RESIZABLE, &sdlWindow, &sdlRenderer);
  SDL_Texture * texture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 640, 480);

	while(!keypress)	{
		if(lastupdate+DELTA_UPDATE_FPS < clock.getElapsedTime().asSeconds())	{
			lastupdate = clock.getElapsedTime().asSeconds();
			cout << "ShaderBasis - FPS: ";
			cout << 1.f / deltaFrame;
			cout << " - Delta: ";
			cout << deltaFrame << " ms" << endl;
		}

		DrawScreen(sdlRenderer, pixels, texture, 640, 480, clock);
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

  delete[] pixels;
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(sdlRenderer);
	SDL_Quit();
#endif
	return 0;
}
