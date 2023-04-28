// Mandelbrot Set.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ComplexPlane.h"



int main()
{
	Font font;
	Text text;


	font.loadFromFile("arial.ttf");

	text.setCharacterSize(30);
	text.setFont(font);

	double width = VideoMode::getDesktopMode().width;
	double height = VideoMode::getDesktopMode().height;

	VideoMode vm(width, height);

	float aspect = height / width;

	RenderWindow window(vm, "Mandelbrot", Style::Default);

	ComplexPlane plane(aspect);

	enum states { CALCULATING, DISPLAYING };
	states state = CALCULATING; //the default state

	VertexArray v;
	v.setPrimitiveType(Points);
	v.resize(height * width);

	size_t numIter = 0;
	while (window.isOpen())
	{
		Event event;

		if (state == CALCULATING)
		{
			for (int j = 0; j < width; j++)
			{
				for (int i = 0; i < height; i++)
				{
					Vector2i pixLoc;
					pixLoc.x = j;
					pixLoc.y = i;
					v[j + i * width].position = { (float)j, (float)i };
					Vector2f coord = window.mapPixelToCoords(pixLoc, plane.getView());
					numIter = plane.countIterations(coord);
					Uint8 r;
					Uint8 g;
					Uint8 b;
					plane.iterationsToRGB(numIter, r, g, b);
					v[j + i * width].color = { r, g, b };

				}
			}
			state = DISPLAYING;
			plane.loadText(text);
			window.clear();
			window.draw(v);
			window.draw(text);
			window.display();
		}

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}
			if (event.type == Event::MouseMoved)
			{
				Vector2f vec = window.mapPixelToCoords(Mouse::getPosition(window), plane.getView());
				plane.setMouseLocation(vec);
				state = CALCULATING;
			}
			if (event.type == Event::MouseButtonPressed)
			{
				Vector2f vec = window.mapPixelToCoords(Mouse::getPosition(window), plane.getView());
				plane.setCenter(vec);
				state = CALCULATING;
			}
			if (event.mouseButton.button = sf::Mouse::Left)
			{
				plane.zoomIn();
			}
			else if (event.mouseButton.button = sf::Mouse::Right)
			{
				plane.zoomOut();
			}
		}
	}
		
	return 0;
}

