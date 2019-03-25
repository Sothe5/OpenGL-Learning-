#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

struct Vertex
{
	float x;
	float y;
};

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);


	if (glewInit() != GLEW_OK)
		std::cout << "ERROR Glew Ok" << std::endl;
	
	Vertex vertices[] = 
	{
		    {-0.5f, -0.5f},
			 {0.5f, -0.5f},
			 {0.5f,  0.5f},
			{-0.5f,  0.5f}
	};

	unsigned int  indices[] = 
	{
			0,1,2,
			2,3,0
	};

	VertexArray va;
	VertexBuffer vb(vertices, 4 * sizeof(Vertex));
	
	VertexBufferLayout layout;
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	IndexBuffer ib(indices, 6);

	Shader shader("resources/shaders/Basic.shader");
	shader.Bind();

	shader.SetUniformf4("u_Color", 0.4f, 0.0f, 0.0f, 1.0f);
	
	va.Unbind();
	vb.UnBind();
	ib.UnBind();
	shader.Unbind();

	float r = 0.1f;
	float increment = 0.05f;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		if (r >= 0.9 || r <= 0.1)
			increment = -increment;
		r += increment;

		shader.Bind();
		shader.SetUniformf4("u_Color", r, 0.0f, 0.0f, 1.0f);
		va.Bind();
		ib.Bind();

		GLCall(glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,nullptr));
		// glDrawArrays(GL_TRIANGLES,0,6);			// With out indexes

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}