#pragma once
#include "../wolf/wolf.h"

class Camera
{
public:
    Camera(wolf::App *);
    ~Camera();

    void update(float);

    glm::mat4 getViewMatrix() const;

private:
    wolf::App *app;

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 800.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float camx = 0.0f;
    float camz = 0.0f;
    float yaw = -90.0f; // yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
    float pitch = 0.0f;
    float lastX;
    float lastY;
    bool firstMouse = true;
};