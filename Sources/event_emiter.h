#pragma once

#include "typedefs.h"
#include "event_handler.h"

typedef struct {
	EventHandler handler[5];
	uint8_t index;
} EventEmitter;

void EventEmitter_emit(EventEmitter * this);
void EventEmitter_addHandler(EventEmitter * this, EventHandler handler);
