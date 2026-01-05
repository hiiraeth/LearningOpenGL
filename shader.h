
#ifndef LEARNOPENGL_SHADER_H
#define LEARNOPENGL_SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <istream>
#include <sstream>
#include <iostream>


class Shader {
public:
    // program ID
    GLuint ID;

    // constructor reads/builds shader
    Shader(const char* vertexPath, const char* fragmentPath);

    // use/activate the shader
    void use();

    // utility uniform funcs
    void setBool(const std::string& name, GLboolean value) const;
    void setInt(const std::string& name, GLint value) const;
    void setFloat(const std::string& name, GLfloat value) const;
	void setVec3(const std::string& name, GLfloat x, GLfloat y, GLfloat z) const;
	void setVec4(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const;
};

#endif //LEARNOPENGL_SHADER_H