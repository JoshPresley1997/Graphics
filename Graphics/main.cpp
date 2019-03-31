#include "Application.h"
#include "TestState.h"


int main(int argc, char*argv[])
{
	Application::Instance()->SetState<TestState>();
	while (Application::Instance()->Run())
	{

	}

	return 0;
}