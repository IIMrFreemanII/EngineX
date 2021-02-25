#pragma once
#include <glm/glm.hpp>

namespace EngineX
{

    struct DirectionLight
    {
        glm::vec3 Direction;
        glm::vec3 Ambient;
        glm::vec3 Diffuse;
        glm::vec3 Specular;
    };

}