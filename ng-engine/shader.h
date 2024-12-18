#pragma once

#include <string>
#include "vector2.h"
#include "vector2i.h"
#include "vector3.h"
#include "vector4.h"
#include "matrix3x3.h"
#include "matrix4x4.h"

class Shader {
public:
    unsigned int id;
    Shader(const char*, const char*);
    ~Shader();
    void use();

    void setFloat(const char*, float) const;
    void setInteger(const char*, int) const;
    void setVector2(const char*, Vector2) const;
    void setVector2i(const char*, Vector2i) const;
    void setVector3(const char*, Vector3) const;
    void setVector4(const char*, Vector4) const;
    void setMatrix3x3(const char*, Matrix3x3) const;
    void setMatrix4x4(const char*, Matrix4x4) const;
};