#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <glm/glm.hpp>
#include <string>
#include "shader.h" // Include your Shader class

class PointLight
{
public:
    PointLight(glm::vec3 pos, glm::vec3 col, float pow);
    void Bind(Shader& shader);
    void Unbind();
    glm::vec3 getPosition(){return position;};
    glm::vec3 position;
    glm::vec3 color;
    float power;
};

#endif // POINTLIGHT_H
