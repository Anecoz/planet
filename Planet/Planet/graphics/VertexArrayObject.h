#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <vector>

typedef std::vector<glm::vec3> VertVec;
typedef std::vector<unsigned> IndVec;

class VertexArrayObject
{
public:
	VertexArrayObject(VertVec& verts, IndVec& indices);
	~VertexArrayObject();

	void bind();
	void unbind();
	void draw();

private:
	GLuint vao;
	GLuint vbo, ibo;

	GLuint count;
};

