//============================================================================
// Name        : ShaderBasis.cpp
// Author      : Lucas Teske
// Version     :
// Copyright   : 2014 - DangerCenter
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

void UpdateBuffer(sf::Image &img, sf::Texture &tex)	{
	for(int i=0;i<640;i++)	{
		img.setPixel(i,i, sf::Color(0,0,0,255));
	}
	tex.update(img);
}


void Draw(sf::Image &img, sf::Texture &tex)	{

}

int main() {
	sf::RenderWindow window(sf::VideoMode(640, 640), "ShaderBasis");
	sf::Image buffer;
	sf::Sprite sprite;
	sf::Texture texture;

	buffer.create(640, 640, sf::Color::Red);
	texture.loadFromImage(buffer);
	sprite.setTexture(texture);
	UpdateBuffer(buffer, texture);

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	while (window.isOpen())
	    {
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
