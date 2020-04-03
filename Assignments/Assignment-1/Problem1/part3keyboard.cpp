//
//  part3keyboard.cpp
//  soc-assignment-1
//  Created by Shabnam Sahay on 28/03/20.
//  Copyright © 2020 PAR. All rights reserved.
//

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"utility/readin.hpp"
#include"utility/shader.hpp"

#include<iostream>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main () {
    
    //glfw: initialize and configure
    
    glfwInit();
    if (!glfwInit ()) { // glfwInit() attempts to initialize GLFW lib
        cerr << "ERROR: could not start GLFW3" << endl;
        return 1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Keyboard", NULL, NULL);
    
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glViewport(0,0,SCR_WIDTH,SCR_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    
    //start GLEW extension handler
    glewExperimental = GL_TRUE; //enables experimental extensions
    glewInit();
    
    
    Shader shaderWhite("shaders/basic.vs", "shaders/white.fs");
    Shader shaderBlack("shaders/basic.vs", "shaders/black.fs");
    
    
    // set up vertex data (and buffer(s)) and configure vertex attributes
    
    float vertices[] = {
        -0.5f, -0.1f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        -0.35f, 0.5f, 0.0f,
        -0.35f, -0.1f, 0.0f,
        -0.15f, -0.1f, 0.0f,
        -0.15f, 0.5f, 0.0f,
        -0.1f, 0.5f, 0.0f,
        -0.1f, -0.1f, 0.0f,
        0.1f, -0.1f, 0.0f,
        0.1f, 0.5f, 0.0f,
        0.15f, 0.5f, 0.0f,
        0.15f, -0.1f, 0.0f,
        0.35f, -0.1f, 0.0f,
        0.35f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, -0.1f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.45f, 0.5f, 0.0f,
        -0.45f, -0.5f, 0.0f,
        0.45f, 0.5f, 0.0f,
        0.45f, -0.5f, 0.0f,
        -0.25f, 0.5f, 0.0f,
        -0.25f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
        0.25f, 0.5f, 0.0f,
        0.25f, -0.5f, 0.0f,
    };
    
    unsigned int indices1[] = { // vertices enclosing white areas
        0, 1, 2,
        0, 2, 3,
        4, 5, 6,
        4, 6, 7,
        8, 9, 10,
        8, 10, 11,
        12, 13, 14,
        12, 14, 15,
        0, 15, 16,
        0, 16, 17
    };
    
    unsigned int indices2[] = { // vertices enclosing black areas
        2, 3, 4,
        2, 4, 5,
        6, 7, 8,
        6, 8, 9,
        10, 11, 12,
        10, 12, 13
    };
    
    
    //generating vao, vbo, ebo for white areas
    
    unsigned int VAO1, VBO1, EBO1;
    glGenVertexArrays(1,&VAO1);
    glGenBuffers(1,&VBO1);
    glGenBuffers(1,&EBO1);
    
    glBindVertexArray(VAO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
   
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    
    //generating vao, vbo, ebo for black areas
    
    unsigned int VAO2, VBO2, EBO2;
    glGenVertexArrays(1,&VAO2);
    glGenBuffers(1,&VBO2);
    glGenBuffers(1,&EBO2);
    
    glBindVertexArray(VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    
    //generating vao and vbo for black lines
    
    unsigned int VAO3, VBO3;
    glGenVertexArrays(1,&VAO3);
    glGenBuffers(1,&VBO3);
    
    glBindVertexArray(VAO3);
    glBindBuffer(GL_ARRAY_BUFFER, VBO3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    
    //uncomment below call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //change GL_LINE to GL_FILL to get default mode again

    
    // render loop
    
    while(!glfwWindowShouldClose(window)) {
        
        //input
        processInput(window);
        
        //render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        shaderWhite.use();
        
        glBindVertexArray(VAO1);
        glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        
        shaderBlack.use();
        
        glBindVertexArray(VAO2);
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        
        glBindVertexArray(VAO3);
        glDrawArrays(GL_LINES, 16, 12);
        glBindVertexArray(0);
        
        // check events and call relevant fns, and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    glDeleteVertexArrays(1, &VAO1);
    glDeleteBuffers(1, &VBO1);
    glDeleteVertexArrays(1, &VAO2);
    glDeleteBuffers(1, &VBO2);
    glDeleteVertexArrays(1, &VAO3);
    glDeleteBuffers(1, &VBO3);

    //clear all previously allocated GLFW resources
    glfwTerminate();
    return 0;
    
}
