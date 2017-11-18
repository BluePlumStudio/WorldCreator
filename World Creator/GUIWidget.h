#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>

#include "GUIState.h"
#include "DrawList.h"
#include "Texture2D.h"

class GUIWidget
{
public:
	enum GUIWidgetState
	{
		None,
		Normal,
		Active,
		Hot,
		Click,
		Change
	};

	enum GUIOrientation
	{
		Horizontal,
		Vertical
	};
	GUIWidget();

	static inline GLboolean isInside(GUIState & state, glm::vec2 & position, glm::vec2 & size)
	{
		if ((state.cursorPosition.x < position.x) ||
			(state.cursorPosition.y < position.y) ||
			(state.cursorPosition.x >= position.x + size.x) ||
			(state.cursorPosition.y >= position.y + size.y))
		{
			return false;
		}
		return true;
	}

	GLuint getID()const;
	GLuint getWidgetCount()const;
	virtual ~GUIWidget();
protected:
	static GLuint widgetCount;
	GLuint ID;
public:
	GUIWidgetState state;

};
