//
//  part2chessboard.cpp
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
const unsigned int SCR_WIDTH = 700;
const unsigned int SCR_HEIGHT = 700;


int main () {
    
    //glfw: initialize and configure
    
    glfwInit();
    if (!glfwInit ()) {
        cerr << "ERROR: could not start GLFW3" << endl;
        return 1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Chessboard", NULL, NULL);
    
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
    glewExperimental = GL_TRUE;
    glewInit();
    
    
    Shader shaderWhite("shaders/basic.vs", "shaders/white.fs");
    Shader shaderBlack("shaders/basic.vs", "shaders/black.fs");
    
    
    // set up vertex data (and buffer(s)) and configure vertex attributes
    
    float vertices[81*3];
    
    int i = 0;
    
    for(float y=0.8; y>=-0.8; y-=0.2) {
        for(float x=-0.8; x<=0.8; x+=0.2) {
            vertices[i] = x;
            vertices[i+1] = y;
            vertices[i+2] = 0.0;
            i+= 3;
        }
    }
    
    
    unsigned int indices1[64*3]; // vertices enclosing white triangles
    
    int j = 0;
    
    for(int k=0; k<32; k++) {
        int crindex=k*6;
        indices1[crindex] = j;
        indices1[crindex+1] = j+1;
        indices1[crindex+2] = j+9;
        indices1[crindex+3] = j+1;
        indices1[crindex+4] = j+9;
        indices1[crindex+5] = j+10;
        
        if (j==6||j==24||j==42||j==60) {
            j += 4;
        }
        
        else {
            j += 2;
        }
    }
    
    unsigned int indices2[64*3]; // vertices enclosing black triangles
    
    int t = 1;
    
    for(int k=0; k<32; k++) {
        int crindex=k*6;
        indices2[crindex] = t;
        indices2[crindex+1] = t+1;
        indices2[crindex+2] = t+9;
        indices2[crindex+3] = t+1;
        indices2[crindex+4] = t+9;
        indices2[crindex+5] = t+10;
        
        if (t==15||t==33||t==51||t==69) {
            t += 4;
        }
        
        else {
            t += 2;
        }
    }
    
    
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
    
    
    //uncomment below call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //change GL_LINE to GL_FILL to get default mode again

    
    // render loop
    
    while(!glfwWindowShouldClose(window)) {
        
        //input
        processInput(window);
        
        //render
        glClearColor(0.3f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        shaderWhite.use();
        
        glBindVertexArray(VAO1);
        glDrawElements(GL_TRIANGLES, 192, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        
        shaderBlack.use();
        
        glBindVertexArray(VAO2);
        glDrawElements(GL_TRIANGLES, 192, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // check events and call relevant fns, and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    glDeleteVertexArrays(1, &VAO1);
    glDeleteBuffers(1, &VBO1);
    glDeleteVertexArrays(1, &VAO2);
    glDeleteBuffers(1, &VBO2);

    //clear all previously allocated GLFW resources
    glfwTerminate();
    return 0;
    
}
