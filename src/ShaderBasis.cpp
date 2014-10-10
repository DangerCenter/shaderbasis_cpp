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

#include <iostream>
#include <map>
#include <cmath>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

#include "ShaderVal.h"
#include "ShaderFunctions.h"

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


int main() {
	sf::RenderWindow window(sf::VideoMode(640, 640), "ShaderBasis");
	sf::Image buffer;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Clock clock;
	float lastupdate = 0;
	stringstream ss;

	buffer.create(640, 640, sf::Color::Red);
	texture.loadFromImage(buffer);
	sprite.setTexture(texture);
	UpdateBuffer(buffer, texture, clock);

	while (window.isOpen())	{
			UpdateBuffer(buffer, texture, clock);

			if(lastupdate+DELTA_UPDATE_FPS < clock.getElapsedTime().asSeconds())	{
				lastupdate = clock.getElapsedTime().asSeconds();
				ss.str(string());
				ss.clear();
				ss << "ShaderBasis - FPS: ";
				ss << 1.f / deltaFrame;
				ss << " - Delta: ";
				ss << deltaFrame << " ms";
				window.setTitle(ss.str());
			}
	        // check all the window's events that were triggered since the last iteration of the loop
	        sf::Event event;
	        while (window.pollEvent(event))
	        {
	            // "close requested" event: we close the window
	            if (event.type == sf::Event::Closed)
	                window.close();
	        }

	        // clear the window with black color
	        window.clear(sf::Color::Black);

	        // draw everything here...
	        // window.draw(...);
	        window.draw(sprite);
	        // end the current frame
	        window.display();
	    }
	return 0;
}
