#pragma once

#include <string>
#include "matrix4x4.h"

class Shader {
public:
    unsigned int id;
    Shader(const char*, const char*);
    ~Shader();
    void use();
    void setMatrix4x4(const std::string&, Matrix4x4) const;
    void setVector3(const std::string&, Vector3) const;
};