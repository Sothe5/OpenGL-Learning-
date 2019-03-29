#include "Renderer.h"

#include <iostream>

void GLClearError()
{
	while (glGetError());
}

bool GLLogCall()
{
	while (GLenum error = glGetError())
	{
		std::cout << "OpenGL error: " << error << std::endl;
		return false;
	}
	return true;
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray & va, const IndexBuffer & ib, const Shader & shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
