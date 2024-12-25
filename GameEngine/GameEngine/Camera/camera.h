#pragma once

#include <glm.hpp>
#include <gtx\transform.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include "..\Graphics\window.h"

class Camera
{
	private:
		glm::vec3 cameraPosition;
		glm::vec3 cameraViewDirection;
		glm::vec3 cameraUp;
		glm::vec3 cameraRight;
		float speedMultiplier;

		//rotation - to be removed
		float rotationOx;
		float rotationOy;

	public:
		Camera();
		Camera(glm::vec3 cameraPosition);
		Camera(glm::vec3 cameraPosition, glm::vec3 cameraViewDirection, glm::vec3 cameraUp);
		Camera(glm::vec3 cameraPosition, glm::vec3 cameraViewDirection, glm::vec3 cameraUp, float speedMultiplier);
		~Camera();

		glm::mat4 getViewMatrix();
		glm::vec3 getCameraPosition();
		glm::vec3 getCameraViewDirection();
		glm::vec3 getCameraUp();
		glm::vec3 getCameraRight();

		void setCameraPosition(glm::vec3 vec);
		void setCameraViewDirection(glm::vec3 vec);
		void setCameraUp(glm::vec3 vec);
		void setCameraRight(glm::vec3 vec);

		void keyboardMoveFront(float cameraSpeed);
		void keyboardMoveBack(float cameraSpeed);
		void keyboardMoveLeft(float cameraSpeed);
		void keyboardMoveRight(float cameraSpeed);
		//void keyboardMoveUp(float cameraSpeed);
		//void keyboardMoveDown(float cameraSpeed);
		void verticalMovement(float cameraSpeed);

		void rotateOx(float angle, glm::vec3 pivot);
		void rotateOy(float angle, glm::vec3 pivot);
};

