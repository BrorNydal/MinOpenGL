#pragma once

#include "Object.h"

class XYZ : public Object
{
public:
	XYZ();
	~XYZ();

	virtual void draw() override;
};

