#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "pointlight.h"
#include "object.h"
#include "camera.h"

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>



class UserInterface
{
public:
    UserInterface(PointLight* m_pl, GLFWwindow* window);
    ~UserInterface();
    void Bind(Shader *shader);
    void Draw();
    float m_rotationSpeed;





protected:
    PointLight *m_pl;
    glm::vec3 m_ambienLightColor;
};

#endif // USERINTERFACE_H
