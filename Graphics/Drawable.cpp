#include <Windows.h>
#include <GL/glew.h>
#include "Drawable.h"

//this is a superclass for anything that will be drawn to the screen.
Drawable::Drawable()
{	
	//initialise the vertex array object, the vertex buffer object, and the element buffer object
	this->vao = 0;
	this->vbo = 0;
	this->ebo = 0;
	this->textureID = 0;
	glGenVertexArrays(1, &this->vao);

}
//load in the vertices for the shader program
void Drawable::loadVertices(float data[], size_t size)
{
	this->vertices.insert(this->vertices.end(), data, data + size);
	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->vertices.size(), this->vertices.data(), GL_STATIC_DRAW);

}
//load in the vertices with a vector instead of an array of data
void Drawable::loadVertices(std::vector<float> data)
{
	this->vertices.insert(this->vertices.end(), data.begin(), data.end());
	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->vertices.size(), this->vertices.data(), GL_STATIC_DRAW);

}

//initialise the array of edges for the shader program
void Drawable::loadElements(GLuint data[], size_t size)
{
	this->elements.insert(this->elements.end(), data, data + size);
	glGenBuffers(1, &this->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * this->elements.size(), this->elements.data(), GL_STATIC_DRAW);

}

//initialise the array of edges for the shader program using a vector instead of a list of elements.
void Drawable::loadElements(std::vector<GLuint> data)
{
	this->elements.insert(this->elements.end(), data.begin(), data.end());
	glGenBuffers(1, &this->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * this->elements.size(), this->elements.data(), GL_STATIC_DRAW);
}

//load a 2d texture for the shader program. 
//I think there is something in here that I did wrong.
void Drawable::loadTexture(std::string fileName)
{
	this->texture = SDL_LoadBMP(fileName.c_str());
	if (this->texture)
	{
		glGenTextures(1, &this->textureID);
		if (this->textureID)
		{
			glBindTexture(GL_TEXTURE_2D, this->textureID);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->texture->w, this->texture->h, 0, GL_BGR, GL_UNSIGNED_BYTE, this->texture->pixels);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}

//bind the vertex array object
void Drawable::bindVAO()
{
	glBindVertexArray(this->vao);
}

//unbind the vertex array object
void Drawable::unbindVAO()
{
	glBindVertexArray(0);
}
//bind the vertex array object for the lighting. ended up not being needed
void Drawable::bindLightVAO()
{
	glBindVertexArray(this->lightvao);
}
//unbind the vertex array object for the lighting. ended up not being needed
void Drawable::unbindLightVAO()
{
	glBindVertexArray(0);
}

//actually draw the elements from the vao and vbo
bool Drawable::Draw()
{

	if (!this->vao || !this->vbo || !this->ebo)
	{
		return false;
	}

	this->bindVAO();
	glBindTexture(GL_TEXTURE_2D, this->textureID);
	glDrawElements(GL_TRIANGLES, this->elements.size(), GL_UNSIGNED_INT, 0);	
	glBindTexture(GL_TEXTURE_2D, 0);
	
	return true;

}
//clear all the buffers.
Drawable::~Drawable()
{
	if (this->ebo)
	{
		glDeleteBuffers(1, &this->ebo);
	}
	if (this->vbo)
	{
		glDeleteBuffers(1, &this->vbo);
	}
	if (this->vao)
	{
		glDeleteVertexArrays(1, &this->vao);
	}
	if (this->textureID)
	{
		SDL_FreeSurface(this->texture);
	}
	
}