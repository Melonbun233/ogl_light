//this file is a camera class that can detect wsad and move accordingly. It also can 
//detect mouse movement and adjust view angle
#include "../include/camera.h"

Camera::Camera(glm::vec3 position ,glm::vec3 front, glm::vec3 up, float yaw, float pitch){
	Position = position;
	Front = front;
	Up = up;
	_yaw = yaw;
	_pitch = pitch;
	_speed = INIT_SPEED;
	_fov = FOV_MAX;
	_mouse_sens = INIT_MOUSE_SENSITIVITY;
	MOUSE_VERTICAL_INVERSE = false;
	MOUSE_HORIZONTAL_INVERSE = false;
	updateCamera();
}

void Camera::processKeypad(MOVEMENT direction, float delta_time) {
	float speed = _speed * delta_time; 
	switch (direction){
		case FORWARD:{
			Position += Front * speed;
			break;
		}
		case BACKWARD:{
			Position -= Front * speed;
			break;
		}
		case LEFT:{
			Position -= glm::normalize(glm::cross(Front, Up)) * speed;
			break;
		}
		case RIGHT:{
			Position += glm::normalize(glm::cross(Front, Up)) * speed;
			break;
		}
		case UP:{
			glm::vec3 right = glm::cross(Front, Up);
			Position += glm::normalize(glm::cross(right, Front)) * speed;
			break;
		}
		case DOWN:{
			glm::vec3 right = glm::cross(Front, Up);
			Position -= glm::normalize(glm::cross(right, Front)) * speed;
		}
	}
}

void Camera::processMouseMovement(float x_offset, float y_offset, GLboolean constrainPitch) {
	x_offset *= _mouse_sens;
	y_offset *= _mouse_sens;

	//update yaw and pitch
	_yaw += MOUSE_HORIZONTAL_INVERSE ? -x_offset : x_offset;
	_pitch += MOUSE_VERTICAL_INVERSE ? -y_offset : y_offset;
	//check whether we constrain pitch value
	if (constrainPitch){
		if(_pitch >= 89.0f)
			_pitch = 89.0f;
		if(_pitch <= -89.0f)
			_pitch = -89.0f;
	}
	//update camera vector
	updateCamera();

}

void Camera::processMouseScroll(double scroll_value) {
	_fov -= scroll_value;

	if (_fov >= FOV_MAX)
		_fov = FOV_MAX;
	if (_fov <= FOV_MIN)
		_fov = FOV_MIN;
}

void Camera::updateCamera() {
	//calculate the new front vector
	glm::vec3 front;
	front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	front.y = sin(glm::radians(_pitch));
	front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	Front = normalize(front);
}

glm::mat4 Camera::getView(){
	return glm::lookAt(Position, Position + Front, Up);
}

float Camera::getFOV(){
	return _fov;
}

void Camera::setSpeed(float speed){
	_speed = speed;
}

void Camera::setMouseSensitivity(float sens){
	_mouse_sens = sens;
}

void Camera::setMouseHorizontalInverse(GLboolean inverse){
	MOUSE_HORIZONTAL_INVERSE = inverse;
}

void Camera::setMouseVerticalInverse(GLboolean inverse){
	MOUSE_VERTICAL_INVERSE = inverse;
}