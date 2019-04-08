#pragma once

#include "Application.h"
#include "Shape.h"
#include "TexturedShape.h"
#include "RoomCube.h"
#include "Shader.h"
#include "Camera.h"


class InitialState :
	public GameState
{
public:
	InitialState(Application* app);
	bool Init();
	bool Update();
	bool Destroy();	
	~InitialState();
private:
	Shader* shader;
	Shader* textureShader;	
	RoomCube* room;
	Camera* camera;
	glm::vec3 camRotation;
	glm::vec3 camVelocity;
	void Move();
	void CreateShapes();
};

