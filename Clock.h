#pragma once

#include <string>
#include "Object.h"
#include "Font.h"
#include "Glyph.h"

class Clock : public Object {
public:
	Clock();
	~Clock(){}
	virtual void draw() const;
	virtual void update(double dt);
	virtual void setX(double newX);
	virtual void setY(double newY);

private:
	Font font;
	double xPos;
	double yPos;
	double elapsed_seconds;
};
