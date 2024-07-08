#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Cells.h"


int main() {

	sf::RenderWindow window;
	Cells cells;
	bool pause = false;

	while (1) {

		if (cells.cell_size > 0 && cells.dencity > 0) {

			window.create(sf::VideoMode(640, 480), "KOTOK");
			cells.start_gen();
			break;
		}
		else {

			std::cout << "Enter cell size >>\t";
			std::cin >> cells.cell_size;

			std::cout << "Enter dencity >>\t";
			std::cin >> cells.dencity;
		}
	}

	

	while (window.isOpen()) {

		sf::Event e;
		while (window.pollEvent(e)) 
			if (e.type == sf::Event::Closed) window.close();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) pause = true;
		
		window.clear();

		if (pause) {

			std::cout << "Enter cell size >>\t"; 
			std::cin >> cells.cell_size; 
			std::cout << "\n";

			std::cout << "Enter dencity >>\t";
			std::cin >> cells.dencity;
			std::cout << "\n";

			if (cells.cell_size > 0 && cells.dencity > 0) {

				cells.field.clear();
				cells.next_field.clear();
				cells.start_gen();
			}
		}
		
		if (!pause) {

			cells.draw(window);
			cells.next_gen();
			cells.threading();
		}

		window.display();
	}

	return 0;
}