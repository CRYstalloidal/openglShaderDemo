
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Shader.h"

using namespace std;

// 构造函数
Shader::Shader(const char* vertexShader, const char* fragmentShader)
{


	vertexSource = vertexShader;
	fragmentSource = fragmentShader;


	// 编译着色器
	unsigned int vertex, fragment;

	// 顶点着色器
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexSource, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");

	// 片段着色器
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentSource, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");

	// 着色程序
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID); // 确定函数具体位置
	checkCompileErrors(ID, "PROGRAM");

	// 删除着色器
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

// 激活着色器程序
void Shader::use()
{
	glUseProgram(ID);
}

// 检查着色器glsl语言错误
void Shader::checkCompileErrors(unsigned int ID, std::string type)
{
	int success;
	char infolog[512];
	if (type != "PROGRAM")
	{
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(ID, 512, NULL, infolog);
			cout << "shader compile error:" << infolog << endl;
		}
	}
	else
	{
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infolog);
			cout << "program link error:" << infolog << endl;
		}
	}
}
