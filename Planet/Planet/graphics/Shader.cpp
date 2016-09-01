#include "Shader.h"
#include "../utils/ShaderUtils.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Shader::Shader() {
	id = -1;
}

Shader::Shader(string vertPath, string fragPath) {
	id = ShaderUtils::loadShaders(vertPath.c_str(), fragPath.c_str());
	std::cout << "Loaded shader: " << vertPath << ", " << fragPath << std::endl;
}

Shader::~Shader() {
	glDeleteProgram(id);
}

GLuint Shader::getId() {
	return id;
}

void Shader::comeHere() {
	glUseProgram(id);
}

void Shader::pissOff() {
	glUseProgram(0);
}

void Shader::uploadBool(GLboolean val, string name) {
	GLint loc = glGetUniformLocation(id, name.c_str());
	glUniform1i(loc, val);
}

void Shader::uploadFloat(GLfloat val, string name) {
	GLint loc = glGetUniformLocation(id, name.c_str());
	glUniform1f(loc, val);
}

void Shader::uploadInt(GLint val, string name) {
	GLint loc = glGetUniformLocation(id, name.c_str());
	glUniform1i(loc, val);
}

void Shader::uploadMatrix(mat4& mat, string name) {
	GLint loc = glGetUniformLocation(id, name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, &mat[0][0]);
}

void Shader::uploadTexture(GLint texUnit, string name) {
	GLint loc = glGetUniformLocation(id, name.c_str());
	glUniform1i(loc, texUnit);
}

void Shader::uploadVec(vec2& vec, string name) {
	GLint loc = glGetUniformLocation(id, name.c_str());
	glUniform2fv(loc, 1, value_ptr(vec));
}

void Shader::uploadVec(vec3& vec, string name) {
	GLint loc = glGetUniformLocation(id, name.c_str());
	glUniform3fv(loc, 1, value_ptr(vec));
}

void Shader::uploadVec(vec4& vec, string name) {
	GLint loc = glGetUniformLocation(id, name.c_str());
	glUniform4fv(loc, 1, value_ptr(vec));
}

void Shader::uploadVecArr(vector<vec2>& arr, string name) {
	GLint loc = glGetUniformLocation(id, name.c_str());
	GLint size = arr.size();
	glUniform3fv(loc, size, &arr[0].x);
}