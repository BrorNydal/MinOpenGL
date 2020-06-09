#include "Camera.h"
#include "Globals.h"


Camera::Camera()
	:	mPosition(GlobalWorldSettings::WorldUpVector), mFocusPoint(vec3::ZeroVector())
{

}


Camera::~Camera()
{
}

void Camera::initialize()
{
	mProjectionMatrix.frustum(-1, 1, -1, 1, 1, -1);
}

void Camera::tick(float delta)
{
	lookAt();
}

void Camera::lookAt()
{
	mViewMatrix.lookAt(mPosition, mFocusPoint, vec3(0,1,0));
}
