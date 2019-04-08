#pragma once
#include <vector>
#include <iterator>
#include <SDL2/SDL.h>


class Drawable
{
public:
	Drawable();
	bool Draw();
	~Drawable();
private:
	GLuint vao, lightvao, vbo, ebo; //vertex array object, vertex buffer object, element buffer object
	
	SDL_Surface* texture;
	std::vector<GLuint> elements;
	std::vector<float> vertices;
protected:
	GLuint textureID;

	void loadVertices(float data[], size_t size);
	void loadVertices(std::vector<float> data);

	void loadElements(GLuint data[], size_t size);
	void loadElements(std::vector<GLuint> data);

	void loadTexture(std::string fileName);


	void bindVAO();
	void unbindVAO();

	void bindLightVAO();
	void unbindLightVAO();
};