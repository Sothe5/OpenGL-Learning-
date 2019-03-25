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