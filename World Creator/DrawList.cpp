#include "DrawList.h"


using namespace std;

DrawList::DrawList()
{
	VAO = 0;
	dataStride = 5;
}

DrawList::DrawList(const DrawList & right) :VertexBuffer(right)
{
	this->dataStride = dataStride;
	//data.clear();

	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindVertexArray(0);

	if (!glIsVertexArray(VAO))
	{
#ifdef _DEBUG
		cout << "RederList£ºVertexArrayÉêÇëÊ§°Ü£¡" << endl;
#endif
		throw runtime_error("RederList£ºVertexArrayÉêÇëÊ§°Ü£¡");
	}

}

GLint DrawList::init(GLuint dataStride)
{
	VertexBuffer::init();

	this->dataStride = dataStride;

	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindVertexArray(0);

	if (!glIsVertexArray(VAO))
	{
#ifdef _DEBUG
		cout << "RederList£ºVertexArrayÉêÇëÊ§°Ü£¡" << endl;
#endif
		return 1;
	}
	return 0;
}

DrawList & DrawList::operator = (const DrawList & right)
{
	//glBindVertexArray(VAO);
	VertexBuffer::operator=(right);
	//glBindVertexArray(0);
	return *this;
}

GLvoid DrawList::getRectangleDrawData(const glm::vec2 & position, const glm::vec2 & size, const glm::vec2 texCoords, const glm::vec2 texSize, const glm::vec4 & color, DrawList & drawList)
{
	GLuint drawListSize = drawList.data.size();
	drawList.data.resize(drawListSize + 48);

	//×óÏÂ
	drawList.data[drawListSize + 0] = position.x;
	drawList.data[drawListSize + 1] = position.y;
	drawList.data[drawListSize + 2] = texCoords.x;
	drawList.data[drawListSize + 3] = texCoords.y;
	drawList.data[drawListSize + 4] = color.r;
	drawList.data[drawListSize + 5] = color.g;
	drawList.data[drawListSize + 6] = color.b;
	drawList.data[drawListSize + 7] = color.a;
	//ÓÒÏÂ
	drawList.data[drawListSize + 8] = position.x + size.x;
	drawList.data[drawListSize + 9] = position.y;
	drawList.data[drawListSize + 10] = texCoords.x + texSize.x;
	drawList.data[drawListSize + 11] = texCoords.y;
	drawList.data[drawListSize + 12] = color.r;
	drawList.data[drawListSize + 13] = color.g;
	drawList.data[drawListSize + 14] = color.b;
	drawList.data[drawListSize + 15] = color.a;
	//ÓÒÉÏ
	drawList.data[drawListSize + 16] = position.x + size.x;
	drawList.data[drawListSize + 17] = position.y + size.y;
	drawList.data[drawListSize + 18] = texCoords.x + texSize.x;
	drawList.data[drawListSize + 19] = texCoords.y + texSize.y;
	drawList.data[drawListSize + 20] = color.r;
	drawList.data[drawListSize + 21] = color.g;
	drawList.data[drawListSize + 22] = color.b;
	drawList.data[drawListSize + 23] = color.a;
	//ÓÒÉÏ
	drawList.data[drawListSize + 24] = position.x + size.x;
	drawList.data[drawListSize + 25] = position.y + size.y;
	drawList.data[drawListSize + 26] = texCoords.x + texSize.x;
	drawList.data[drawListSize + 27] = texCoords.y + texSize.y;
	drawList.data[drawListSize + 28] = color.r;
	drawList.data[drawListSize + 29] = color.g;
	drawList.data[drawListSize + 30] = color.b;
	drawList.data[drawListSize + 31] = color.a;
	//×óÉÏ
	drawList.data[drawListSize + 32] = position.x;
	drawList.data[drawListSize + 33] = position.y + size.y;
	drawList.data[drawListSize + 34] = texCoords.x;
	drawList.data[drawListSize + 35] = texCoords.y + texSize.y;
	drawList.data[drawListSize + 36] = color.r;
	drawList.data[drawListSize + 37] = color.g;
	drawList.data[drawListSize + 38] = color.b;
	drawList.data[drawListSize + 39] = color.a;
	//×óÏÂ
	drawList.data[drawListSize + 40] = position.x;
	drawList.data[drawListSize + 41] = position.y;
	drawList.data[drawListSize + 42] = texCoords.x;
	drawList.data[drawListSize + 43] = texCoords.y;
	drawList.data[drawListSize + 44] = color.r;
	drawList.data[drawListSize + 45] = color.g;
	drawList.data[drawListSize + 46] = color.b;
	drawList.data[drawListSize + 47] = color.a;
}

DrawList::~DrawList()
{
	glDeleteVertexArrays(1, &VAO);
}
