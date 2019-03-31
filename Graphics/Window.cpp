#include"Window.h"

Window::Window(const std::string& title, int width, int height)
{
	this->sdlWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_FLAG);

	if (this->sdlWindow == nullptr)
	{
		throw window_exception(SDL_GetError());
	}
	else
	{
		this->InitRenderer();
	}
}

void Window::InitRenderer()
{
	{
		this->sdlGLContext = SDL_GL_CreateContext(this->sdlWindow);
		if (this->sdlGLContext == nullptr)
		{
			throw(gl_context_exception(SDL_GetError()));

		}
		else
		{
			if (SDL_GL_SetSwapInterval(1) < 0)
			{
				throw gl_context_exception(SDL_GetError());
			}
		}
	}
}

void Window::Update()
{
	SDL_GL_SwapWindow(this->sdlWindow);
}
Window::Window(const std::string& title, int x, int y, int width, int height)
{
	this->sdlWindow = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_SHOWN);
}

Window::~Window()
{
	SDL_GL_DeleteContext(this->sdlGLContext);
	SDL_DestroyWindow(this->sdlWindow);
}