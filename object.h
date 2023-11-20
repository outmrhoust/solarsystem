#ifndef OBJECT_H
#define OBJECT_H

#include <string>

#include <glm/glm.hpp>

#include "vertexbuffer.h"
#include "vertexarray.h"
#include "texture.h"
#include "uvbuffer.h"

class Object
{
public:
//    Object(std::vector< glm::vec3 > vertices, std::vector< glm::vec2 > uvs,std::vector<glm::vec3> normals, std::string texturePath);
    Object(std::string objPath, std::string texturePath);
    ~Object();
    void Bind() const;
    void Unbind() const;
    void Draw() const;
    glm::vec3 position;
    glm::vec3 rotationAngles;
    float scaleFactor;
    glm::mat4 getModelMatrix();
    void setReflectivity(float n);
    float getReflectivity(){return this->m_reflectivity;};
    bool loadOBJ(const char *path, std::vector<glm::vec3> &out_vertices, std::vector<glm::vec2> &out_uvs, std::vector<glm::vec3> &out_norm);

private:
    VertexBuffer *m_vb;
    UVBuffer *m_uvsb;
    Texture *m_texture;
    VertexBuffer* m_normalsb; // New normals buffer
    float m_reflectivity;

};

#endif // OBJECT_H
