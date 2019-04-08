#include <Windows.h>
#include <GL/glew.h>
#include "TexturedShape.h"
#include <array>

//this class was a failed attempt at creating a textured object 

TexturedShape::TexturedShape(Shader* shader) : Drawable()
{
	//this->bindVAO();
	//this->loadVertices(vData, 48);
	//this->loadElements(eData, 36);
	//this->posAtt = shader->getAttribute("position");
	//this->colAtt = shader->getAttribute("color");
	//this->lightColAtt = shader->getAttribute("lightColor");
	//this->uvAtt = shader->getAttribute("uv");

	//glEnableVertexAttribArray(this->posAtt);
	//glVertexAttribPointer(this->posAtt, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), 0);

	//glEnableVertexAttribArray(this->colAtt);
	//glVertexAttribPointer(this->colAtt, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(3 * sizeof(float)));

	//glEnableVertexAttribArray(this->lightColAtt);
	//glVertexAttribPointer(this->lightColAtt, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(6 * sizeof(float)));

	//glEnableVertexAttribArray(this->uvAtt);
	//glVertexAttribPointer(this->lightColAtt, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(9 * sizeof(float)));

	////this->loadTexture


}

TexturedShape::TexturedShape(Shader* shader, GLfloat vertData[], GLuint edgeData[], size_t sizeV, size_t sizeE) : Drawable()
{
	this->bindVAO();

	this->loadVertices(vertData, sizeV);
	this->loadElements(edgeData, sizeE);
	this->posAtt = shader->getAttribute("position");
	this->colAtt = shader->getAttribute("color");
	this->lightColAtt = shader->getAttribute("lightColor");
	this->uvAtt = shader->getAttribute("uv");

	glEnableVertexAttribArray(this->posAtt);
	glVertexAttribPointer(this->posAtt, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), 0);

	glEnableVertexAttribArray(this->colAtt);
	glVertexAttribPointer(this->colAtt, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(this->lightColAtt);
	glVertexAttribPointer(this->lightColAtt, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (void*)(6 * sizeof(float)));


	glEnableVertexAttribArray(this->uvAtt);
	glVertexAttribPointer(this->lightColAtt, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (void*)(9 * sizeof(float)));

	this->loadTexture("carpet.bmp");

	
	//glBindTexture(GL_TEXTURE_2D, this->textureID);

}


TexturedShape::~TexturedShape()
{

}