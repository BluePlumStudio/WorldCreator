#include "Font.h"

using namespace std;

/*
StdShaderProgram Font::textProgram;
GLint Font::colorLoc = -1;
GLint Font::dwProjectionLoc = -1;
*/

Font::Font()
{

	characters.clear();

}

FT_Error Font::init(const GLchar * fontPath, FT_UInt width, FT_UInt height)
{
	
	
	FT_Error ret;

	ret = FT_Init_FreeType(&ft);
	if (ret)
	{
#ifdef _DEBUG
		cout <<"FreeType Library 初始化失败！" << endl;
#endif
		return ret;
	}

	ret = FT_New_Face(ft, fontPath, 0, &face);
	if (ret)
	{
#ifdef _DEBUG
		cout<<"加载字体："<<fontPath<<" 失败！"<<endl;
#endif
		return ret;
	}
#ifdef _DEBUG
	cout << "加载字体：" << fontPath << " 成功！" << endl;
#endif

	FT_Select_Charmap(face, FT_ENCODING_UNICODE);
	FT_Set_Pixel_Sizes(face, width, height);
	//FT_Set_Char_Size(face, width, height, 1000, 1000);
	size.x = GLfloat(width);
	size.y = GLfloat(height);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	slot = face->glyph;

	for (wchar_t ch = 0; ch < 128; ++ch)
	{
		addCharacter(ch);
	}

	return ret;
}

FT_Error Font::addCharacter(wchar_t ch)
{
	FT_Error ret = 0;
	FT_Bitmap* bitmap;
	GLubyte *textureSrcData;
	GLubyte *textureData;
	//GLuint width; 
	FT_UInt charIndex;

	//width = (GLuint)pow(2, ceil(log2(size.y)));
	charIndex = FT_Get_Char_Index(face, ch);

	ret = FT_Load_Glyph(face, charIndex, FT_LOAD_DEFAULT | FT_LOAD_FORCE_AUTOHINT);
	if (ret)
	{
		return ret;
	}

	ret = FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL);
	if (ret)
	{
		return ret;
	}

	bitmap = &(slot->bitmap);
	textureSrcData = bitmap->buffer;
	textureData = new GLubyte[bitmap->width*bitmap->rows * 4 + 1];
	if (!textureData)
	{
		return 1;
	}
	memset(textureData, 0, (bitmap->width *bitmap->rows * 4 + 1) * sizeof(GLubyte));

	for (GLuint i = 0; i < bitmap->rows; i++)
	{
		for (GLuint j = 0; j < bitmap->width; j++)
		{
			textureData[(i * bitmap->width + j) * 4 + 0] = textureData[(i * bitmap->width + j) * 4 + 1] = textureData[(i * bitmap->width + j) * 4 + 2] = 255U;
			textureData[(i * bitmap->width + j) * 4 + 3] = *textureSrcData;
			textureSrcData++;
		}
	}
	/*
	stringstream ss;
	ss << "Chars/" << face->family_name << " " << ch << ".png";
	SOIL_save_image(ss.str().c_str(), SOIL_SAVE_TYPE_BMP, bitmap->width, bitmap->rows, SOIL_LOAD_RGBA, textureData);
	*/

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE0);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		bitmap->width,
		bitmap->rows,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		textureData);
	// 设置纹理选项
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	delete[] textureData;

	// 储存字符供之后使用
	Character character;
	//character.textureID = texture;
	character.characterTexture.init(texture, GL_TEXTURE0);
	character.size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
	character.bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
	character.advance = face->glyph->advance.x;
	characters.insert(pair<wchar_t, Character>(ch, character));
	glBindTexture(GL_TEXTURE_2D, 0);
	return ret;
	
}

Font & Font::operator = (const Font & right)
{
	ft = right.ft;
	face = right.face;
	characters = right.characters;
	return *this;
}

GLboolean Font::getCharacterData(wchar_t character, glm::vec4 & color, glm::vec3 & coords, GLfloat scale, DrawList & drawList, CharacterTexture2D & texture)
{
	map<wchar_t, Character>::iterator it = characters.find(character);
	Character ch;
	if (it == characters.end())
	{
		if (addCharacter(character))
		{
			return false;
		}
		it = characters.find(character);
	}
	ch = (*it).second;
	

	GLfloat xPos = coords.x + ch.bearing.x * scale;
	GLfloat yPos = coords.y - (ch.size.y - ch.bearing.y) * scale;
	GLfloat zPos = coords.z;

	GLfloat w = ch.size.x * scale;
	GLfloat h = ch.size.y * scale;

	drawList.data[0] = xPos;
	drawList.data[1] = yPos + h;
	drawList.data[2] = zPos;
	drawList.data[3] = 0.0f;
	drawList.data[4] = 0.0f;
	drawList.data[5] = color.r;
	drawList.data[6] = color.g;
	drawList.data[7] = color.b;
	drawList.data[8] = color.a;

	drawList.data[9] = xPos;
	drawList.data[10] = yPos;
	drawList.data[11] = zPos;
	drawList.data[12] = 0.0f;
	drawList.data[13] = 1.0f;
	drawList.data[14] = color.r;
	drawList.data[15] = color.g;
	drawList.data[16] = color.b;
	drawList.data[17] = color.a;

	drawList.data[18] = xPos + w;
	drawList.data[19] = yPos;
	drawList.data[20] = zPos;
	drawList.data[21] = 1.0f;
	drawList.data[22] = 1.0f;
	drawList.data[23] = color.r;
	drawList.data[24] = color.g;
	drawList.data[25] = color.b;
	drawList.data[26] = color.a;

	drawList.data[27] = xPos;
	drawList.data[28] = yPos + h;
	drawList.data[29] = zPos;
	drawList.data[30] = 0.0f;
	drawList.data[31] = 0.0f;
	drawList.data[32] = color.r;
	drawList.data[33] = color.g;
	drawList.data[34] = color.b;
	drawList.data[35] = color.a;

	drawList.data[36] = xPos + w;
	drawList.data[37] = yPos;
	drawList.data[38] = zPos;
	drawList.data[39] = 1.0f;
	drawList.data[40] = 1.0f;
	drawList.data[41] = color.r;
	drawList.data[42] = color.g;
	drawList.data[43] = color.b;
	drawList.data[44] = color.a;

	drawList.data[45] = xPos + w;
	drawList.data[46] = yPos + h;
	drawList.data[47] = zPos;
	drawList.data[48] = 1.0f;
	drawList.data[49] = 0.0f;
	drawList.data[50] = color.r;
	drawList.data[51] = color.g;
	drawList.data[52] = color.b;
	drawList.data[53] = color.a;

	texture.init(ch.characterTexture.ID, ch.characterTexture.level);

	return true;
}

GLboolean Font::getStringData(string str, glm::vec4 & color, glm::vec3 & coords, GLfloat scale, vector<DrawList> & drawLists/*size = 54*/, vector<CharacterTexture2D> & textures)
{
	wchar_t* wstr = nullptr;
	Font::multiByteToWideChar(str.c_str(), &wstr, str.length());
	GLuint strLength = 0;
	map<wchar_t, Character>::iterator it;

	strLength = lstrlenW(wstr);
	drawLists.resize(strLength);
	textures.resize(strLength);
	for (GLuint i = 0; i < strLength; ++i)
	{
		it = characters.find(wstr[i]);
		Character ch;
		if (it == characters.end())
		{
			if (addCharacter(wstr[i]))
			{
				return false;
			}
			it = characters.find(wstr[i]);
		}
		ch = (*it).second;


		GLfloat xPos = coords.x + ch.bearing.x * scale;
		GLfloat yPos = coords.y - (ch.size.y - ch.bearing.y) * scale;
		GLfloat zPos = coords.z;

		GLfloat w = ch.size.x * scale;
		GLfloat h = ch.size.y * scale;

		drawLists[i].data.resize(54);

		drawLists[i].data[0] = xPos;
		drawLists[i].data[1] = yPos + h;
		drawLists[i].data[2] = zPos;
		drawLists[i].data[3] = 0.0f;
		drawLists[i].data[4] = 0.0f;
		drawLists[i].data[5] = color.r;
		drawLists[i].data[6] = color.g;
		drawLists[i].data[7] = color.b;
		drawLists[i].data[8] = color.a;

		drawLists[i].data[9] = xPos;
		drawLists[i].data[10] = yPos;
		drawLists[i].data[11] = zPos;
		drawLists[i].data[12] = 0.0f;
		drawLists[i].data[13] = 1.0f;
		drawLists[i].data[14] = color.r;
		drawLists[i].data[15] = color.g;
		drawLists[i].data[16] = color.b;
		drawLists[i].data[17] = color.a;

		drawLists[i].data[18] = xPos + w;
		drawLists[i].data[19] = yPos;
		drawLists[i].data[20] = zPos;
		drawLists[i].data[21] = 1.0f;
		drawLists[i].data[22] = 1.0f;
		drawLists[i].data[23] = color.r;
		drawLists[i].data[24] = color.g;
		drawLists[i].data[25] = color.b;
		drawLists[i].data[26] = color.a;

		drawLists[i].data[27] = xPos;
		drawLists[i].data[28] = yPos + h;
		drawLists[i].data[29] = zPos;
		drawLists[i].data[30] = 0.0f;
		drawLists[i].data[31] = 0.0f;
		drawLists[i].data[32] = color.r;
		drawLists[i].data[33] = color.g;
		drawLists[i].data[34] = color.b;
		drawLists[i].data[35] = color.a;

		drawLists[i].data[36] = xPos + w;
		drawLists[i].data[37] = yPos;
		drawLists[i].data[38] = zPos;
		drawLists[i].data[39] = 1.0f;
		drawLists[i].data[40] = 1.0f;
		drawLists[i].data[41] = color.r;
		drawLists[i].data[42] = color.g;
		drawLists[i].data[43] = color.b;
		drawLists[i].data[44] = color.a;

		drawLists[i].data[45] = xPos + w;
		drawLists[i].data[46] = yPos + h;
		drawLists[i].data[47] = zPos;
		drawLists[i].data[48] = 1.0f;
		drawLists[i].data[49] = 0.0f;
		drawLists[i].data[50] = color.r;
		drawLists[i].data[51] = color.g;
		drawLists[i].data[52] = color.b;
		drawLists[i].data[53] = color.a;

		textures[i].init(ch.characterTexture.ID, ch.characterTexture.level);

		coords.x += (getCharacterAdvance(wstr[i]) >> 6) * scale;
	}
	free(wstr);

	return true;
}

Font::~Font()
{
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
	
	for (map<wchar_t, Character>::iterator it = characters.begin(); it != characters.end(); ++it)
	{
		glDeleteTextures(1, &(*it).second.characterTexture.ID);
	}
}


/**/

Font::CharacterTexture2D::CharacterTexture2D()
{
	level = GL_TEXTURE0;

}

Font::CharacterTexture2D::CharacterTexture2D(const CharacterTexture2D & right)
{
	ID = right.ID;
	level = right.level;
}

Font::CharacterTexture2D & Font::CharacterTexture2D::operator = (const CharacterTexture2D & right)
{
	ID = right.ID;
	level = right.level;

	return *this;
}

GLuint Font::CharacterTexture2D::init(const char * texturePath, GLenum level)
{
	ID = 0;
	GLint width = 0;
	GLint height = 0;
	unsigned char* image = nullptr;
	image = SOIL_load_image(texturePath, &width, &height, 0, SOIL_LOAD_RGBA);
	if (!image)
	{
#ifdef _DEBUG
		cout << "字符纹理初始化失败！" << endl;
#endif
		return 1;
	}
	this->level = level;
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glActiveTexture(level);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	//glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
#ifdef _DEBUG
	cout << "字符纹理：" << ID << " 创建成功！" << endl;
#endif

	return 0;
}

GLvoid Font::CharacterTexture2D::init(GLuint textureID, GLenum level)
{
	this->ID = textureID;
	this->level = level;
}
Font::CharacterTexture2D::~CharacterTexture2D()
{
	//cout << "+1s" << endl;
}

/**/
