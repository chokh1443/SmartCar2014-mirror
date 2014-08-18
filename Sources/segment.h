#pragma once
#include "board.h"

typedef struct {
	void (*print)(void * this, uint16_t number);
	void (*onTick)(void * this);
	uint8_t charArray[4];
	
	uint8_t NUM_PINS[4];
	
	uint8_t id;
	uint8_t index;
	uint8_t holdCount;
} Segment;

void Segment_init(Segment * this, uint8_t id);
void Segment_print(Segment * this, uint16_t number);
void Segment_onTick(Segment * this);
