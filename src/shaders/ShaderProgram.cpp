#include "../common/const.h"
#include "ShaderProgram.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <string>

std::string basePath = "./res/glsl/";

ShaderProgram::ShaderProgram(std::string shaderName)
{
	std::string vertex = basePath + shaderName + ".vshad.glsl";
	std::string fragment = basePath + shaderName + ".fshad.glsl";
	std::vector<char> vertexChar(vertex.begin(), vertex.end());
	std::vector<char> fragmentChar(fragment.begin(), fragment.end());

	vertexChar.push_back('\0');
	fragmentChar.push_back('\0');

	this->vertexShaderID = this->loadShader(&vertexChar[0], GL_VERTEX_SHADER);
	this->fragmentShaderID = this->loadShader(&fragmentChar[0], GL_FRAGMENT_SHADER);
}

void ShaderProgram::create()
{
	this->programID = glCreateProgram();
	glAttachShader(this->programID, this->vertexShaderID);
	glAttachShader(this->programID, this->fragmentShaderID);
	this->bindAttributes();
	glLinkProgram(this->programID);
	glValidateProgram(this->programID);
	this->getAllUniformLocations();
}

int ShaderProgram::getUniformLocation(const char* uniformName)
{
	return glGetUniformLocation(this->programID, uniformName);
}

void ShaderProgram::start()
{
	glUseProgram(this->programID);
}

void ShaderProgram::stop()
{
	glUseProgram(0);
}

void ShaderProgram::cleanUp()
{
	this->stop();
	glDetachShader(this->programID, this->vertexShaderID);
	glDetachShader(this->programID, this->fragmentShaderID);
	glDeleteShader(this->vertexShaderID);
	glDeleteShader(this->fragmentShaderID);
	glDeleteShader(this->programID);
}

void ShaderProgram::bindAttribute(GLuint attribute, const GLchar* variableName)
{
	glBindAttribLocation(this->programID, attribute, variableName);
}

void ShaderProgram::loadFloat(GLint location, GLfloat value)
{
	glUniform1f(location, value);
}

void ShaderProgram::loadInt(GLint location, GLfloat value)
{
	glUniform1i(location, value);
}

void ShaderProgram::loadVector(GLint location, glm::vec3 vector)
{
	glUniform3f(location, vector.x, vector.y, vector.z);
}

void ShaderProgram::loadBoolean(GLint location, bool value)
{
	float toLoad = 0;
	if (value) {
		toLoad = 1;
	}
	glUniform1f(location, value);
}

void ShaderProgram::loadMatrix(GLint location, glm::mat4 matrix)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

GLuint ShaderProgram::loadShader(const char* file, GLenum type)
{
	GLuint shaderID = glCreateShader(type);
	std::string ShaderCode;
	std::ifstream ShaderStream(file, std::ios::in);
	if (ShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << ShaderStream.rdbuf();
		ShaderCode = sstr.str();
		ShaderStream.close();
	}
	else {
		printf("Impossible to open %s.\n", file);
		exit(NOXENGINE_SHADERS_MISSING);
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	char const* ShaderSourcePointer = ShaderCode.c_str();
	glShaderSource(shaderID, 1, &ShaderSourcePointer, NULL);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(shaderID, InfoLogLength, NULL, &ShaderErrorMessage[0]);
		printf("Compiling shader error %s : %s\n", file, &ShaderErrorMessage[0]);
		exit(NOXENGINE_SHADERS_COMPILATION_ERROR);
	}

	return shaderID;
}
