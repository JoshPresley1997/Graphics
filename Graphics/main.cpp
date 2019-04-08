#include "Application.h"
#include "InitialState.h"

int main(int argc, char*argv[])
{
	//Create an instance of the application and set it to the initial state
	Application* app = new Application();
	SetState<InitialState>(app);
	//once the application is created, run it
	while (app->Run())
	{

	}
	delete app;
	return 0;
}