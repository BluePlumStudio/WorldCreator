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
		inline static GLvoid clearTexture()
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
	FT_Error init(const GLchar * fontPath, FT_UInt width = 0, FT_UInt height = 16);
	FT_Error addCharacter(wchar_t ch);
	GLboolean getCharacterData(wchar_t character, glm::vec4 & color, glm::vec3 & coords, GLfloat scale, DrawList & drawList/*size = 54*/, CharacterTexture2D & texture);
	GLboolean getStringData(std::string str, glm::vec4 & color, glm::vec3 & coords, GLfloat scale, std::vector<DrawList> & drawLists/*size = 54*/, std::vector<CharacterTexture2D> & textures);
	GLubyte * getCharacterTextureData(wchar_t character);
	inline GLvoid getCharacterAdvance(wchar_t character, GLuint & advance)
	{
		advance = characters[character].advance;
	}
	inline GLuint getCharacterAdvance(wchar_t character)
	{
		return characters[character].advance;
	}
	inline GLvoid getCharacterSize(wchar_t character, glm::ivec2 & size)
	{
		size = characters[character].size;
	}
	inline glm::ivec2 getCharacterSize(wchar_t character)
	{
		return characters[character].size;
	}
	inline GLvoid getCharacterBearing(wchar_t character, glm::ivec2 & bearing)
	{
		bearing = characters[character].bearing;
	}
	inline glm::ivec2 getCharacterBearing(wchar_t character)
	{
		return characters[character].bearing;
	}
	inline GLvoid texParameteri(GLenum pname, GLint param)
	{
		for (std::map<wchar_t, Character>::iterator it = characters.begin(); it != characters.end(); ++it)
		{
			//glBindTexture(GL_TEXTURE_2D, (*it).second.textureID);
			(*it).second.characterTexture.bind();
			glActiveTexture(GL_TEXTURE0);
			glTexParameteri(GL_TEXTURE_2D, pname, param);
			
		}
		CharacterTexture2D::clearTexture();
	}
	inline GLvoid texParameterivec(std::vector<std::pair<GLenum, GLint>>parameters)
	{
		for (std::map<wchar_t, Character>::iterator it = characters.begin(); it != characters.end(); ++it)
		{
			//glBindTexture(GL_TEXTURE_2D, (*it).second.textureID);
			(*it).second.characterTexture.bind();
			glActiveTexture(GL_TEXTURE0);
			for (std::vector<std::pair<GLenum, GLint>>::iterator it = parameters.begin(); it != parameters.end(); ++it)
			{
				glTexParameteri(GL_TEXTURE_2D, (*it).first, (*it).second);
			}
		}
		CharacterTexture2D::clearTexture();
	}

	inline GLint getStringWidth(std::string str)
	{
		GLint width = 0;
		wchar_t* wstr = nullptr;
		std::map<wchar_t, Character>::iterator it;

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
			width += ((*it).second.advance >> 6);

			//std::cout << width << std::endl;

		}
		free(wstr);
		return width;
	}

	inline static wchar_t * multiByteToWideChar(const char * lpcszStr, int dwSize)
	{
#ifdef WIN32
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
		dwSize *= 4;
		*lpwszStr = (wchar_t*)malloc(dwSize);
		std::memset(*lpwszStr, 0, dwSize);
		GLuint newSize = (MultiByteToWideChar(0, 0, lpcszStr, strlen(lpcszStr), *lpwszStr, strlen(lpcszStr)) + 1)*sizeof(wchar_t);
		*lpwszStr = (wchar_t*)realloc(*lpwszStr, newSize);
		
#endif
	}
	~Font();
private:
	
public:
	glm::vec2 size;
	FT_Library ft;
	FT_Face face;
	FT_GlyphSlot slot;
	std::map<wchar_t, Character> characters;
	//msdfgen::FreetypeHandle * msdfFT;
};

