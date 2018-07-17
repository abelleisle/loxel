#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <game_class.hpp>
#include <script/scriptable.hpp>

class Camera : public Scriptable
{
    public:
        glm::vec3 pos;
        glm::vec3 rot;
        glm::vec2 angle;

        bool w_f;
        bool w_b;
        bool w_r;
        bool w_l;

        Camera();

        void update();

        void registerScript();
};

#endif // CAMERA_HPP
