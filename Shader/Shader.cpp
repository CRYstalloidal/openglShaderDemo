
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Shader.h"

using namespace std;

// ���캯��
Shader::Shader(const char* vertexShader, const char* fragmentShader)
{


	vertexSource = vertexShader;
	fragmentSource = fragmentShader;


	// ������ɫ��
	unsigned int vertex, fragment;

	// ������ɫ��
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexSource, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");

	// Ƭ����ɫ��
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentSource, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");

	// ��ɫ����
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID); // ȷ����������λ��
	checkCompileErrors(ID, "PROGRAM");

	// ɾ����ɫ��
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

// ������ɫ������
void Shader::use()
{
	glUseProgram(ID);
}

// �����ɫ��glsl���Դ���
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
