#pragma once
#include <glm/glm.hpp>

namespace EngineX
{

    class Material
    {
    public:
        glm::vec3 Diffuse;
        float Specular;
        float Shininess;
    };

}