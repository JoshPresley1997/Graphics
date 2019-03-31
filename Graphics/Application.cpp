#include "Application.h"
#include <SDL2/SDL.h>
#include <Windows.h>	
#include <GL/GL.h>

Application* Application::applicationInstance = nullptr;

Application* Application::Instance()
{
	if (Application::applicationInstance == nullptr)
	{
		Application::applicationInstance = new Application();
	}
	return Application::applicationInstance;
}


Application::Application()
{
	try
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			throw application_exception(SDL_GetError());
		}
		else
		{
			this->window = new Window("Graphics Project", 640, 480);
		}
	}
	catch (application_exception& exception)
	{
		std::cout << "Application Error: ";
#ifdef _DEBUG
		std::cout << "Line 20 in Application.cpp" << std::endl;
#endif // _DEBUG

		std::cout << exception.what() << std::endl;
	}
	catch (window_exception& exception)
	{
		std::cout << "Window Error: ";
#ifdef _DEBUG
		std::cout << "Line 5 in Window.cpp" << std::endl;
#endif // _DEBUG

		std::cout << exception.what() << std::endl;
	}
	catch (gl_context_exception& exception)
	{
		std::cout << "Gl Context Error: ";
#ifdef _DEBUG
		std::cout << "in Window.cpp" << std::endl;
#endif // _DEBUG

		std::cout << exception.what() << std::endl;
	}
};

bool Application::Run()
{
	if (this->active)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				this->Stop();
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					this->Stop();
					break;
				
				}
				break;
			}
		}
		

		if (this->state != nullptr && this->state->Update())
		{
			this->window->Update();
		}
		
		
	}
	return this->active;
}

void Application::Stop()
{
	this->active = false;
}

template <class T>
void Application::SetState()
{
	if (this->state != nullptr)
	{
		this->state->Destroy();
	}
	this->state = new T();
	this->state->Init();
}

Application::~Application()
{
	SDL_Quit();
}

