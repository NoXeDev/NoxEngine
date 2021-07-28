#include "ShaderProgram.h"
#include "../common/const.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <string>
#include "../core/errorHandler.h"

std::string basePath = "./res/glsl/";

ShaderProgram::ShaderProgram(std::string shaderName)
{
	ostringstream vertex;
	ostringstream fragment;
	vertex << basePath << shaderName << ".vshad.glsl";
	fragment << basePath << shaderName << ".fshad.glsl";

	this->vertexShaderID = this->loadShader(vertex.str().c_str(), GL_VERTEX_SHADER);
	this->fragmentShaderID = this->loadShader(fragment.str().c_str(), GL_FRAGMENT_SHADER);
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
		std::ostringstream ss;
		ss << "Impossible to open " << file << ".";
		errorHandler::fatal(ss.str());
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
		std::ostringstream ss;
		ss << "Compiling shader error " << file << " : " << &ShaderErrorMessage[0];
		errorHandler::fatal(ss.str());
	}

	return shaderID;
}
