#pragma once
#include "GameState.h"
#include <Windows.h>	
#include <GL/GL.h>
class TestState :
	public GameState
{
public:
	TestState();
	bool Init();
	bool Update();
	bool Destroy();
	
	~TestState();
};

