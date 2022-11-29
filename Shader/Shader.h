#pragma once
#include <string>

class Shader
{
public:
	// 程序ID
	unsigned int ID;

	std::string vertexString, fragmentString; // 寻常字符串
	const char* vertexSource, * fragmentSource; // CPU能识别的字符串

	// 构造器读取并构建着色器
	Shader(const char* vertexPath, const char* fragmentPath);

	// 使用/激活程序
	void use();

private:
	// 检查着色器glsl语言错误
	void checkCompileErrors(unsigned int ID, std::string type);
};


