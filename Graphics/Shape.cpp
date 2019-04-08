#include <Windows.h>
#include <GL/glew.h>
#include "Shape.h"
#include <array>

//these are the vertices and their colours. Can be passed in with the other constructor. these are
//test values.
GLfloat vData[] = {
	-0.5f, 0.5f, 0.0f, 1.0f, 0.8f, 1.0f,//top-left-front 0 
	0.5f, 0.5f, 0.0f, 1.0f, 0.8f, 1.0f,//top-right-front 1
	0.5f, -0.5f, 0.0f, 1.0f, 0.8f, 1.0f,//bottom-right-front 2
	-0.5f, -0.5f, 0.0f, 1.0f, 0.8f, 1.0f,//bottom-left-front 3

	-0.5f, 0.5f, -0.5f, 1.0f, 0.8f, 1.0f,//top-left-back 4
	0.5f, 0.5f, -0.5f, 1.0f, 0.8f, 1.0f,//top-right-back 5 
	0.5f, -0.5f, -0.5f, 1.0f, 0.8f, 1.0f,//bottom-right-back 6
	-0.5f, -0.5f, -0.5f, 1.0f, 0.8f, 1.0f//bottom-left-back 7
};


//these are the triangles that get drawn. This combonation will draw a cube
GLuint eData[] = {
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



//an old version of the constructor when the Shape drew only 2d objects.
Shape::Shape(Shader* shader) : Drawable()
{
	this->bindVAO();
	this->loadVertices(vData, 48);
	this->loadElements(eData, 36);
	//grab the positions of the parameters in the shader file
	this->posAtt = shader->getAttribute("position");
	this->colAtt = shader->getAttribute("color");
	this->lightColAtt = shader->getAttribute("lightColor");
	
	//essentially pass the values in the vertex array to the shader with the 6 calls below
	glEnableVertexAttribArray(this->posAtt);
	glVertexAttribPointer(this->posAtt, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), 0);

	glEnableVertexAttribArray(this->colAtt);
	glVertexAttribPointer(this->colAtt, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(3*sizeof(float)));

	glEnableVertexAttribArray(this->lightColAtt);
	glVertexAttribPointer(this->lightColAtt, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(6 * sizeof(float)));
}

//new version of the constructor which allows you to pass vertex and edge
//data to create custom 3d shapes.
Shape::Shape(Shader* shader, GLfloat vertData[], GLuint edgeData[], size_t sizeV, size_t sizeE) : Drawable()
{
	this->bindVAO();
	//get the attribute locations 
	this->loadVertices(vertData, sizeV);
	this->loadElements(edgeData, sizeE);
	this->posAtt = shader->getAttribute("position");
	this->colAtt = shader->getAttribute("color");
	this->lightColAtt = shader->getAttribute("lightColor");

	//essentially pass the values in the vertex array to the shader with the 6 calls below
	glEnableVertexAttribArray(this->posAtt);
	glVertexAttribPointer(this->posAtt, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), 0);

	glEnableVertexAttribArray(this->colAtt);
	glVertexAttribPointer(this->colAtt, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(this->lightColAtt);
	glVertexAttribPointer(this->lightColAtt, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(6 * sizeof(float)));


}


Shape::~Shape()
{

}


//this was an attempt to add in more complex lighting by calculating normals 
//and then calculating color based on that.
//in the end had some trouble deciding when to pass certain values and 
//went with simple ambient lighting.
//GLfloat* Cube::calculateNormals(GLfloat vData[])
//{
//	glm::vec3 normal1, normal2, normal3, normal4, normal5, normal6;
//	glm::vec3 p1, p2, p3; //points that will be used to calculate the normals of the surfaces.
//	glm::vec3 v1, v2;
//	//first, get two vectors for the front face and compute the normal.
//	p1 = glm::vec3(vData[0], vData[1], vData[2]);
//	p2 = glm::vec3(vData[3], vData[4], vData[5]);
//	v1 = glm::vec3(p2 - p1);
//
//	p3 = glm::vec3(vData[6], vData[7], vData[8]);
//	v2 = glm::vec3(p3 - p1);
//	normal1 = glm::cross(v1, v2);
//	normal2 = glm::vec3(-normal1); //back normal is opposite front normal
//	
//	//left/right side
//	p1 = glm::vec3(vData[9], vData[10], vData[11]);
//	p2 = glm::vec3(vData[21], vData[22], vData[23]);
//	v1 = glm::vec3(p2 - p1);
//
//	p3 = glm::vec3(vData[0], vData[1], vData[2]);
//	v2 = glm::vec3(p3 - p1);
//
//	normal3 = glm::cross(v1, v2);
//	normal4 = glm::vec3(-normal3); //right normal is opposite left normal
//
//
//	//top/bottom
//	p1 = glm::vec3(vData[0], vData[1], vData[2]);
//	p2 = glm::vec3(vData[3], vData[4], vData[5]);
//	v1 = glm::vec3(p2 - p1);
//
//	p3 = glm::vec3(vData[12], vData[11], vData[13]);
//	v2 = glm::vec3(p3 - p1);
//
//	normal5 = glm::cross(v1, v2);
//	normal6 = glm::vec3(-normal5); //bottom normal is opposite top normal
//
//	GLfloat Normals[] = 
//	{
//		normal1.x, normal1.y, normal1.z,
//		normal2.x, normal2.y, normal2.z, 
//		normal3.x, normal3.y, normal3.z, 
//		normal4.x, normal4.y, normal4.z, 
//		normal5.x, normal5.y, normal5.z, 
//		normal6.x, normal6.y, normal6.z
//
//	};
//
//	return Normals;
//}