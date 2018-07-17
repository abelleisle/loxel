#include <client/camera.hpp>
#include <LuaBridge/LuaBridge.h>
#include <iostream>

void Camera::registerScript()
{
    luabridge::getGlobalNamespace(script->getState())
        .beginClass<Camera>("Camera")
        .addConstructor<void (*)()>()
        .endClass();
}

Camera::Camera()
{
    pos = glm::vec3(0.0, 0.0, 0.0);
    rot = glm::vec3(0.0, 0.0, 0.0);
    angle = glm::vec2(0.0, 0.0);

    w_f = false;
    w_b = false;
    w_r = false;
    w_l = false;
}

void Camera::update()
{
    if (angle.x < -M_PI)
        angle.x += M_PI * 2;
    if (angle.x > M_PI)
        angle.x -= M_PI * 2;

    if (angle.y < -M_PI / 2.2)
        angle.y = -M_PI / 2.2;
    if (angle.y > M_PI / 2.2)
        angle.y = M_PI / 2.2;

    rot.x = sinf(angle.x) * cosf(angle.y);
    rot.y = sinf(angle.y);
    rot.z = cosf(angle.x) * cosf(angle.y);

    if (w_f) {
        pos.x += float(sin(angle.x))*.025f*GameState::gameObject()->getDeltaTime();
        pos.z += float(cos(angle.x))*.025f*GameState::gameObject()->getDeltaTime();
    }

    if (w_b) {
        pos.x -= float(sin(angle.x))*.025f*GameState::gameObject()->getDeltaTime();
        pos.z -= float(cos(angle.x))*.025f*GameState::gameObject()->getDeltaTime();
    }

    if (w_l) {
        pos.x += float(cos(angle.x))*.025f*GameState::gameObject()->getDeltaTime();
        pos.z -= float(sin(angle.x))*.025f*GameState::gameObject()->getDeltaTime();
    }

    if (w_r) {
        pos.x -= float(cos(angle.x))*.025f*GameState::gameObject()->getDeltaTime();
        pos.z += float(sin(angle.x))*.025f*GameState::gameObject()->getDeltaTime();
    }
}
