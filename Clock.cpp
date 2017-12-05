#include "Clock.h"
#include "Frame.h"
#include "Font.h"
#include "Object.h"
#include <string>
#include <sstream>
#include <cstring>

extern Frame frame;

Clock::Clock() {
	xPos = 0;
	yPos = 0;
	elapsed_seconds = 0;
}

void Clock::update(double dt) {
	elapsed_seconds += dt;
}

void Clock::draw() const {
	std::stringstream ss;
	ss << (int)elapsed_seconds;
	font.draw(ss.str(), xPos, yPos);
}

void Clock::setX(double newX) {
	xPos = newX;
}

void Clock::setY(double newY) {
	yPos = newY;
}
