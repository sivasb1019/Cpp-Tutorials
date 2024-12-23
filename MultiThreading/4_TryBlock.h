#pragma once
#include <mutex>

void waitingSeconds(int seconds);
void incrementXorY(int& value, std::mutex& mtx, char* desc);
void consumeXY();
