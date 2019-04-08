#include <Windows.h>	
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"


using namespace std;
//creates a shader program to correctly color the vertices and surfaces in the space
Shader::Shader(string vertexFileName, string fragmentFileName)
{

	
	this->ready = false;
	this->vertexFileName = vertexFileName;
	this->fragmentFileName = fragmentFileName;	

	//in order for the shader to be successfully created, we must load the sources,
	//compile them, and link the two programs together
	if (this->Load() < 1) 
	{
		cout << "Error loading shader sources!" << endl;
		return;
	}
	if (this->Compile() < 1)
	{
		cout << "Error compiling shader sources!" << endl;
		return;

	}
	if (this->Link() < 1)
	{
		cout << "Error linking shader program!" << endl;
		return;
	}

	this->ready = true;
}
//tells OpenGL to use the current program
bool Shader::Use()
{
	if (this->ready)
	{
		glUseProgram(this->shaderProgram);
	}
	return this->ready;
}
//gets an attribute location from the shader program so that data can be assigned to it.
GLint Shader::getAttribute(string name)
{
	return glGetAttribLocation(this->shaderProgram, name.c_str());
}
//gets the location of a uniform from the shader program so that data can be assigned to it
GLint Shader::getUniformLocation(string name)
{
	return glGetUniformLocation(this->shaderProgram, name.c_str());
}
//updates the value of a 4d uniform matrix
void Shader::setUniformMatrix(GLint location, glm::mat4 matrix)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}
//load the two files in
int Shader::Load()
{
	//first, read in the vertex file.
	this->vertFile.open(this->vertexFileName, ios::in);
	if (!vertFile)
	{
		return -1;
	}
	this->vertexSourceStream << vertFile.rdbuf();
	
	//next, read in the fragment file
	this->fragFile.open(this->fragmentFileName, ios::in);
	if (!fragFile)
	{
		return -2;
	}
	this->fragmentSourceStream << fragFile.rdbuf();
	//update the values in the class
	this->vertexSource = this->vertexSourceStream.str();
	this->fragmentSource = this->fragmentSourceStream.str();
	//success
	return 1;
}

int Shader::Compile()
{
	//compile the vertex shader
	//convert to a c string for compatability with c
	const char* tempSource = this->vertexSource.c_str();
	this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(this->vertexShader, 1, &tempSource, 0);
	glCompileShader(this->vertexShader);
	GLint compiled;
	glGetShaderiv(this->vertexShader, GL_COMPILE_STATUS, &compiled);

	//if there is an error compiling, log the errors to standard output
	if (compiled == false)
	{
		unsigned int maxLength;
		glGetShaderiv(this->vertexShader, GL_INFO_LOG_LENGTH, (GLint*)&maxLength);
		char* vertexCompileLog = (char*)malloc(maxLength);
		glGetShaderInfoLog(this->vertexShader, maxLength, (GLsizei*)&maxLength, vertexCompileLog);
		cout << "Vertex shader error: " << endl << vertexCompileLog << endl << endl;
		free(vertexCompileLog);
		return -1;
	}

	//now the fragment shader
	tempSource = this->fragmentSource.c_str();
	this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(this->fragmentShader, 1, &tempSource, 0);
	glCompileShader(this->fragmentShader);
	glGetShaderiv(this->fragmentShader, GL_COMPILE_STATUS, &compiled);

	//if there is an error compiling, log the errors to standard output
	if (compiled == false)
	{
		unsigned int maxLength;
		glGetShaderiv(this->fragmentShader, GL_INFO_LOG_LENGTH, (GLint*)&maxLength);
		char* fragmentCompileLog = (char*)malloc(maxLength);
		glGetShaderInfoLog(this->fragmentShader, maxLength, (GLsizei*)&maxLength, fragmentCompileLog);
		cout << "Fragment shader error: " << endl << fragmentCompileLog << endl << endl;
		free(fragmentCompileLog);
		return -2;
	}

	return 1; //success

}
//the two programs must be linked so that the vertex file can output values to 
//the fragment file
int Shader::Link()
{
	//create the program in openGL
	this->shaderProgram = glCreateProgram();
	//attach the two shader programs
	glAttachShader(this->shaderProgram, this->vertexShader);
	glAttachShader(this->shaderProgram, this->fragmentShader);
	//tell opengl to link them
	glLinkProgram(this->shaderProgram);

	GLint linked;
	//check if the link was successfull
	glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &linked);
	if (linked == false)
	{
		//output some info on fail
		unsigned int maxLength;
		glGetProgramiv(this->shaderProgram, GL_INFO_LOG_LENGTH, (GLint*)&maxLength);
		char* programLinkLog = (char*)malloc(maxLength);
		glGetProgramInfoLog(this->shaderProgram, maxLength, (GLsizei*)&maxLength, programLinkLog);
		cout << "Program link error: " << endl << programLinkLog << endl << endl;
		free(programLinkLog); //make sure to free this memory.
		return -1;
	}

	return 1; //success
}