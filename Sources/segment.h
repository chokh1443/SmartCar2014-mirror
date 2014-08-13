#pragma once
#include "board.h"

typedef struct {
	void (*print)(void * this, uint16_t number);
	void (*onTick)(void * this);
	uint8_t charArray[4];
	
	uint8_t NUM_PINS[4];
	
	uint8_t * ENABLE_PINS;
	uint8_t * NUMBER_PINS;
	
	GPIO * gpio;
} Segment;

initSegment(Segment * segment, Board * board, uint8_t id);
