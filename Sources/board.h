#pragma once
#include "typedefs.h"

typedef struct {
	void (*on)(uint16_t number);
	void (*off)(uint16_t number);
} LED;

typedef struct {
	void (*on)(uint16_t number);
	void (*off)(uint16_t number);
	uint8_t (*get)(uint16_t number);
} GPIO;

typedef struct {
	LED led;
	GPIO gpio;
} Board;

void initBoard(Board * board);
