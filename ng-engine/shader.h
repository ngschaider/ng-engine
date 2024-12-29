#pragma once

#include <string>
#include "vector2.h"
#include "vector2i.h"
#include "vector3.h"
#include "vector4.h"
#include "matrix3x3.h"
#include "matrix4x4.h"

/**
* A compiled and linked OpenGL shader program.
*/
class Shader {
public:
    /**
    * The ID assigned by OpenGL. This should only be modified by the Shader.
    */
    unsigned int id;

    /**
    * Load, compile and link a new shader program from the given paths
    */
    Shader(const char* vertexFile, const char* fragmentFile);

    /**
    * De-allocates the allocated graphics memory and destructs the object.
    */
    virtual ~Shader();

    /**
    * Activates the shader program.
    */
    void use();

    /**
    * Sets a uniform variable with the given name to the given value.
    * This method uses glUniform1f.
    */
    void setFloat(const char* name, float value) const;

    /**
    * Sets a uniform variable with the given name to the given value.
    * This method uses glUniform1i.
    */
    void setInteger(const char* name, int value) const;

    /**
    * Sets a uniform variable with the given name to the given value.
    * This method uses glUniform2f.
    */
    void setVector2(const char* name, Vector2 value) const;

    /**
    * Sets a uniform variable with the given name to the given value.
    * This method uses glUniform2i.
    */
    void setVector2i(const char* name, Vector2i value) const;

    /**
    * Sets a uniform variable with the given name to the given value.
    * This method uses glUniform3f.
    */
    void setVector3(const char* name, Vector3 value) const;

    /**
    * Sets a uniform variable with the given name to the given value.
    * This method uses glUniform4f.
    */
    void setVector4(const char* name, Vector4 value) const;

    /**
    * Sets a uniform variable with the given name to the given value.
    * This method uses glUniformMatrix3fv.
    */
    void setMatrix3x3(const char* name, Matrix3x3 m) const;

    /**
    * Sets a uniform variable with the given name to the given value.
    * This method uses glUniformMatrix4fv.
    */
    void setMatrix4x4(const char* name, Matrix4x4 m) const;
};