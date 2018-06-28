#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

class Camera
{
    public:
        glm::vec3 pos;
        glm::vec3 angle;

        Camera();
};

#endif // CAMERA_HPP
