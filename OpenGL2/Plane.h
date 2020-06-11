#pragma once

#include "Object.h"

class Plane : public Object
{
public:
	Plane();
	~Plane();

	virtual void draw() override;

};

