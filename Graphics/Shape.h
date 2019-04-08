#pragma once
#include "Drawable.h"
#include "Shader.h"

class Shape : public Drawable
{
public:
	Shape(Shader* shader);
	Shape(Shader* shader, GLfloat vData[], GLuint eData[], size_t sizeV, size_t sizeE);
	~Shape();
private:
	GLint posAtt, colAtt, lightColAtt; //position and color, and lightcolor attributes attributes
	
};