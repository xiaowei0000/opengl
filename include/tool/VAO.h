#ifndef VAO_CLASS
#define VAO_CLASS

#include<glad/glad.h>
#include"VBO.h"

class VAO{
public:

    GLuint ID;

    VAO();

    void LinkVBO(VBO &VBO,GLuint layout);
    void LinkAttrib(VBO& VBO,GLuint layout,GLuint numComponents,GLenum type,GLsizeiptr stride,void *offset);
    void Bind();
    void Unbind();
    void Delete();
};
#endif