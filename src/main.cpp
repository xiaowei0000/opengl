#include<filesystem>
namespace fs=std::filesystem;

#include<glad/glad.h>
#include <GLFW/glfw3.h>

#include<iostream>
#include<string>
#include<math.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include<tool/shaderClass.h>
#include<tool/VAO.h>
#include<tool/VBO.h>
#include<tool/EBO.h>
#include<tool/Texture.h>
#include<tool/camera.h>
 GLfloat vertices[]={
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
    };

    GLuint indices[]={
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
    };
    unsigned int width=800;
    unsigned int height=800;
    int main(int argc, char *argv[])
    {
        GLFWwindow* window;
 
        if (!glfwInit()) return -1;
 
        window = glfwCreateWindow(800, 800, "TestOpenGL", NULL ,NULL);
 
        if (!window)
        {
            glfwTerminate();
            return -1;
        }
 
        glfwMakeContextCurrent(window);

        gladLoadGL();

        glViewport(0,0,800,800);

        Shader shaderProgram("glsl\\camera\\default.vert","glsl\\camera\\default.frag");

        VAO VAO1;
        VAO1.Bind();

        VBO VBO1(vertices,sizeof(vertices));

        EBO EBO1(indices,sizeof(indices));

        //VAO1.LinkVBO(VBO1,0);
        VAO1.LinkAttrib(VBO1,0,3,GL_FLOAT,8*sizeof(float),(void*)0);
        VAO1.LinkAttrib(VBO1,1,3,GL_FLOAT,8*sizeof(float),(void*)(3*sizeof(float)));
        VAO1.LinkAttrib(VBO1,2,2,GL_FLOAT,8*sizeof(float),(void*)(6*sizeof(float)));

        VAO1.Unbind();
        VBO1.Unbind();
        EBO1.Unbind();

        //GLuint uniID=glGetUniformLocation(shaderProgram.ID,"scale");

        std::string parentDir=(fs::current_path().fs::path::parent_path().string());
        std::string texPath="\\OPENGLLEARN\\resources\\brick.png";

        Texture popCat((parentDir+texPath).c_str(),GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
        popCat.texUnit(shaderProgram,"tex0",0);

        float rotation=0.0f;
        double prevTime=glfwGetTime();

        glEnable(GL_DEPTH_TEST);

        Camera camera(width,height,glm::vec3(0.0f,0.0f,2.0f));

        while (!glfwWindowShouldClose(window))
        {
            glClearColor(0.07f,0.13f,0.17f,1.0f);

            glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

            shaderProgram.Activate();
           
            double crntTime=glfwGetTime();
            if(crntTime-prevTime>=1/60)
            {
                rotation+=0.5f;
                prevTime=crntTime;
            }
            //初始化矩阵

            camera.Inputs(window);

            camera.Matrix(45.0f,0.1f,100.0f,shaderProgram,"camMatrix");
            
            popCat.Bind();
            
            VAO1.Bind();

            glDrawElements(GL_TRIANGLES,sizeof(indices)/sizeof(int),GL_UNSIGNED_INT,0);
 
            glfwSwapBuffers(window);
 
            glfwPollEvents();
        }
        glfwTerminate();
        return 0;
    }