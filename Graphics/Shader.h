#pragma once
#include<string>
#include<sstream>	
#include<iostream>
#include<fstream>
#include<glm/glm.hpp>
class Shader
{
public:
	Shader(std::string vertexFileName, std::string fragmentFileName);
	bool Use();
	GLint getAttribute(std::string name);
	GLint getUniformLocation(std::string name);
	void setUniformMatrix(GLint location, glm::mat4 matrix);
private:
	std::ifstream vertFile, fragFile;
	std::string vertexFileName, fragmentFileName;
	std::stringstream vertexSourceStream, fragmentSourceStream;
	std::string vertexSource, fragmentSource;
	GLuint vertexShader, fragmentShader, shaderProgram;
	bool ready;
	int Load();
	int Compile();
	int Link();
};