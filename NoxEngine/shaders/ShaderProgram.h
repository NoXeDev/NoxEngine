#pragma once
#include <glew.h>
#include <glm.hpp>

class ShaderProgram
{
public:
	ShaderProgram(const char* vertexFile, const char* fragmentFile);
	void create();
	void start();
	void stop();
	void cleanUp();
private:
	GLuint programID;
	GLuint vertexShaderID;
	GLuint fragmentShaderID;
	static GLuint loadShader(const char* file, GLenum type);
protected:
	virtual void bindAttributes() = 0;
	void bindAttribute(GLuint attribute, const GLchar* variableName);
	int getUniformLocation(const char* uniformName);
	virtual void getAllUniformLocations() = 0;
	void loadFloat(GLint location, GLfloat value);
	void loadVector(GLint location, glm::vec3 vector);
	void loadBoolean(GLint location, bool value);
	void loadMatrix(GLint location, glm::mat4 matrix);
};

