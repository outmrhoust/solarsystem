#include "pointlight.h"

PointLight::PointLight(glm::vec3 pos, glm::vec3 col, float pow)
            : position(pos), color(col), power(pow) {}

void PointLight::Bind(Shader& shader) {
            // Bind the point light attributes to the shader as uniforms
            shader.setUniform3fv("pointLightPosition", position);
            shader.setUniform3fv("pointLightColor", color);
            shader.setUniform1f("pointLightPower", power);
        }

void PointLight::Unbind() {
            // Unbind if needed
        }
