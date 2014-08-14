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
} GPIO;

typedef struct {
	LED led;
	GPIO gpio;

	void (*addTimerHandler)(EventHandler handler);
} Board;

void ON_TIMER();

extern Board board;
