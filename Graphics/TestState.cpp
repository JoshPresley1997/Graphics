#include "TestState.h"



TestState::TestState()
{
}

bool TestState::Init()
{
	glClearColor(1, 0, 0, 1);
	return true;
}

bool TestState::Update()
{
	glClear(GL_COLOR_BUFFER_BIT);
	return true;
}

bool TestState::Destroy()
{
	return true;
}

TestState::~TestState()
{
}
