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
			throw string("顶点着色器路径为空！");
		}
		if (!fragmentShaderPath)
		{
			throw string("片元着色器路径为空！");
		}

		this->vertexShaderPath = vertexShaderPath;
		this->fragmentShaderPath = fragmentShaderPath;

		vsFile.open(vertexShaderPath);
		if (!vsFile.is_open())
		{
			throw string("顶点着色器打开失败！：") + vertexShaderPath;
		}
		fsFile.open(fragmentShaderPath);
		if (!fsFile.is_open())
		{
			throw string("片元着色器打开失败！：") + fragmentShaderPath;
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
		cout << "着色器读取失败！" << endl;
		return 1;
	}
	catch (...)
	{
		cout << "着色器读取失败（未知错误）！" << endl;
		return 1;
	}

	const GLchar * vsCCode = vsCode.c_str();
	const GLchar * fsCCode = fsCode.c_str();
	GLint success = 0;
	GLchar infoLog[1024] = "";
	
	VSID = glCreateShader(GL_VERTEX_SHADER);
	if (!glIsShader(VSID))
	{
		cout << "顶点着色器创建失败！：" << vertexShaderPath << endl;
		return 1;
	}
	
	FSID = glCreateShader(GL_FRAGMENT_SHADER);
	if (!glIsShader(FSID))
	{
		cout << "片元着色器创建失败！：" << fragmentShaderPath << endl;
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
		cout << "顶点着色器编译失败！：" << vertexShaderPath << endl;
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
		cout << "片元着色器编译失败！：" << fragmentShaderPath << endl;
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
		
		cout << "着色器程序链接失败！：" << ID << endl;
		return 1;
	}

	cout << "着色器程序：" << ID << " 创建成功！：" << vertexShaderPath << "|" << fragmentShaderPath << endl;

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
			throw "顶点着色器路径为空！";
		}
		if (!this->fragmentShaderPath.c_str())
		{
			throw "片元着色器路径为空！";
		}

		vsFile.open(vertexShaderPath);
		if (!vsFile.is_open())
		{
			throw "顶点着色器打开失败！";
		}
		fsFile.open(fragmentShaderPath);
		if (!fsFile.is_open())
		{
			throw "片元着色器打开失败！";
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
		cout << "着色器读取失败！" << endl;
		return 1;
	}
	catch (...)
	{
		cout << "着色器读取失败（未知错误）！" << endl;
		return 1;
	}

	const GLchar * vsCCode = vsCode.c_str();
	const GLchar * fsCCode = fsCode.c_str();
	GLint success = 0;
	GLchar infoLog[1024] = "";

	VSID = glCreateShader(GL_VERTEX_SHADER);
	if (!glIsShader(VSID))
	{
		cout << "顶点着色器创建失败！" << endl;
		return 1;
	}

	FSID = glCreateShader(GL_FRAGMENT_SHADER);
	if (!glIsShader(FSID))
	{
		cout << "片元着色器创建失败！" << endl;
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
		cout << "顶点着色器编译失败！" << endl;
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
		cout << "片元着色器编译失败！" << endl;
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

		cout << "着色器程序链接失败！" << endl;
		return 1;
	}

	cout << "着色器程序：" << ID << " 创建成功！" << endl;

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
