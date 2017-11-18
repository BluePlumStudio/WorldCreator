#pragma once

#include "Font.h"

class TextRenderer:public Font
{
public:
	class String
	{
	public:
		String();
		String(std::string & str);
		String(const GLchar * str);
		String(const String & right);
		GLvoid resetDrawLists(GLuint positionLocation, GLuint texCoordsLocation, GLuint colorLocation);
		String & operator=(const String & right);
		String & operator=(std::string & right);
		inline GLvoid draw(GLint textTextureLoc)
		{
			GLuint size = drawLists.size();
			for (GLuint i = 0; i < size; ++i)
			{
				textures[i].bind(textTextureLoc);
				drawLists[i].draw();
			}
		}
		~String();

	public:
		std::string str;
		std::vector<Font::CharacterTexture2D> textures;
		std::vector<DrawList> drawLists;
	private:
	};

	TextRenderer();
	GLint init(const GLchar * fontPath, GLuint positionLocation, GLuint texCoordsLocation, GLuint colorLocation, FT_UInt width = 0, FT_UInt height = 16);
	GLboolean getStringData(glm::vec4 & color, glm::vec3 & coords, GLfloat scale, String & str, Font::Mode mode = Font::Mode::Normal);
	inline GLvoid drawText(GLint textTextureLoc, std::string str, glm::vec4 color, glm::vec3 coords, GLfloat scale, Font::Mode mode = Font::Mode::Normal)
	{
		wchar_t* wstr = nullptr;
		Font::multiByteToWideChar(str.c_str(), &wstr, str.length());
		GLfloat xSrc = coords.x;
		FT_ULong textLength = lstrlenW(wstr);
		for (FT_ULong ch = 0; ch < textLength; ++ch)
		{
			if (wstr[ch] == '\n')
			{
				coords.y -= Font::size.y;
				coords.x = xSrc;
				continue;
			}
			Font::getCharacterData(wstr[ch], color, coords, scale, characterDrawList, characterTexture, mode);

			characterDrawList.updateSubData(0, 54);
			characterTexture.bind(textTextureLoc);
			characterDrawList.draw();
			// 更新位置到下一个字形的原点，单位是1/64像素
			coords.x += (Font::getCharacterAdvance(wstr[ch]) >> 6) * scale; // 位偏移6个单位来获取单位为像素的值 (2^6 = 64)
		}
		free(wstr);
		//delete[] wstr;
	}
	~TextRenderer();
public:
	//Font font;
private:
	GLuint positionLocation;
	GLuint texCoordsLocation;
	GLuint colorLocation;
	DrawList characterDrawList;
	Font::CharacterTexture2D characterTexture;
};

