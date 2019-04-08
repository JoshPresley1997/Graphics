#include "Window.h"

Window::Window(const std::string& title, int width, int height)
{
	//use SDL to create the window
	this->sdlWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_FLAG);
	//throw a custom exception with data if creation fails
	if (this->sdlWindow == nullptr)
	{
		throw window_exception(SDL_GetError());
	}
	else
	{
		//otherwise, begin setting up the renderer
		this->InitRenderer();
	}
}

void Window::InitRenderer()
{
	{
		//create a GL context for the window
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
//update the window when necessary. This gets called when the state changes.
void Window::Update()
{
	SDL_GL_SwapWindow(this->sdlWindow);
}
//use a constructor to create the SDL window object
Window::Window(const std::string& title, int x, int y, int width, int height)
{
	this->sdlWindow = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_SHOWN);
}

//free the sdl resources on quit
Window::~Window()
{
	SDL_GL_DeleteContext(this->sdlGLContext);
	SDL_DestroyWindow(this->sdlWindow);
}