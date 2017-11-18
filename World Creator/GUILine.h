#pragma once

#include "GUIWidget.h"

class GUILine :public GUIWidget
{
public:
	GUILine();

	static inline GLvoid setTexCoordsNormal(glm::vec2 & texCoords, glm::vec2 & size)
	{
		texCoordsNormal = texCoords;
		texSizeNormal = size;
	}

	static inline GLvoid getDrawData(const glm::vec2 & position, const glm::vec2 & size, glm::vec4 & colorNormal, DrawList & drawList)
	{
		GLuint drawListSize = drawList.data.size();
		drawList.data.resize(drawListSize + 48);
		//左下
		drawList.data[drawListSize + 0] = position.x;
		drawList.data[drawListSize + 1] = position.y;
		//右下
		drawList.data[drawListSize + 8] = position.x + size.x;
		drawList.data[drawListSize + 9] = position.y;
		//右上
		drawList.data[drawListSize + 16] = position.x + size.x;
		drawList.data[drawListSize + 17] = position.y + size.y;
		//右上
		drawList.data[drawListSize + 24] = position.x + size.x;
		drawList.data[drawListSize + 25] = position.y + size.y;
		//左上
		drawList.data[drawListSize + 32] = position.x;
		drawList.data[drawListSize + 33] = position.y + size.y;
		//左下
		drawList.data[drawListSize + 40] = position.x;
		drawList.data[drawListSize + 41] = position.y;

		//左下
		drawList.data[drawListSize + 2] = texCoordsNormal.x;
		drawList.data[drawListSize + 3] = texCoordsNormal.y;
		drawList.data[drawListSize + 4] = colorNormal.r;
		drawList.data[drawListSize + 5] = colorNormal.g;
		drawList.data[drawListSize + 6] = colorNormal.b;
		drawList.data[drawListSize + 7] = colorNormal.a;
		//右下
		drawList.data[drawListSize + 10] = texCoordsNormal.x + texSizeNormal.x;
		drawList.data[drawListSize + 11] = texCoordsNormal.y;
		drawList.data[drawListSize + 12] = colorNormal.r;
		drawList.data[drawListSize + 13] = colorNormal.g;
		drawList.data[drawListSize + 14] = colorNormal.b;
		drawList.data[drawListSize + 15] = colorNormal.a;
		//右上
		drawList.data[drawListSize + 18] = texCoordsNormal.x + texSizeNormal.x;
		drawList.data[drawListSize + 19] = texCoordsNormal.y + texSizeNormal.y;
		drawList.data[drawListSize + 20] = colorNormal.r;
		drawList.data[drawListSize + 21] = colorNormal.g;
		drawList.data[drawListSize + 22] = colorNormal.b;
		drawList.data[drawListSize + 23] = colorNormal.a;
		//右上
		drawList.data[drawListSize + 26] = texCoordsNormal.x + texSizeNormal.x;
		drawList.data[drawListSize + 27] = texCoordsNormal.y + texSizeNormal.y;
		drawList.data[drawListSize + 28] = colorNormal.r;
		drawList.data[drawListSize + 29] = colorNormal.g;
		drawList.data[drawListSize + 30] = colorNormal.b;
		drawList.data[drawListSize + 31] = colorNormal.a;
		//左上
		drawList.data[drawListSize + 34] = texCoordsNormal.x;
		drawList.data[drawListSize + 35] = texCoordsNormal.y + texSizeNormal.y;
		drawList.data[drawListSize + 36] = colorNormal.r;
		drawList.data[drawListSize + 37] = colorNormal.g;
		drawList.data[drawListSize + 38] = colorNormal.b;
		drawList.data[drawListSize + 39] = colorNormal.a;
		//左下
		drawList.data[drawListSize + 42] = texCoordsNormal.x;
		drawList.data[drawListSize + 43] = texCoordsNormal.y;
		drawList.data[drawListSize + 44] = colorNormal.r;
		drawList.data[drawListSize + 45] = colorNormal.g;
		drawList.data[drawListSize + 46] = colorNormal.b;
		drawList.data[drawListSize + 47] = colorNormal.a;


	}


	~GUILine();
private:
	static glm::vec2 texCoordsNormal;
	static glm::vec2 texSizeNormal;
};

