#include "Camera.h"
#include "../Input/KeyInput.h"
#include "../Input/MousePosInput.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm/gtx/transform.hpp>
#include <iostream>

Camera::Camera() {
	this->_pos = { 45, 185, 531 };
	this->_look = { 51, 0, 525 };
	this->_currMousePos = { 0, 0 };

	init();
}

Camera::Camera(const glm::vec3 initPos)
{
	// Initialize to some position provided in constructor
	this->_pos = initPos;
	this->_look = { _pos.x + 1, _pos.y, _pos.z };
	this->_currMousePos = { 0, 0 };

	// Initialize state stuff
	init();
}

void Camera::init() {
	this->_tSinceLast = glfwGetTime();
	_projMatrix = glm::perspective(45.0f, 1.0f / 1.0f, 0.1f, 2000.0f);
}

glm::vec3 Camera::getPos() {
	return this->_pos;
}

glm::vec2 Camera::getCurrMousePos() {
	return _currMousePos;
}

void Camera::handleMouseMovement(int x, int y) {
	_currMousePos.x = x;
	_currMousePos.y = y;
	if (_shouldMoveCamera) {
		GLfloat xdiff = ((GLfloat)MOUSE_WARP_X - x) / ((GLfloat)_sensitivity*MOUSE_WARP_X); //Using offsets where mouse is warped everytime
		GLfloat ydiff = ((GLfloat)MOUSE_WARP_Y - y) / ((GLfloat)_sensitivity*MOUSE_WARP_Y);

		// Rotate l point----------------
		//Y-axis----------------------
		glm::mat4 camtrans = glm::translate(glm::vec3(-_pos.x, -_pos.y, -_pos.z));
		glm::mat4 camRotY = glm::rotate(xdiff, glm::vec3(0, 1, 0));
		glm::mat4 invcamtrans = glm::translate(glm::vec3(_pos.x, _pos.y, _pos.z));
		glm::mat4 yTot = invcamtrans * camRotY * camtrans;
		_look = glm::vec3(yTot * glm::vec4(_look, 1.0));

		//X-axis (or whatever)-------------
		//needs check for if l is on up (y-axis)
		glm::mat4 camRotX = glm::mat4(1.0f);

		_look = glm::vec3(camtrans * glm::vec4(_look, 1.0));
		glm::vec3 axis = glm::cross(_look, _up);
		camRotX = glm::rotate(ydiff, axis);
		_look = glm::vec3(camRotX * glm::vec4(_look, 1.0));
		glm::vec3 axisAfter = glm::cross(_look, _up);
		if (axisAfter.x < 0.05 && axisAfter.x > -0.05
			&& axisAfter.z < 0.05 && axisAfter.z > -0.05
			&& axisAfter.y < 0.05 && axisAfter.y > -0.05)
		{
			camRotX = glm::rotate(-ydiff, axis);
			_look = glm::vec3(camRotX * glm::vec4(_look, 1.0));
		}
		_look = glm::vec3(invcamtrans * glm::vec4(_look, 1.0));
	}	
	//glfwSetMousePos(MOUSE_WARP_X, MOUSE_WARP_Y);
}

glm::mat4 Camera::getProj() const {
	return _projMatrix;
}

glm::mat4 Camera::getCameraMatrix() const {
	// Glm provides a nice look-at implementation here
	return glm::lookAt(this->_pos, this->_look, this->_up);
}

glm::mat4 Camera::getCombined() const {
	// Return combined proj and cam matrix
	return _projMatrix * getCameraMatrix();
}

void Camera::updateTSinceLast() {
	_tSinceLast = glfwGetTime();
}

void Camera::update()
{
	handleMouseMovement(MousePosInput::getPosition().x, MousePosInput::getPosition().y);
	// I did the maths for this a loooooong 
	// time ago and sadly didn't comment anything.
	// It is what it is, move along.
	GLfloat timeElapsed = abs(glfwGetTime() - _tSinceLast);
	//tSinceLast = (GLfloat)glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	GLfloat speedModifier = 1.0;

	if (KeyInput::isKeyDown(GLFW_KEY_SPACE))
		speedModifier = 3.0;

	GLfloat speed = (speedModifier*timeElapsed)*10.0;
	// Directional vector
	glm::vec3 n = _look - _pos;
	n = glm::normalize(n);
	n = n * speed;

	glm::mat4 camtrans = glm::translate(glm::vec3(-_pos.x, -_pos.y, -_pos.z));
	glm::mat4 invcamtrans = glm::translate(glm::vec3(_pos.x, _pos.y, _pos.z));

	_look = glm::vec3(camtrans * glm::vec4(_look, 1.0f));
	glm::vec3 axis = glm::cross(_look, _up);
	_look = glm::vec3(invcamtrans * glm::vec4(_look, 1.0f));
	axis = glm::normalize(axis);
	axis = axis * speed;

	glm::vec3 tmp, tmp2, tmp3;

	tmp = _pos;
	tmp2 = n;
	tmp3 = axis;

	if (KeyInput::isKeyDown(GLFW_KEY_W))
	{
		_pos = tmp + tmp2;
		_look = _look + n;
	}
	else if (KeyInput::isKeyDown(GLFW_KEY_S))
	{
		_pos = tmp - tmp2;
		_look = _look - n;
	}
	else if (KeyInput::isKeyDown(GLFW_KEY_A))
	{
		_pos = tmp - tmp3;
		_look = _look - axis;
	}
	else if (KeyInput::isKeyDown(GLFW_KEY_D))
	{
		_pos = tmp + tmp3;
		_look = _look + axis;
	}

	printf("We are now at: %f, %f, %f\n", _pos.x, _pos.y, _pos.z);
	//printf("Now looking towards: %f %f %f\n", _look.x, _look.y, _look.z);
	updateTSinceLast();
}