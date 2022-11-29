#pragma comment(lib,"glew32.lib")
#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
using namespace std;

// 顶点数据
float vertices[] = { // 逆时针绘制正面
	// 位置					// 颜色
	-0.5f, -0.5f, 0.0f,	1.0f, 0, 0, // 0
	0.5f, -0.5f, 0.0f,		0, 1.0f, 0, // 1
	0.0f,  0.5f, 0.0f,		0, 0, 1.0f, // 2
};

// 索引缓冲对象
unsigned int indices[] = {
	0, 1, 2, // 三角形
};



int main()
{
	// ---------------------------------------------------------------
	// ---------------------------------------------------------------
	// 初始化GLFW
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
		glfwTerminate(); // 终止glfw
		return -1; // 失败
	}
	glfwMakeContextCurrent(window); // 通知GLFW将我们窗口的上下文设置为当前线程的主上下文了

		// Init GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		cout << "Init GLEW failed." << endl;
		glfwTerminate(); 
		return -1; 
	}

	// 渲染窗口及线条设置
	glViewport(0, 0, 800, 600); 

	char vertexShader[400] = "#version 330 core \n layout(location = 0)  in vec3 aPos;\n layout(location = 1)  in vec3 aColor;\n out vec4 vertexColor;\n void main() { gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); vertexColor = vec4(aColor.x, aColor.y, aColor.z, 1.0);}";
	char fragmentShader[400] = "#version 330 core \n in vec4 vertexColor;\n out vec4 FragColor;\n void main() { FragColor = vertexColor; }";
	// 生成着色器
	Shader* myShader = new Shader(vertexShader, fragmentShader);



	// 1.绑定VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO); 
	glBindVertexArray(VAO); 

	// 2.把顶点数组复制到缓冲中供OpenGL使用,将顶点数据存入VBO中
	unsigned int VBO; 
	glGenBuffers(1, &VBO); 
	glBindBuffer(GL_ARRAY_BUFFER, VBO); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

	// 3.复制索引数组到一个索引缓冲中，供OpenGL使用
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4.设置顶点属性指针,告诉OpenGL该如何解析顶点数据
	// 位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);



	while (!glfwWindowShouldClose(window)) 
	{

		glClearColor(0.2f, 0.3f, 0.5f, 1.0f); // 设置清空屏幕所用的颜色
		glClear(GL_COLOR_BUFFER_BIT); // 清空颜色缓冲


		myShader->use();

		glDrawElements(GL_TRIANGLES, 3 * 4, GL_UNSIGNED_INT, 0); // 绘制物体

		glfwPollEvents(); 
		glfwSwapBuffers(window); 
	}


	glfwTerminate(); // 终止glfw，释放资源
	return 0;
}