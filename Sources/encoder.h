#pragma once
#include "typedefs.h"

typedef struct {
	void (*onTimer)(void * this);
	void (*onTick)(void * this);
	uint16_t (*get)(void * this);
	
	uint16_t count;
	uint16_t speed;
} Encoder;

void initEncoder(Encoder * encoder);

