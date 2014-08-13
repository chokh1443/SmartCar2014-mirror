#include "event_handler.h"

EventHandler bind(void * that, void (*func) (void *)){
	EventHandler eventHandler;
	eventHandler.that = that;
	eventHandler.onEvent = func;
	return eventHandler;
}

void trigger(EventHandler eventHandler){
	eventHandler.onEvent(eventHandler.that);
}
