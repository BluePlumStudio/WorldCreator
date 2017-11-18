#include "TextRenderer.h"

using namespace std;



TextRenderer::String::String()
{
	for (GLuint i = 0; i < drawLists.size(); ++i)
	{
		drawLists[i].data.resize(54);
		drawLists[i].setDrawMode(GL_TRIANGLES);
		drawLists[i].setDataStride(9);
	}
}

TextRenderer::String::String(string & str)
{
	this->str = str;
	for (GLuint i = 0; i < drawLists.size(); ++i)
	{
		drawLists[i].data.resize(54);
		drawLists[i].setDrawMode(GL_TRIANGLES);
		drawLists[i].setDataStride(9);
	}
}

TextRenderer::String::String(const GLchar * str)
{
	this->str = str;
	for (GLuint i = 0; i < drawLists.size(); ++i)
	{
		drawLists[i].data.resize(54);
		drawLists[i].setDrawMode(GL_TRIANGLES);
		drawLists[i].setDataStride(9);
	}
}

TextRenderer::String::String(const String & right)
{
	str = right.str;
	textures = right.textures;
	drawLists = right.drawLists;

	for (GLuint i = 0; i < drawLists.size(); ++i)
	{
		drawLists[i].data.resize(54);
		drawLists[i].setDrawMode(GL_TRIANGLES);
		drawLists[i].setDataStride(9);
	}

}

TextRenderer::String & TextRenderer::String::operator=(const String & right)
{
	str = right.str;
	textures = right.textures;
	drawLists = right.drawLists;

	return *this;
}

TextRenderer::String & TextRenderer::String::operator=(string & right)
{
	str = right;

	return *this;
}

TextRenderer::String::~String()
{
}

GLvoid TextRenderer::String::resetDrawLists(GLuint positionLocation, GLuint texCoordsLocation, GLuint colorLocation)
{
	for (GLuint i = 0; i < drawLists.size(); ++i)
	{
		drawLists[i].data.resize(54);
		drawLists[i].setVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 9, (GLvoid*)0);
		drawLists[i].setVertexAttribPointer(texCoordsLocation, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 9, (GLvoid*)(sizeof(GLfloat)* 3));
		drawLists[i].setVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 9, (GLvoid*)(sizeof(GLfloat)* 5));
		drawLists[i].setDrawMode(GL_TRIANGLES);
		drawLists[i].setDataStride(9);
	}
}

/**/

TextRenderer::TextRenderer()
{

}

GLint TextRenderer::init(const GLchar * fontPath, GLuint positionLocation, GLuint texCoordsLocation, GLuint colorLocation, FT_UInt width, FT_UInt height)
{
	if (characterDrawList.init())
	{
		return 1;
	}
	this->positionLocation = positionLocation;
	this->texCoordsLocation = texCoordsLocation;
	this->colorLocation = colorLocation;
	characterDrawList.data.resize(54);
	characterDrawList.setVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 9, (GLvoid*)0);
	characterDrawList.setVertexAttribPointer(texCoordsLocation, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 9, (GLvoid*)(sizeof(GLfloat)* 3));
	characterDrawList.setVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 9, (GLvoid*)(sizeof(GLfloat)* 5));
	characterDrawList.setDrawMode(GL_TRIANGLES);
	characterDrawList.setDataStride(9);
	characterDrawList.updateData(GL_DYNAMIC_DRAW);
	return Font::init(fontPath, width, height);
}

GLboolean TextRenderer::getStringData(glm::vec4 & color, glm::vec3 & coords, GLfloat scale, String & str, Font::Mode mode)
{
	wchar_t* wstr = nullptr;
	GLuint strLength = 0;
	multimap<wchar_t, Font::Character>::iterator it;
	GLfloat xSrc = coords.x;

	Font::multiByteToWideChar(str.str.c_str(), &wstr, str.str.length());

	strLength = lstrlenW(wstr);
	str.drawLists.resize(strLength);
	str.textures.resize(strLength);

	for (GLuint i = 0; i < strLength; ++i)
	{
		if (wstr[i] == '\n')
		{
			coords.y += Font::size.y;
			coords.x = xSrc;
			continue;
		}
		it = Font::characters.find(wstr[i]);
		Font::Character ch;
		if (it == Font::characters.end())
		{
			if (Font::addCharacter(wstr[i]))
			{
				return false;
			}
			it = Font::characters.find(wstr[i]);
		}
		if (mode == Font::Mode::MSDF)
		{
			it++;
		}
		ch = (*it).second;


		GLfloat xPos = coords.x + ch.bearing.x * scale;
		GLfloat yPos = coords.y - (ch.size.y - ch.bearing.y) * scale;
		GLfloat zPos = coords.z;

		GLfloat w = ch.size.x * scale;
		GLfloat h = ch.size.y * scale;

		str.drawLists[i].init();
		str.drawLists[i].data.resize(54);

		str.drawLists[i].data[0] = xPos;
		str.drawLists[i].data[1] = yPos + h;
		str.drawLists[i].data[2] = zPos;
		str.drawLists[i].data[3] = 0.0f;
		str.drawLists[i].data[4] = 0.0f;
		str.drawLists[i].data[5] = color.r;
		str.drawLists[i].data[6] = color.g;
		str.drawLists[i].data[7] = color.b;
		str.drawLists[i].data[8] = color.a;

		str.drawLists[i].data[9] = xPos;
		str.drawLists[i].data[10] = yPos;
		str.drawLists[i].data[11] = zPos;
		str.drawLists[i].data[12] = 0.0f;
		str.drawLists[i].data[13] = 1.0f;
		str.drawLists[i].data[14] = color.r;
		str.drawLists[i].data[15] = color.g;
		str.drawLists[i].data[16] = color.b;
		str.drawLists[i].data[17] = color.a;

		str.drawLists[i].data[18] = xPos + w;
		str.drawLists[i].data[19] = yPos;
		str.drawLists[i].data[20] = zPos;
		str.drawLists[i].data[21] = 1.0f;
		str.drawLists[i].data[22] = 1.0f;
		str.drawLists[i].data[23] = color.r;
		str.drawLists[i].data[24] = color.g;
		str.drawLists[i].data[25] = color.b;
		str.drawLists[i].data[26] = color.a;

		str.drawLists[i].data[27] = xPos;
		str.drawLists[i].data[28] = yPos + h;
		str.drawLists[i].data[29] = zPos;
		str.drawLists[i].data[30] = 0.0f;
		str.drawLists[i].data[31] = 0.0f;
		str.drawLists[i].data[32] = color.r;
		str.drawLists[i].data[33] = color.g;
		str.drawLists[i].data[34] = color.b;
		str.drawLists[i].data[35] = color.a;

		str.drawLists[i].data[36] = xPos + w;
		str.drawLists[i].data[37] = yPos;
		str.drawLists[i].data[38] = zPos;
		str.drawLists[i].data[39] = 1.0f;
		str.drawLists[i].data[40] = 1.0f;
		str.drawLists[i].data[41] = color.r;
		str.drawLists[i].data[42] = color.g;
		str.drawLists[i].data[43] = color.b;
		str.drawLists[i].data[44] = color.a;

		str.drawLists[i].data[45] = xPos + w;
		str.drawLists[i].data[46] = yPos + h;
		str.drawLists[i].data[47] = zPos;
		str.drawLists[i].data[48] = 1.0f;
		str.drawLists[i].data[49] = 0.0f;
		str.drawLists[i].data[50] = color.r;
		str.drawLists[i].data[51] = color.g;
		str.drawLists[i].data[52] = color.b;
		str.drawLists[i].data[53] = color.a;

		str.textures[i].init(ch.characterTexture.getID(), ch.characterTexture.getLevel());

		coords.x += (Font::getCharacterAdvance(wstr[i]) >> 6) * scale;

		str.drawLists[i].updateData(GL_DYNAMIC_DRAW);

	}
	free(wstr);
	str.resetDrawLists(positionLocation, texCoordsLocation, colorLocation);
	return true;
}

TextRenderer::~TextRenderer()
{
}

/**/
