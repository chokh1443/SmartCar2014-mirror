#include "event_emiter.h"

void EventEmitter_emit(EventEmitter * this);
void EventEmitter_addHandler(EventEmitter * this, EventHandler handler);

void EventEmitter_emit(EventEmitter * this){
	uint8_t i;
	for(i =0 ; i < this->index; i++){
		trigger(this->handler[i]);
	}
}
void EventEmitter_addHandler(EventEmitter * this, EventHandler handler){
	this->handler[this->index] = handler;
	this->index++;
}
