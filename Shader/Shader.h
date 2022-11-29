#pragma once
#include <string>

class Shader
{
public:
	// ����ID
	unsigned int ID;

	std::string vertexString, fragmentString; // Ѱ���ַ���
	const char* vertexSource, * fragmentSource; // CPU��ʶ����ַ���

	// ��������ȡ��������ɫ��
	Shader(const char* vertexPath, const char* fragmentPath);

	// ʹ��/�������
	void use();

private:
	// �����ɫ��glsl���Դ���
	void checkCompileErrors(unsigned int ID, std::string type);
};


