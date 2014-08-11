#pragma once

const static unsigned char newLine[2] = {'\r', '\n'};

void sendBlueChar(const char * arr, unsigned long length);
void sendBlueInt(int integer);
void sendBlueNewLine();
void sendBlueMsg(const char * arr, unsigned long length); //XXX
void sendBlueArrayDump(const int * arr, int length);
void sendBluePID(int count, int target, int pwm);
int recvBlueInt(void);
