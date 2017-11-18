#pragma once

#include "GUIWidget.h"

class GUILabel :public GUIWidget
{
public:
	GUILabel();

	static inline GLvoid setTexCoordsNormal(glm::vec2 & texCoords, glm::vec2 & size)
	{
		texCoordsNormal = texCoords;
		texSizeNormal = size;
	}

	static inline GLvoid getDrawData(const glm::vec2 & position, const glm::vec2 & size, glm::vec4 & colorNormal, DrawList & drawList)
	{
		DrawList::getRectangleDrawData(position, size, texCoordsNormal, texSizeNormal, colorNormal, drawList);

	}


	~GUILabel();
private:
	static glm::vec2 texCoordsNormal;
	static glm::vec2 texSizeNormal;

};

