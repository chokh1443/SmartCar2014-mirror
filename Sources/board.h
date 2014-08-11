#pragma once

struct LED {
	void (*on)(int number);
	void (*off)(int number);
};

struct GPIO {
	void (*on)(int number);
	void (*off)(int number);
};

struct Board {
	struct LED led;
	struct GPIO gpio;
};

void initBoard(struct Board * board);
