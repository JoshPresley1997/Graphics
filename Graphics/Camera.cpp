#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/transform.hpp>	
#include <glm/gtc/type_ptr.hpp>
#include <Windows.h>
#include <GL/glew.h>
#include "Shader.h"

#include "Camera.h"
//this class does everything for the camera and making sure objects are drawn correctly
Camera::Camera(Shader* shader, float w, float h)
{
	//set the shader for the camera to use.
	this->shader = shader;
	//grab the matrix from the shader
	this->vpUniform = this->shader->getUniformLocation("mvpMatrix");
	//set the projection matrix
	this->projecMatrix = glm::perspective(glm::radians(45.0f), w / h, 1.0f, 1000.0f);
	this->SetTranslation(0, 0, -2);
	this->SetRotation(0, 1, 1, 1);
}

//update the current shader to a new shader program
//thing that this is not working properly.
void Camera::SetShader(Shader* shader)
{
	this->shader;
	this->vpUniform = this->shader->getUniformLocation("mvpMatrix");
		
}

//set the camera's translation to a specified point in space. used to set or reset
void Camera::SetTranslation(float x, float y, float z)
{
	this->translation = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
	this->UpdateViewMatrix();
}
//add the specified values to the camera's translation. Used for movement.
void Camera::Translate(float x, float y, float z)
{
	this->translation = glm::translate(this->translation, glm::vec3(x, y, z));
	this->UpdateViewMatrix();
}
//set the rotation to a specific angle along the specified axis. used to set or reset
void Camera::SetRotation(float rotation, float x, float y, float z) 
{
	this->rotation = glm::rotate(glm::mat4(1.0f),glm::radians(rotation) ,glm::vec3(x, y, z));
	this->UpdateViewMatrix();
}
//rotate the camera the specified rotation along the x y or z axis. used to look around
void Camera::Rotate(float rotation, float x, float y, float z)
{
	this->rotation = glm::rotate(this->rotation, glm::radians(rotation), glm::vec3(x, y, z));
	this->UpdateViewMatrix();
}
//update the camera when it's placement has changed.
void Camera::Update()
{
	glm::mat4 tmp = this->projecMatrix * this->viewMatrix;

	this->shader->setUniformMatrix(this->vpUniform, tmp);

}
//update the viewmatrix by performing the rotation, and then the translation.
void Camera::UpdateViewMatrix()
{
	this->viewMatrix = this->rotation * this->translation;
	
}