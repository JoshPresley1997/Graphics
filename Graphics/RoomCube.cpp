#include <Windows.h>
#include <GL/glew.h>
#include "RoomCube.h"

//vertices of the "room" that you appear in on program start.
GLfloat roomVertices[] = {
	//positions					//colors					//ambient light
	-100.5f, 10.5f, -100.0f,	1.0f, 0.3f, 1.0f,			1.0f, 1.0f, 1.0f,	//top-left - front 0 
	100.5f, 10.5f, -100.0f,		1.0f, 0.3f, 1.0f,			1.0f, 1.0f, 1.0f,//top-right - front 1
	100.5f, -1.5f, -100.0f,		0.0f, 0.1f, 0.1f,			1.0f, 1.0f, 1.0f,//bottom-right - front 2
	-100.5f, -1.5f, -100.0f,	0.0f, 0.1f, 0.1f,			1.0f, 1.0f, 1.0f,//bottom-left - front 3
	
	-100.5f, 10.5f, 100.0f,		1.0f, 1.0f, 0.0f,			1.0f, 1.0f, 1.0f,//top-left - back 4 
	100.5f, 10.5f,	100.0f,		1.0f, 1.0f, 0.0f,			1.0f, 1.0f, 1.0f,//top-right - back 5
	100.5f, -1.5f, 100.0f,		0.0f, 0.1f, 0.1f,			1.0f, 1.0f, 1.0f,//bottom-right -  back 6 
	-100.5f, -1.5f, 100.0f,		0.0f, 0.0f, 0.1f,			1.0f, 1.0f, 1.0f,//bottom-left - back 7 
	
};
//edges of the room
GLuint roomElements[] = {
	0, 1, 2,
	2, 3, 0, //front wall

	4, 5, 6,
	6, 7, 4, //back wall

	4, 0, 3,
	3, 7, 4, //left wall

	1, 5, 6,
	6, 2, 1, // right wall

	2, 6, 7,
	7, 3, 2,  // floor 

	0, 4, 5,
	5, 1, 0 //ceiling
};
//create the room in the same way all other drawables are created.
RoomCube::RoomCube(Shader* shader) : Drawable()
{
	this->bindVAO();
	this->loadVertices(roomVertices, 72);
	this->loadElements(roomElements, 36);
	this->posAtt = shader->getAttribute("position");
	this->colAtt = shader->getAttribute("color");
	this->lightColAtt = shader->getAttribute("lightColor");

	glEnableVertexAttribArray(this->posAtt);
	glVertexAttribPointer(this->posAtt, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), 0);

	glEnableVertexAttribArray(this->colAtt);
	glVertexAttribPointer(this->colAtt, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(this->lightColAtt);
	glVertexAttribPointer(this->lightColAtt, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(6 * sizeof(float)));
}

RoomCube::~RoomCube()
{

}