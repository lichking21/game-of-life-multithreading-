#ifndef CELLS_H
#define CELLS_H

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <mutex>

class Cells {

private:
	int rows = 0;
	int cols = 0;
	int count_neightbor(int y, int x);

public:
	int dencity = 0;
	int cell_size = 0;

	std::vector<std::vector<bool>> field;
	std::vector<std::vector<bool>> next_field; // field for new generations

	void start_gen();
	void next_gen();
	void draw(sf::RenderWindow& window);
	void threading();
};


#endif // !CELLS_H
