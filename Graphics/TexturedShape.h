#pragma once
#include "Drawable.h"
#include "Shader.h"

class TexturedShape : public Drawable
{
public:
	TexturedShape(Shader* shader);
	TexturedShape(Shader* shader, GLfloat vData[], GLuint eData[], size_t sizeV, size_t sizeE);
	~TexturedShape();
private:
	GLint posAtt, colAtt, lightColAtt, uvAtt; //position and color, and lightcolor attributes attributes

};