#pragma once
#include "typedefs.h"

typedef struct {
	int16_t count;
	int16_t speed;
	int16_t target;
} Encoder;

void Encoder_init(Encoder * encoder);
void Encoder_onTimer(Encoder * this);
void Encoder_onTick(Encoder * this);
int16_t Encoder_get(Encoder * this);
void Encoer_setTarget(Encoder * this, uint16_t val);

