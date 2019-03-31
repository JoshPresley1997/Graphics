#pragma once
#include<SDL2/SDL.h>
#include<iostream>
#include<exception>
#define	SDL_WINDOW_FLAG SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
#define SDL_RENDERER_FLAG SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_WINDOW_OPENGL
class window_exception : public std::runtime_error
{
public:
	window_exception(const std::string& error) : std::runtime_error(error)
	{

	};
};
class gl_context_exception : public std::runtime_error
{
public:
	gl_context_exception(const std::string& error) : std::runtime_error(error)
	{

	};
};
class Window
{
public:
	Window(const std::string& title, int width, int height);
	Window(const std::string& title, int x, int y, int width, int height);
	void Update();
	~Window();
private:
	void InitRenderer();
	SDL_Window* sdlWindow;
	SDL_GLContext sdlGLContext;
};