#include "camera.h"

Camera::Camera(glm::vec3 cameraPosition)
{
	this->cameraPosition = cameraPosition;
	this->cameraViewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->cameraRight = glm::cross(cameraViewDirection, cameraUp);
	this->rotationOx = 0.0f;
	this->rotationOy = -90.0f;
	this->speedMultiplier = 2.0f;
}

Camera::Camera()
{
	this ->cameraPosition = glm::vec3(20.0f, 10.0f, 20.0f);
	this ->cameraViewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	this ->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->cameraRight = glm::cross(cameraViewDirection, cameraUp);
	this->rotationOx = 0.0f;
	this->rotationOy = -90.0f;
	this->speedMultiplier = 2.0f;
}

Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraViewDirection, glm::vec3 cameraUp)
{
	this->cameraPosition = cameraPosition;
	this->cameraViewDirection = cameraViewDirection;
	this->cameraUp = cameraUp;
	this->cameraRight = glm::cross(cameraViewDirection, cameraUp);
	this->speedMultiplier = 2.0f;
}

Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraViewDirection, glm::vec3 cameraUp, float speedMultiplier)
{
	this->cameraPosition = cameraPosition;
	this->cameraViewDirection = cameraViewDirection;
	this->cameraUp = cameraUp;
	this->cameraRight = glm::cross(cameraViewDirection, cameraUp);
	this->speedMultiplier = speedMultiplier;
}

Camera::~Camera()
{
}

void Camera::keyboardMoveFront(float cameraSpeed) {
	cameraPosition += glm::vec3(1.0f, 0.0f, 1.0f) * cameraViewDirection * cameraSpeed * speedMultiplier;
}

void Camera::keyboardMoveBack(float cameraSpeed) {
	cameraPosition -= glm::vec3(1.0f, 0.0f, 1.0f) * cameraViewDirection * cameraSpeed * speedMultiplier;
}

// subtract with cross product between viewing direction & camera's up orientation
void Camera::keyboardMoveLeft(float cameraSpeed) {
	cameraPosition -= glm::cross(cameraViewDirection, cameraUp) * cameraSpeed * speedMultiplier;
}

// add with cross product between viewing direction & camera's up orientation
void Camera::keyboardMoveRight(float cameraSpeed) {
	cameraPosition += glm::cross(cameraViewDirection, cameraUp) * cameraSpeed * speedMultiplier;
}

// move Up for positive value, Down for negative value
void Camera::verticalMovement(float cameraSpeed) {
	cameraPosition += glm::vec3(0.0f, 1.0f, 0.0f) * cameraSpeed * speedMultiplier;
}

/*
// rise strictly on y axis
void Camera::keyboardMoveUp(float cameraSpeed) {
	cameraPosition += glm::vec3(0.0f, 1.0f, 0.0f) * cameraSpeed * speedMultiplier;
}

// fall strictly on y axis
void Camera::keyboardMoveDown(float cameraSpeed) {
	cameraPosition -= glm::vec3(0.0f, 1.0f, 0.0f) * cameraSpeed * speedMultiplier;
}
*/


void Camera::rotateOx(float angle, glm::vec3 pivot)
{	
	// Translate camera position relative to the pivot
	glm::vec3 relativePosition = cameraPosition - pivot;

	// Rotate the relative position around the pivot using the rotation matrix
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, cameraRight);
	relativePosition = glm::vec3(rotationMatrix * glm::vec4(relativePosition, 1.0f));

	// update camera position with new relative position
	cameraPosition = relativePosition + pivot;

	cameraViewDirection = glm::normalize(glm::vec3((glm::rotate(glm::mat4(1.0f), angle, cameraRight) * glm::vec4(cameraViewDirection, 1))));
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraViewDirection));
	cameraRight = glm::cross(cameraViewDirection, cameraUp);
}

void Camera::rotateOy(float angle, glm::vec3 pivot) {

	// Translate camera position relative to the pivot
	glm::vec3 relativePosition = cameraPosition - pivot;

	// Rotate the relative position around the pivot using the rotation matrix
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
	relativePosition = glm::vec3(rotationMatrix * glm::vec4(relativePosition, 1.0f));

	// update camera position with new relative position
	cameraPosition = relativePosition + pivot;

	// Rotate the camera's orientation vectors (cameraViewDirection, cameraUp, cameraRight)
	cameraViewDirection = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(cameraViewDirection, 0.0f)));
	cameraUp = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(cameraUp, 0.0f)));
	cameraRight = glm::normalize(glm::cross(cameraViewDirection, cameraUp));
}





glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(cameraPosition, cameraPosition + cameraViewDirection, cameraUp);
}

glm::vec3 Camera::getCameraPosition()
{
	return cameraPosition;
}

glm::vec3 Camera::getCameraViewDirection()
{
	return cameraViewDirection;
}

glm::vec3 Camera::getCameraUp()
{
	return cameraUp;
}

glm::vec3 Camera::getCameraRight()
{
	return cameraRight;
}




void Camera::setCameraPosition(glm::vec3 vec)
{
	//return cameraPosition;
	this->cameraPosition = vec;
}

void Camera::setCameraViewDirection(glm::vec3 vec)
{
	//return cameraViewDirection;
	this->cameraViewDirection = vec;
}

 void Camera::setCameraUp(glm::vec3 vec)
{
	//return cameraUp;
	 this->cameraUp = vec;
}

void Camera::setCameraRight(glm::vec3 vec)
{
	//return cameraRight;
	this->cameraRight = vec;
}



