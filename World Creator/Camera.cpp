#include "camera.h"


Camera::Camera()
{
}

GLvoid Camera::init(glm::vec3 & position, glm::vec3 & target, glm::vec3 & up, GLfloat mouseSpeed, GLfloat moveSpeed)
{
	this->position = position;
	this->target = glm::normalize(target);
	this->up = glm::normalize(up);

	glm::vec3 hTarget;
	hTarget.x = target.x;
	hTarget.y = 0.0f;
	hTarget.z = target.z;
	hTarget = glm::normalize(hTarget);
	if (hTarget.z >= 0.0f)
	{
		if (hTarget.x >= 0.0f)
		{
			angleH = 360.0f - glm::degrees(asin(hTarget.z));
		}
		else
		{
			angleH = 180.0f + glm::degrees(asin(hTarget.z));
		}
	}
	else
	{
		if (hTarget.x >= 0.0f)
		{
			angleH = glm::degrees(asin(-hTarget.z));
		}
		else
		{
			angleH = 90.0f + glm::degrees(asin(-hTarget.z));
		}
	}
	angleV = -glm::degrees(asin(target.y));

	this->mouseSpeed = mouseSpeed;
	this->moveSpeed = moveSpeed;
	isInited = false;
}


GLvoid Camera::viewRotate(GLdouble x, GLdouble y)
{
	if (!isInited)
	{
		lastMousePosX = (GLfloat)x;
		lastMousePosY = (GLfloat)y;
		isInited = true;
	}
	mousePosX = x;
	mousePosY = y;
	GLfloat deltaX = (GLfloat)mousePosX - lastMousePosX;
	GLfloat deltaY = (GLfloat)mousePosY - lastMousePosY;

	angleH -= deltaX*mouseSpeed;
	angleV += deltaY*mouseSpeed;
	if (angleV >= 90.0f)
	{
		angleV = 90.0f;
	}
	if (angleV <= -90.0f)
	{
		angleV = -90.0f;
	}
	lastMousePosX = (GLfloat)mousePosX;
	lastMousePosY = (GLfloat)mousePosY;
	update();
}

GLvoid Camera::update()
{
	glm::vec3 Vaxis(0.0f, 1.0f, 0.0f);
	glm::vec3 view(1.0f, 0.0f, 0.0f);
	view = glm::rotate(view, glm::radians(angleH), Vaxis);
	view = glm::normalize(view);
	glm::vec3 Haxis = glm::cross(Vaxis, view);
	Haxis = glm::normalize(Haxis);
	view = glm::rotate(view, glm::radians(angleV), Haxis);
	view = glm::normalize(view);
	target = view;
	target = glm::normalize(target);
	up = glm::cross(target, Haxis);
	up = glm::normalize(up);
}

Camera::~Camera()
{
}
