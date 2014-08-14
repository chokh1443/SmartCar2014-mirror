#include "event_emiter.h"

void EventEmitter_emit(EventEmitter * this);
void EventEmitter_addHandler(EventEmitter * this, EventHandler handler);

void initEventEmitter(EventEmitter * this){
	this->emit = (void(*)(void *))EventEmitter_emit;
	this->addHandler = (void(*)(void *, EventHandler))EventEmitter_addHandler;
	this->index = 0;
}

void EventEmitter_emit(EventEmitter * this){
	uint8_t i;
	for(i =0; i < this->index; i++){
		trigger(this->handler[i]);
	}
}
void EventEmitter_addHandler(EventEmitter * this, EventHandler handler){
	this->handler[this->index++] = handler;
}
