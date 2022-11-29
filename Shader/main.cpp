#pragma comment(lib,"glew32.lib")
#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
using namespace std;

// ��������
float vertices[] = { // ��ʱ���������
	// λ��					// ��ɫ
	-0.5f, -0.5f, 0.0f,	1.0f, 0, 0, // 0
	0.5f, -0.5f, 0.0f,		0, 1.0f, 0, // 1
	0.0f,  0.5f, 0.0f,		0, 0, 1.0f, // 2
};

// �����������
unsigned int indices[] = {
	0, 1, 2, // ������
};



int main()
{
	// ---------------------------------------------------------------
	// ---------------------------------------------------------------
	// ��ʼ��GLFW
	// ---------------------------------------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

	// Open GLFW Window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Triangle", NULL, NULL); 
	if (window == NULL)
	{
		cout << "Create Window Failed." << endl;
		glfwTerminate(); // ��ֹglfw
		return -1; // ʧ��
	}
	glfwMakeContextCurrent(window); // ֪ͨGLFW�����Ǵ��ڵ�����������Ϊ��ǰ�̵߳�����������

		// Init GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		cout << "Init GLEW failed." << endl;
		glfwTerminate(); 
		return -1; 
	}

	// ��Ⱦ���ڼ���������
	glViewport(0, 0, 800, 600); 

	char vertexShader[400] = "#version 330 core \n layout(location = 0)  in vec3 aPos;\n layout(location = 1)  in vec3 aColor;\n out vec4 vertexColor;\n void main() { gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); vertexColor = vec4(aColor.x, aColor.y, aColor.z, 1.0);}";
	char fragmentShader[400] = "#version 330 core \n in vec4 vertexColor;\n out vec4 FragColor;\n void main() { FragColor = vertexColor; }";
	// ������ɫ��
	Shader* myShader = new Shader(vertexShader, fragmentShader);



	// 1.��VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO); 
	glBindVertexArray(VAO); 

	// 2.�Ѷ������鸴�Ƶ������й�OpenGLʹ��,���������ݴ���VBO��
	unsigned int VBO; 
	glGenBuffers(1, &VBO); 
	glBindBuffer(GL_ARRAY_BUFFER, VBO); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

	// 3.�����������鵽һ�����������У���OpenGLʹ��
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4.���ö�������ָ��,����OpenGL����ν�����������
	// λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// ��ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);



	while (!glfwWindowShouldClose(window)) 
	{

		glClearColor(0.2f, 0.3f, 0.5f, 1.0f); // ���������Ļ���õ���ɫ
		glClear(GL_COLOR_BUFFER_BIT); // �����ɫ����


		myShader->use();

		glDrawElements(GL_TRIANGLES, 3 * 4, GL_UNSIGNED_INT, 0); // ��������

		glfwPollEvents(); 
		glfwSwapBuffers(window); 
	}


	glfwTerminate(); // ��ֹglfw���ͷ���Դ
	return 0;
}