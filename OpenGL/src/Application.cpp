#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

struct Vertex
{
	float x, y, u, v;
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
		    {-0.5f, -0.5f, 0.0f, 0.0f},
			 {0.5f, -0.5f, 1.0f, 0.0f},
			 {0.5f,  0.5f, 1.0f, 1.0f},
			{-0.5f,  0.5f, 0.0f, 1.0f}
	};

	unsigned int  indices[] = 
	{
			0,1,2,
			2,3,0
	};

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	VertexArray va;
	VertexBuffer vb(vertices, 4 * sizeof(Vertex));
	
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	IndexBuffer ib(indices, 6);

	Shader shader("resources/shaders/Basic.shader");
	shader.Bind();
	shader.SetUniform4f("u_Color", 0.4f, 0.0f, 0.0f, 1.0f);
	

	Texture texture("res/textures/Symbol.png");
	texture.Bind();
	shader.SetUniform1i("u_Texture", 0);

	va.Unbind();
	vb.UnBind();
	ib.UnBind();
	shader.Unbind();

	Renderer renderer;

	float r = 0.1f;
	float increment = 0.05f;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		renderer.Clear();

		if (r >= 0.9 || r <= 0.1)
			increment = -increment;
		r += increment;

		shader.Bind();
		shader.SetUniform4f("u_Color", r, 0.0f, 0.0f, 1.0f);

		renderer.Draw(va,ib,shader);
		// glDrawArrays(GL_TRIANGLES,0,6);			// With out indexes

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}