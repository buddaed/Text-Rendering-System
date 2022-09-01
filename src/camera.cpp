#include "camera.h"

Camera::Camera(wolf::App *inApp)
{
    app = inApp;
    glfwSetInputMode(app->m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Camera::~Camera()
{
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::update(float dt)
{
    glm::vec2 mousePos = app->getMousePos();
    float speed = 100 * dt;

    if (app->isKeyDown('w'))
    {
        cameraPos += cameraFront * speed;
    }
    if (app->isKeyDown('s'))
    {
        cameraPos -= cameraFront * speed;
    }
    if (app->isKeyDown('a'))
    {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
    }
    if (app->isKeyDown('d'))
    {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
    }

    if (firstMouse)
    {
        lastX = mousePos.x;
        lastY = mousePos.y;
        firstMouse = false;
    }

    float xoffset = mousePos.x - lastX;
    float yoffset = lastY - mousePos.y; // reversed since y-coordinates go from bottom to top
    lastX = mousePos.x;
    lastY = mousePos.y;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;

    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    cameraFront = glm::normalize(front);
}