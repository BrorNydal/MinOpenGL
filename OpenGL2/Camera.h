#pragma once

#include <GLFW/glfw3.h>

#include "mat4x4.h"
#include "vec3.h"
#include "vec2.h"

class Camera
{
private://variables
	mat4x4 mViewMatrix;
	mat4x4 mProjectionMatrix;

	vec2 mMousePosition;

	vec3 mPosition	;	//position of camera
	vec3 mFocusPoint;	//where the camera is looking

	//vectors adjusted by position and focuspoint
	vec3 mForwardVector = vec3(1, 0, 0);
	vec3 mRightVector	= vec3(0, 0, 1);
	vec3 mUpVector		= vec3(0, 1, 0);

public://functions
	Camera();
	~Camera();

	void initialize();
	void tick(float delta);	

	//setters and getters
	void setPosition(vec3 newPos)	{ mPosition = newPos;	}
	vec3 getPosition() const		{ return mPosition;		}

	void setFocusPoint(vec3 newFoc)	{ mFocusPoint = newFoc; }
	vec3 getFocusPoint() const		{ return mFocusPoint;	}

	mat4x4 getViewMatrix()		 const { return mViewMatrix;		}
	mat4x4 getProjectionMatrix() const { return mProjectionMatrix;	}


private://functions
	void lookAt();

};

