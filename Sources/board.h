#pragma once
#include "typedefs.h"
#include "zp_pin.h"

typedef struct {
	void (*on)(uint16_t ledId);
	void (*off)(uint16_t ledId);
} LED;

typedef struct {
	void (*on)(uint16_t ch);
	void (*off)(uint16_t ch);
	uint8_t (*get)(uint16_t ch);
	
	struct {
		uint8_t ** segmentNumber;
		uint8_t ** segmentEnable;
	} ch;
} GPIO;

typedef struct {
	LED led;
	GPIO gpio;
} Board;

void initBoard(Board * board);

