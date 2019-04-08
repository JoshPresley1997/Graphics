#include "TestState2.h"
#include "InitialState.h"



TestState2::TestState2(Application* app) : GameState(app)
{
}
bool TestState2::Init()
{
	glClearColor(1, 0, 0, 1);	
	return true;
}

bool TestState2::Update()
{
	glClear(GL_COLOR_BUFFER_BIT);

	const uint8_t* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_LEFT])
	{
		SetState<InitialState>(this->app);
	}
	return true;

}

bool TestState2::Destroy()
{
	return true;
}


TestState2::~TestState2()
{
}
