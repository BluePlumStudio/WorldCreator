#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>
#include <msdfgen/msdfgen.h>
#include <msdfgen/msdfgen-ext.h>

#include <iostream>
#include <map>

#include "PipeLine.h"
#include "DrawList.h"
#include "Texture2D.h"

#ifdef WIN32
#include <Windows.h>
#include <stdarg.h>
#include <direct.h>
#endif

#include FT_FREETYPE_H

class Font
{
public:
	enum Mode
	{
		Normal, MSDF
	};
	class CharacterTexture2D// :public Texture2D
	{
	public:
		friend Font;
		CharacterTexture2D();
		CharacterTexture2D(const CharacterTexture2D & right);
		GLuint init(const char * texturePath, GLenum level = GL_TEXTURE0);
		GLvoid init(GLuint textureID, GLenum level = GL_TEXTURE0);
		CharacterTexture2D & operator=(const CharacterTexture2D & right);
		inline GLuint getID()const
		{
			return ID;
		}
		inline GLuint getLevel()const
		{
			return level;
		}
		inline CharacterTexture2D & shallowCopy(const CharacterTexture2D & texture)
		{
			this->ID = texture.ID;
			return *this;
		}
		inline GLvoid texParameteri(GLenum pname, GLint param)
		{
			glBindTexture(GL_TEXTURE_2D, ID);
			glTexParameteri(GL_TEXTURE_2D, pname, param);
		}
		inline GLvoid bind(GLint location)const
		{
			glActiveTexture(level);
			glBindTexture(GL_TEXTURE_2D, ID);
			glUniform1f(location, GLfloat(level - GL_TEXTURE0));
		}
		inline GLvoid bind()const
		{
			glActiveTexture(level);
			glBindTexture(GL_TEXTURE_2D, ID);
		}
		inline static GLvoid resetTexture()
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		~CharacterTexture2D();

	private:
		
		GLuint ID;
		GLenum level;
	};

	struct Character
	{
		Character()
		{
			//textureID = { 0 };
			size = { 0, 0 };
			bearing = { 0, 0 };
			advance = { 0 };
		}
		//GLuint textureID;
		CharacterTexture2D characterTexture;
		glm::ivec2 size;
		glm::ivec2 bearing;
		GLuint advance;
	};


	/**/
	Font();
	Font & operator=(const Font & right);
	GLint init(const GLchar * fontPath, FT_UInt width = 0, FT_UInt height = 16);
	GLint addCharacter(wchar_t ch);
	GLboolean getCharacterData(wchar_t character, glm::vec4 & color, glm::vec3 & coords, GLfloat scale, DrawList & drawList/*size = 54*/, CharacterTexture2D & texture, Mode mode = Normal);
	GLboolean getStringData(std::string str, glm::vec4 & color, glm::vec3 & coords, GLfloat scale, std::vector<DrawList> & drawLists/*size = 54*/, std::vector<CharacterTexture2D> & textures, Mode mode = Normal);
	inline GLvoid getCharacterAdvance(wchar_t character, GLuint & advance)
	{
		std::multimap<wchar_t, Character>::iterator it = characters.find(character);
		if (it == characters.end())
		{
			if (addCharacter(character))
			{
				advance = 0;
				return;
			}
			it = characters.find(character);
		}
		advance = (*it).second.advance;
	}
	inline GLuint getCharacterAdvance(wchar_t character)
	{
		std::multimap<wchar_t, Character>::iterator it = characters.find(character);
		if (it == characters.end())
		{
			if (addCharacter(character))
			{
				return 0;
			}
			it = characters.find(character);
		}
		return (*it).second.advance;
	}
	inline GLvoid getCharacterSize(wchar_t character, glm::ivec2 & size)
	{
		std::multimap<wchar_t, Character>::iterator it = characters.find(character);
		if (it == characters.end())
		{
			if (addCharacter(character))
			{
				size = glm::ivec2(0, 0);
				return;
			}
			it = characters.find(character);
		}
		size = (*it).second.size;
	}
	inline glm::ivec2 getCharacterSize(wchar_t character)
	{
		std::multimap<wchar_t, Character>::iterator it = characters.find(character);
		if (it == characters.end())
		{
			if (addCharacter(character))
			{
				return glm::ivec2(0, 0);
			}
			it = characters.find(character);
		}
		return (*it).second.size;
	}
	inline GLvoid getCharacterBearing(wchar_t character, glm::ivec2 & bearing)
	{
		std::multimap<wchar_t, Character>::iterator it = characters.find(character);
		if (it == characters.end())
		{
			if (addCharacter(character))
			{
				bearing = glm::ivec2(0, 0);
				return;
			}
			it = characters.find(character);
		}
		bearing = (*it).second.bearing;
	}
	inline glm::ivec2 getCharacterBearing(wchar_t character)
	{
		std::multimap<wchar_t, Character>::iterator it = characters.find(character);
		if (it == characters.end())
		{
			if (addCharacter(character))
			{
				return glm::ivec2(0, 0);
			}
			it = characters.find(character);
		}
		return (*it).second.bearing;
	}
	inline GLvoid texParameteri(GLenum pname, GLint param)
	{
		for (std::multimap<wchar_t, Character>::iterator it = characters.begin(); it != characters.end(); ++it)
		{
			//glBindTexture(GL_TEXTURE_2D, (*it).second.textureID);
			(*it).second.characterTexture.bind();
			glTexParameteri(GL_TEXTURE_2D, pname, param);
			
		}
		//CharacterTexture2D::resetTexture();
	}
	inline GLvoid texParameterivec(std::vector<std::pair<GLenum, GLint>>parameters)
	{
		for (std::multimap<wchar_t, Character>::iterator it = characters.begin(); it != characters.end(); ++it)
		{
			//glBindTexture(GL_TEXTURE_2D, (*it).second.textureID);
			(*it).second.characterTexture.bind();
			for (std::vector<std::pair<GLenum, GLint>>::iterator it = parameters.begin(); it != parameters.end(); ++it)
			{
				glTexParameteri(GL_TEXTURE_2D, (*it).first, (*it).second);
			}
		}
		//CharacterTexture2D::resetTexture();
	}

	inline GLint getStringWidth(std::string & str)
	{
		GLint width = 0;
		GLint maxWidth = 0;
		wchar_t* wstr = nullptr;
		std::multimap<wchar_t, Character>::iterator it;

		Font::multiByteToWideChar(str.c_str(), &wstr, str.length());
		FT_ULong textLength = lstrlenW(wstr);
		for (FT_ULong ch = 0; ch < textLength; ++ch)
		{
			it = characters.find(wstr[ch]);
			if (it == characters.end())
			{
				if (addCharacter(wstr[ch]))
				{
					return -1;
				}
				it = characters.find(wstr[ch]);
			}

			if (wstr[ch] == '\n')
			{
				if (width>maxWidth)
				{
					maxWidth = width;
				}
				width = 0;
				continue;
			}

			width += ((*it).second.advance >> 6);

		}

		if (width>maxWidth)
		{
			maxWidth = width;
		}

		free(wstr);
		return maxWidth;
	}

	inline GLint getStringWidth(const GLchar * str)
	{
		GLint width = 0;
		GLint maxWidth = 0;
		wchar_t* wstr = nullptr;
		std::multimap<wchar_t, Character>::iterator it;

		Font::multiByteToWideChar(str, &wstr, strlen(str));
		FT_ULong textLength = lstrlenW(wstr);
		for (FT_ULong ch = 0; ch < textLength; ++ch)
		{
			it = characters.find(wstr[ch]);
			if (it == characters.end())
			{
				if (addCharacter(wstr[ch]))
				{
					return -1;
				}
				it = characters.find(wstr[ch]);
			}

			if (wstr[ch] == '\n')
			{
				if (width>maxWidth)
				{
					maxWidth = width;
				}
				width = 0;
				continue;
			}

			width += ((*it).second.advance >> 6);

		}

		if (width>maxWidth)
		{
			maxWidth = width;
		}

		free(wstr);
		return maxWidth;
	}

	inline GLint getStringHeight(std::string & str)
	{
		GLint height = size.y;
		wchar_t* wstr = nullptr;
		std::multimap<wchar_t, Character>::iterator it;

		Font::multiByteToWideChar(str.c_str(), &wstr, str.length());
		FT_ULong textLength = lstrlenW(wstr);
		for (FT_ULong ch = 0; ch < textLength; ++ch)
		{

			it = characters.find(wstr[ch]);
			if (it == characters.end())
			{
				if (addCharacter(wstr[ch]))
				{
					return -1;
				}
				it = characters.find(wstr[ch]);
			}
			if (wstr[ch] == '\n')
			{
				height += size.y;
				continue;
			}
			//std::cout << width << std::endl;

		}

		free(wstr);
		return height;
	}

	inline GLint getStringHeight(const GLchar * str)
	{
		GLint height = size.y;
		wchar_t* wstr = nullptr;
		std::multimap<wchar_t, Character>::iterator it;

		Font::multiByteToWideChar(str, &wstr, strlen(str));
		FT_ULong textLength = lstrlenW(wstr);
		for (FT_ULong ch = 0; ch < textLength; ++ch)
		{

			it = characters.find(wstr[ch]);
			if (it == characters.end())
			{
				if (addCharacter(wstr[ch]))
				{
					return -1;
				}
				it = characters.find(wstr[ch]);
			}
			if (wstr[ch] == '\n')
			{
				height += size.y;
				continue;
			}
			//std::cout << width << std::endl;

		}

		free(wstr);
		return height;
	}

	inline static wchar_t * multiByteToWideChar(const char * lpcszStr, int dwSize)
	{
#ifdef WIN32
		if (!dwSize)
		{
			return nullptr;
		}
		dwSize *= 4;
		wchar_t *lpwszStr = (wchar_t*)malloc(dwSize);
		std::memset(lpwszStr, 0, dwSize);
		GLuint newSize = (MultiByteToWideChar(0, 0, lpcszStr, strlen(lpcszStr), lpwszStr, strlen(lpcszStr)) + 1)*sizeof(wchar_t);
		return (wchar_t*)realloc(lpwszStr, newSize);
#endif
	}

	inline static void multiByteToWideChar(const char * lpcszStr, wchar_t ** lpwszStr, int dwSize)
	{
#ifdef WIN32
		if (!dwSize)
		{
			return;
		}
		dwSize *= 4;
		*lpwszStr = (wchar_t*)malloc(dwSize);
		std::memset(*lpwszStr, 0, dwSize);
		GLuint newSize = (MultiByteToWideChar(0, 0, lpcszStr, strlen(lpcszStr), *lpwszStr, strlen(lpcszStr)) + 1)*sizeof(wchar_t);
		*lpwszStr = (wchar_t*)realloc(*lpwszStr, newSize);
		
#endif
	}
	static void invertColor(msdfgen::Bitmap<msdfgen::FloatRGB> &bitmap)
	{
		for (GLint y = 0; y < bitmap.height(); ++y)
		{
			for (GLint x = 0; x < bitmap.width(); ++x)
			{
				bitmap(x, y).r = 1.f - bitmap(x, y).r;
				bitmap(x, y).g = 1.f - bitmap(x, y).g;
				bitmap(x, y).b = 1.f - bitmap(x, y).b;
			}
		}
	}
	~Font();
private:
	GLint addCharacterNormal(wchar_t ch);
public:
	glm::ivec2 size;
	//FT_Library ft;
	FT_Face face;
	FT_GlyphSlot slot;
	std::multimap<wchar_t, Character> characters;
	msdfgen::FreetypeHandle * ft;
	msdfgen::FontHandle * font;
};

