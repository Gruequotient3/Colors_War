#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

class Camera{
    private:
        glm::mat4 view;
        glm::mat4 projection;

    public:
        float ratio;

        float yaw;
        float pitch;
        float fov;

        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;

        Camera(float ratio);

        void Update();

        float *GetViewMatrice();
        float *GetProjectionMatrice();
};

#endif
