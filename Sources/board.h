#pragma once
#include "typedefs.h"
#include "zp_pin.h"
#include "event_handler.h"
#include "event_emiter.h"

typedef struct {
	void (*on)(uint16_t ledId);
	void (*off)(uint16_t ledId);
} LED;

typedef struct {
	void (*on)(uint16_t ch);
	void (*off)(uint16_t ch);
	uint8_t (*get)(uint16_t ch);
	void (*set)(uint16_t ch, uint8_t value);
	
	struct {
		uint8_t ** segmentNumber;
		uint8_t ** segmentEnable;
	} ch;
} GPIO;

typedef struct {
	void (*addHandler)(void * this, EventHandler * handler);
	void (*setInterval)(void * this);
	
	EventEmitter emitter;
} Interrupt;

typedef struct {
	LED led;
	GPIO gpio;
	
	Interrupt timerInterrupt;
	Interrupt encoderInterrupt;
	Interrupt cameraInterrupt;
} Board;

void initBoard(Board * board);
void initInterrupt(Interrupt * this);
