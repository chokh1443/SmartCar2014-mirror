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
	void (*set)(uint16_t ch, uint16_t value);
} PWM;

typedef struct {
	LED led;
	GPIO gpio;
	PWM pwm;

	void (*addTimerHandler)(EventHandler handler);
	void (*addCameraHandler)(EventHandler handler);
} Board;

void ON_TIMER();
void ON_CAMERA();

extern Board board;
