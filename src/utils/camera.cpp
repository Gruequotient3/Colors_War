#ifndef CAMERA_CPP
#define CAMERA_CPP

#include "camera.hpp"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(float ratio){
    this->ratio = ratio;
    yaw = -90.0;
    pitch = 0.0f;
    fov = 90.0f;

    position = glm::vec3{0.0f, 0.0f, 5.0f};
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);

    Update();
}

void Camera::Update(){
    view = glm::lookAt(position, position + front, up);
    projection = glm::perspective(glm::radians(fov), ratio, 0.01f, 100.0f);
}

float *Camera::GetViewMatrice(){
    return glm::value_ptr(view);
}

float *Camera::GetProjectionMatrice(){
    return glm::value_ptr(projection);
}



#endif
