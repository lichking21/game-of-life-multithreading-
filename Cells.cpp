#include "Cells.h"

void Cells::start_gen() {

	srand(time(NULL));

	rows = 480 / cell_size;
	cols = 640 / cell_size;

	field.resize(rows, std::vector<bool>(cols, false));
	next_field.resize(rows, std::vector<bool>(cols, false));

	for (int x = 0; x < cols; ++x) {

		for (int y = 0; y < rows; ++y) {

			int rnd = rand() % (dencity + 1);
			field[y][x] = (rnd == 0);
		}
	}
}

std::mutex mtx;
int Cells::count_neightbor(int y, int x) {

	mtx.lock();
	int count = 0;
	mtx.unlock();

	for (int i = -1; i < 2; i++) {

		for (int j = -1; j < 2; j++) {

			int col = (x + i + cols) % cols;
			int row = (y + j + rows) % rows;

			bool self_check = (col == x && row == y);
			bool has_life = field[row][col];

			if (has_life && !self_check) {

				mtx.lock();
				count++;
				mtx.unlock();
			}
		}
	}

	return count;
}

void Cells::next_gen() {

	for (int x = 0; x < cols; ++x) {

		for (int y = 0; y < rows; ++y) {

			int count = count_neightbor(y, x); // count of neightbors for continue generation
			bool has_life = field[y][x];

			if (!has_life && count == 3)
				next_field[y][x] = true;
			else if (has_life && (count < 2 || count > 3))
				next_field[y][x] = false;
			else
				next_field[y][x] = field[y][x];
		}
	}
	field = next_field;
}

void Cells::draw(sf::RenderWindow& window) {

	sf::RectangleShape cell(sf::Vector2f(cell_size, cell_size));
	cell.setFillColor(sf::Color::Blue);

	for (int x = 0; x < cols; x++) {

		for (int y = 0; y < rows; y++) {

			if (field[y][x]) {

				cell.setPosition(x * cell_size, y * cell_size);
				window.draw(cell);
			}
		}
	}
}

void Cells::threading() {

	int t_count = 2;
	int range = rows / t_count; // rows per thread

	std::thread t1([this, range]() {

		for (int y = 0; y < range; ++y) {

			for (int x = 0; x < cols; ++x)
				count_neightbor(y, x);
		}
	});
	std::thread t2([this, range]() {

		for (int y = range; y < rows; ++y) {

			for (int x = 0; x < cols; ++x)
				count_neightbor(y, x);
		}
	});

	t1.join();
	t2.join();
}