#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "GUIWidget.h"


class GUIPushButton:public GUIWidget
{
public:
	GUIPushButton();
	static inline GLvoid setTexCoordsNormal(glm::vec2 & texCoords, glm::vec2 & size)
	{
		texCoordsNormal = texCoords;
		texSizeNormal = size;
	}
	static inline GLvoid setTexCoordsActive(glm::vec2 & texCoords, glm::vec2 & size)
	{
		texCoordsActive = texCoords;
		texSizeActive = size;
	}
	static inline GLvoid setTexCoordsHot(glm::vec2 & texCoords, glm::vec2 & size)
	{
		texCoordsHot = texCoords;
		texSizeHot = size;
	}
	static inline GLvoid setColorNormal(glm::vec4 & color)
	{
		colorNormal = color;
	}
	static inline GLvoid setColorActive(glm::vec4 & color)
	{
		colorActive = color;
	}
	static inline GLvoid setColorHot(glm::vec4 & color)
	{
		colorHot = color;
	}

	static inline GLvoid getDrawData(const glm::vec2 & position, const glm::vec2 & size, GUIWidgetState ObjectState, DrawList & drawList)
	{
		if (ObjectState == GUIWidgetState::Active)
		{
			DrawList::getRectangleDrawData(position, size, texCoordsActive, texSizeActive, colorActive, drawList);
		}
		else if (ObjectState == GUIWidgetState::Hot)
		{
			DrawList::getRectangleDrawData(position, size, texCoordsHot, texSizeHot, colorHot, drawList);
		}
		else
		{
			DrawList::getRectangleDrawData(position, size, texCoordsNormal, texSizeNormal, colorNormal, drawList);
		}
	}
	virtual ~GUIPushButton();
protected:
	static glm::vec2 texCoordsNormal;
	static glm::vec2 texSizeNormal;
	static glm::vec4 colorNormal;

	static glm::vec2 texCoordsActive;
	static glm::vec2 texSizeActive;
	static glm::vec4 colorActive;

	static glm::vec2 texCoordsHot;
	static glm::vec2 texSizeHot;
	static glm::vec4 colorHot;
};

