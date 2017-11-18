#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <iostream>

class Camera
{
public:
	Camera();
	GLvoid init(glm::vec3 & position, glm::vec3 & target, glm::vec3 & up, GLfloat mouseSpeed = 0.2f, GLfloat moveSpeed = 5.0f);

	inline GLvoid moveForward()
	{
		glm::vec3 top = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 forward = glm::cross(up, target);
		forward = glm::cross(forward, top);
		forward = glm::normalize(forward);
		forward.y = 0.0f;
		forward *= moveSpeedS;
		position += forward;

	}

	inline GLvoid moveBackward()
	{
		glm::vec3 top = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 forward = glm::cross(up, target);
		forward = glm::cross(forward, top);
		forward = glm::normalize(forward);
		forward.y = 0.0f;
		forward *= moveSpeedS;
		position -= forward;
	}

	inline GLvoid moveLeft()
	{
		glm::vec3 Left = glm::cross(up, target);
		Left = glm::normalize(Left);
		Left.y = 0.0f;
		Left *= moveSpeedS;
		position += Left;
	}

	inline GLvoid moveRight()
	{
		glm::vec3 Left = glm::cross(up, target);
		Left = glm::normalize(Left);
		Left.y = 0.0f;
		Left *= moveSpeedS;
		position -= Left;
	}

	inline GLvoid moveUp()
	{
		glm::vec3 top = glm::vec3(0.0f, 1.0f, 0.0f);
		position += top*moveSpeedS;
	}

	inline GLvoid moveDown()
	{
		glm::vec3 top = glm::vec3(0.0f, 1.0f, 0.0f);
		position -= top*moveSpeedS;
	}
	/*============================================================*/
	inline GLvoid setPosition(glm::vec3 position)
	{
		this->position = position;
	}

	inline GLvoid setTarget(glm::vec3 target)
	{
		this->target = target;
	}

	inline GLvoid setUp(glm::vec3 up)
	{
		this->up = up;
	}

	inline GLvoid setAngleH(GLfloat angleH)
	{
		this->angleH = angleH;
	}

	inline GLvoid setAngleV(GLfloat angleV)
	{
		this->angleV = angleV;
	}

	inline GLvoid setMouseSpeed(GLfloat mouseSpeed)
	{
		this->mouseSpeed = mouseSpeed;
	}

	inline GLvoid setMoveSpeedS(GLfloat moveSpeedS)
	{
		this->moveSpeedS = moveSpeedS;
	}

	inline GLvoid setMoveSpeed(GLfloat moveSpeed)
	{
		this->moveSpeed = moveSpeed;
	}

	inline GLvoid setMousePosX(GLfloat GLdouble)
	{
		this->mousePosX = mousePosX;
	}
	inline GLvoid setMousePosY(GLfloat GLdouble)
	{
		this->mousePosY = mousePosY;
	}

	/*============================================================*/

	inline glm::vec3 getPosition()const
	{
		return this->position;
	}

	inline glm::vec3 getTarget()const
	{
		return this->target;
	}

	inline glm::vec3 getUp()const
	{
		return this->up;
	}

	inline GLfloat getAngleH()const
	{
		return this->angleH;
	}

	inline GLfloat getAngleV()const
	{
		return this->angleV;
	}

	inline GLfloat getMouseSpeed()const
	{
		return this->mouseSpeed;
	}

	inline GLfloat getMoveSpeed()const
	{
		return this->moveSpeed;
	}

	inline GLfloat getMoveSpeedS()const
	{
		return this->moveSpeedS;
	}

	inline GLdouble getMousePosX()const
	{
		return this->mousePosX;
	}

	inline GLdouble getMousePosY()const
	{
		return this->mousePosY;
	}
	inline GLdouble getLastMousePosX()const
	{
		return this->mousePosX;
	}

	inline GLdouble getLastMousePosY()const
	{
		return this->mousePosY;
	}
	/*============================================================*/
	/*
	static GLvoid uniformMatrix4fv(GLint location,GLsizei count,GLboolean transpose,GLfloat* value)
	{
		glUniformMatrix4fv(location, count, transpose, value);
	}
	*/

	GLvoid viewRotate(GLdouble x, GLdouble y);
	GLvoid update();
	~Camera();
private:
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 up;
	GLfloat angleH;
	GLfloat angleV;
	GLfloat mouseSpeed;
	GLfloat moveSpeedS;
	GLfloat moveSpeed;
	GLdouble mousePosX;
	GLdouble mousePosY;

	GLfloat lastMousePosX;
	GLfloat lastMousePosY;
	GLboolean isInited;
};

