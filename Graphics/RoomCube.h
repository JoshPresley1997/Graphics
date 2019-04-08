#pragma once
#include "Drawable.h"
#include "Shader.h"

class RoomCube : public Drawable
{
public:
	RoomCube(Shader* shader);
	~RoomCube();
private:
	GLint posAtt, colAtt, lightColAtt; //position and color attributes
};
