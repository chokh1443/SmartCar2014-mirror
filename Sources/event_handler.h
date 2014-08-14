#pragma once

/*
 * usage :
 * handler = bind(this, this->onTick);
 * trigger(handler);
 */

typedef void(*ThisCall)(void *);

typedef struct {
	void * that;
	void (*onEvent)(void * that);
} EventHandler;

EventHandler bind(void * that, void (*func) (void *));
void trigger(EventHandler eventHandler);
