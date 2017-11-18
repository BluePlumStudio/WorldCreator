#include "ShaderProgram.h"

using namespace std;



StdShaderProgram::StdShaderProgram()
{
	ID = 0;
	VSID = 0;
	FSID = 0;
	vertexShaderPath.clear();
	fragmentShaderPath.clear();
}

StdShaderProgram::StdShaderProgram(const StdShaderProgram & right)
{
	ID = 0;
	VSID = 0;
	FSID = 0;
	vertexShaderPath = right.vertexShaderPath;
	fragmentShaderPath = right.fragmentShaderPath;

	GLint ret = init();
	if (ret)
	{
		throw ret;
	}
}

GLint StdShaderProgram::init(const GLchar * vertexShaderPath, const GLchar * fragmentShaderPath)
{
	string vsCode = "";
	string fsCode = "";
	stringstream vsStream;
	stringstream fsStream;
	ifstream vsFile;
	ifstream fsFile;

	vsFile.exceptions(ifstream::badbit);
	fsFile.exceptions(ifstream::badbit);
	try
	{
		if (!vertexShaderPath)
		{
			throw string("������ɫ��·��Ϊ�գ�");
		}
		if (!fragmentShaderPath)
		{
			throw string("ƬԪ��ɫ��·��Ϊ�գ�");
		}

		this->vertexShaderPath = vertexShaderPath;
		this->fragmentShaderPath = fragmentShaderPath;

		vsFile.open(vertexShaderPath);
		if (!vsFile.is_open())
		{
			throw string("������ɫ����ʧ�ܣ���") + vertexShaderPath;
		}
		fsFile.open(fragmentShaderPath);
		if (!fsFile.is_open())
		{
			throw string("ƬԪ��ɫ����ʧ�ܣ���") + fragmentShaderPath;
		}

		vsStream << vsFile.rdbuf();
		fsStream << fsFile.rdbuf();
		vsFile.close();
		fsFile.close();

		vsCode = vsStream.str();
		fsCode = fsStream.str();
	}
	catch (string & errorMessage)
	{
		cout << errorMessage << endl;
		return 1;
	}
	catch (ifstream::failure error)
	{
		cout << "��ɫ����ȡʧ�ܣ�" << endl;
		return 1;
	}
	catch (...)
	{
		cout << "��ɫ����ȡʧ�ܣ�δ֪���󣩣�" << endl;
		return 1;
	}

	const GLchar * vsCCode = vsCode.c_str();
	const GLchar * fsCCode = fsCode.c_str();
	GLint success = 0;
	GLchar infoLog[1024] = "";
	
	VSID = glCreateShader(GL_VERTEX_SHADER);
	if (!glIsShader(VSID))
	{
		cout << "������ɫ������ʧ�ܣ���" << vertexShaderPath << endl;
		return 1;
	}
	
	FSID = glCreateShader(GL_FRAGMENT_SHADER);
	if (!glIsShader(FSID))
	{
		cout << "ƬԪ��ɫ������ʧ�ܣ���" << fragmentShaderPath << endl;
		return 1;
	}
	
	glShaderSource(VSID, 1, &vsCCode, nullptr);
	glShaderSource(FSID, 1, &fsCCode, nullptr);

	GLint infoLogLength = 0;

	glCompileShader(VSID);
	glGetShaderiv(VSID, GL_COMPILE_STATUS, &success);
	glGetShaderiv(VSID, GL_INFO_LOG_LENGTH, &infoLogLength);
	glGetShaderInfoLog(VSID, sizeof(infoLog), nullptr, infoLog);
	if (infoLogLength)
	{
		cout << infoLog << endl;
	}
	if (!success)
	{
		cout << "������ɫ������ʧ�ܣ���" << vertexShaderPath << endl;
		return 1;
	}
	glCompileShader(FSID);
	glGetShaderiv(FSID, GL_COMPILE_STATUS, &success);
	glGetShaderiv(FSID, GL_INFO_LOG_LENGTH, &infoLogLength);
	glGetShaderInfoLog(FSID, sizeof(infoLog), nullptr, infoLog);
	if (infoLogLength)
	{
		cout << infoLog << endl;
	}
	if (!success)
	{
		cout << "ƬԪ��ɫ������ʧ�ܣ���" << fragmentShaderPath << endl;
		return 1;
	}

	ID = glCreateProgram();
	glAttachShader(ID, VSID);
	glAttachShader(ID, FSID);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &infoLogLength);
	glGetProgramInfoLog(ID, sizeof(infoLog), nullptr, infoLog);
	if (infoLogLength)
	{
		cout << infoLog << endl;
	}
	if (!success)
	{
		
		cout << "��ɫ����������ʧ�ܣ���" << ID << endl;
		return 1;
	}

	cout << "��ɫ������" << ID << " �����ɹ�����" << vertexShaderPath << "|" << fragmentShaderPath << endl;

	return 0;
}

GLint StdShaderProgram::init()
{
	string vsCode = "";
	string fsCode = "";
	stringstream vsStream;
	stringstream fsStream;
	ifstream vsFile;
	ifstream fsFile;

	vsFile.exceptions(ifstream::badbit);
	fsFile.exceptions(ifstream::badbit);
	try
	{
		if (!this->vertexShaderPath.c_str())
		{
			throw "������ɫ��·��Ϊ�գ�";
		}
		if (!this->fragmentShaderPath.c_str())
		{
			throw "ƬԪ��ɫ��·��Ϊ�գ�";
		}

		vsFile.open(vertexShaderPath);
		if (!vsFile.is_open())
		{
			throw "������ɫ����ʧ�ܣ�";
		}
		fsFile.open(fragmentShaderPath);
		if (!fsFile.is_open())
		{
			throw "ƬԪ��ɫ����ʧ�ܣ�";
		}

		vsStream << vsFile.rdbuf();
		fsStream << fsFile.rdbuf();
		vsFile.close();
		fsFile.close();

		vsCode = vsStream.str();
		fsCode = fsStream.str();
	}
	catch (GLchar * errorMessage)
	{
		cout << errorMessage << endl;
		return 1;
	}
	catch (ifstream::failure error)
	{
		cout << "��ɫ����ȡʧ�ܣ�" << endl;
		return 1;
	}
	catch (...)
	{
		cout << "��ɫ����ȡʧ�ܣ�δ֪���󣩣�" << endl;
		return 1;
	}

	const GLchar * vsCCode = vsCode.c_str();
	const GLchar * fsCCode = fsCode.c_str();
	GLint success = 0;
	GLchar infoLog[1024] = "";

	VSID = glCreateShader(GL_VERTEX_SHADER);
	if (!glIsShader(VSID))
	{
		cout << "������ɫ������ʧ�ܣ�" << endl;
		return 1;
	}

	FSID = glCreateShader(GL_FRAGMENT_SHADER);
	if (!glIsShader(FSID))
	{
		cout << "ƬԪ��ɫ������ʧ�ܣ�" << endl;
		return 1;
	}

	glShaderSource(VSID, 1, &vsCCode, nullptr);
	glShaderSource(FSID, 1, &fsCCode, nullptr);

	GLint infoLogLength = 0;

	glCompileShader(VSID);
	glGetShaderiv(VSID, GL_COMPILE_STATUS, &success);
	glGetShaderiv(VSID, GL_INFO_LOG_LENGTH, &infoLogLength);
	glGetShaderInfoLog(VSID, sizeof(infoLog), nullptr, infoLog);
	if (infoLogLength)
	{
		cout << infoLog << endl;
	}
	if (!success)
	{
		cout << "������ɫ������ʧ�ܣ�" << endl;
		return 1;
	}
	glCompileShader(FSID);
	glGetShaderiv(FSID, GL_COMPILE_STATUS, &success);
	glGetShaderiv(FSID, GL_INFO_LOG_LENGTH, &infoLogLength);
	glGetShaderInfoLog(FSID, sizeof(infoLog), nullptr, infoLog);
	if (infoLogLength)
	{
		cout << infoLog << endl;
	}
	if (!success)
	{
		cout << "ƬԪ��ɫ������ʧ�ܣ�" << endl;
		return 1;
	}

	ID = glCreateProgram();
	glAttachShader(ID, VSID);
	glAttachShader(ID, FSID);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &infoLogLength);
	glGetProgramInfoLog(ID, sizeof(infoLog), nullptr, infoLog);
	if (infoLogLength)
	{
		cout << infoLog << endl;
	}
	if (!success)
	{

		cout << "��ɫ����������ʧ�ܣ�" << endl;
		return 1;
	}

	cout << "��ɫ������" << ID << " �����ɹ���" << endl;

	return 0;
}

StdShaderProgram & StdShaderProgram::operator = (const StdShaderProgram & right)
{
	ID = 0;
	VSID = 0;
	FSID = 0;
	vertexShaderPath = right.vertexShaderPath;
	fragmentShaderPath = right.fragmentShaderPath;

	GLint ret = init();
	if (ret)
	{
		throw ret;
	}
	return *this;
}

StdShaderProgram::~StdShaderProgram()
{
	glDeleteProgram(ID);
	glDeleteShader(VSID);
	glDeleteShader(FSID);
}
