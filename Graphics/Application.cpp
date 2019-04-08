#include <GL/glew.h>
#include "Application.h"
#include "InitialState.h"
#include <SDL2/SDL.h>


//set everything up, SDL, GLEW, and the initialstate
Application::Application()
{
	try
	{
		//try and initialize sdl
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			//otherwise, throw a custom exception with the data from the error
			throw application_exception(SDL_GetError());
		}
		else
		{
			//if everything is OK, create the window and initialize GLEW
			this->window = new Window("Graphics Project", 640, 480);
			if (glewInit() != GLEW_OK)
			{
				std::cout << "Error initializing GLEW!" << std::endl;
			}
			else
			{
				//enable depth testing and lighting to make sure that
				//the closest thing to the camera is drawn first
				glEnable(GL_DEPTH_TEST | GL_LIGHTING);
			}
			
		}
	}
	catch (application_exception& exception)
	{
		//if there was an error, examine it here and display messages to the user.
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

//the master method that creates everything. Captures events and 
//updates the window as necessary.
bool Application::Run()
{
	if (this->active)
	{
		//gets keypresses
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				//stop the app if the X is clicked
				this->Stop();
				break;
			case SDL_KEYDOWN:
				//updated the screen if a key is pressed.
				if (this->state != nullptr)
				{
					this->state->Update();
				}
				switch (event.key.keysym.sym)
				{
					//also stop when user presses escape
				case SDLK_ESCAPE:
					this->Stop();
					break;
				
				}
				break;
			}
		}
		
		//if the state is updated, update the window
		if (this->state != nullptr && this->state->Update())
		{			
			this->window->Update();			
		}
		
		
		
	}
	return this->active;
}


//kills the application 
void Application::Stop()
{
	this->active = false;
}

//Updates the state of the application. 
//there is only currently one state that runs in the application at the moment,
//but it supports any number of states that may draw whatever they want.
void Application::SetState(GameStateBase* state)
{
	if (this->state != nullptr)
	{
		this->state->Destroy();
		delete this->state;
	}
	this->state = state;
	this->state->Init();
}

//destroy the application and restore the memory
Application::~Application()
{
	if (this->state != nullptr)
	{
		this->state->Destroy();
		delete this->state;
	}
	SDL_Quit();
}

