#ifndef CARMERA_CLASS
#define CARMERA_CLASS

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/vector_angle.hpp>
#include<glm/gtx/rotate_vector.hpp>

#include"shaderClass.h"
class Camera{
public:
    glm::vec3 Position;
    glm::vec3 Orientation=glm::vec3(0.0f,0.0f,-1.0f);
    glm::vec3 Up=glm::vec3(0.0f,1.0f,0.0f);
    
};

#endif