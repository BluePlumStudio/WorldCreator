#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

struct GUIState
{
	GUIState()
	{
		cursorPosition = { 0.0f, 0.0f };
		isMouseLButtonPress = false;
		isMouseRButtonPress = false;
		hotObjectID = 0;
		activeObjectID = 0;
	}
public:
	glm::vec2	cursorPosition;
	GLboolean	isMouseLButtonPress;
	GLboolean	isMouseRButtonPress;
	GLuint		hotObjectID;
	GLuint		activeObjectID;
};

