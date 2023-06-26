#ifndef VBO_CLASS
#define VBO_CLASS

#include<glad/glad.h>

class VBO{
public:
    GLuint ID;

    VBO(GLfloat* vertices,GLsizeiptr size);

    //bind the vbo
    void Bind();
    //unbind the vbo
    void Unbind();
    //deletes the vbo
    void Delete();
};
#endif