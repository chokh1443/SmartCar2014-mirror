#pragma once

#include "typedefs.h"
#include "event_handler.h"

typedef struct {
	void (*emit)(void * this);
	void (*addHandler)(void * this, EventHandler handler);
	
	EventHandler handler[5];
	uint8_t index;
} EventEmitter;

void initEventEmitter(EventEmitter * this);
