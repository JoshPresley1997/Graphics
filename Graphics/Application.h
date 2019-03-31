#pragma once
#include "Window.h"
#include "GameState.h"


class application_exception : public std::runtime_error
{
public :
	application_exception(const std::string& error) : std::runtime_error(error) 
	{

	};
		

};


class Application
{
	Application();
	~Application();
	static Application* applicationInstance;

public:
	static Application* Instance();	
	bool Run();
	void Stop();
	
	template <class T>
	void SetState();
private:
	bool active;
	Window* window;
	GameState* state = nullptr;
};