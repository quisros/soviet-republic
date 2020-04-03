//
//  disc.cpp
//  glinat0
//
//  Created by Shabnam Sahay on 28/03/20.
//  Copyright © 2020 PAR. All rights reserved.
//

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"utility/readin.hpp"
#include"utility/shader.hpp"
#include"utility/stb_image.h"

#include<iostream>
#include<cmath>
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

float degtorad(int degrees) {
    const float pi = 3.14159;
    return (degrees*pi)/180;
}


// settings
const unsigned int SCR_WIDTH = 700;
const unsigned int SCR_HEIGHT = 700;


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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Textured Disc", NULL, NULL);
    
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
    
    Shader shaderProgram("shaders/poscoltex.vs", "shaders/createtex.fs");
    
    // set up vertex data (and buffer(s)) and configure vertex attributes
    
    float r = 0.75;
    
    float vertices[361*8];
    
    for(int i = 0; i<8; i++) {
        if (i<6) {
            vertices[i] = 0.0;
        }
        else {
            vertices[i] = 0.5;
        }
    }
    
    for(int i = 1; i<=360; i++) {
        float theta = degtorad(i);
        int crindex = i*8;
        vertices[crindex] = r*cos(theta);
        vertices[crindex+1] = r*sin(theta);
        vertices[crindex+2] = 0.0;
        vertices[crindex+3] = 0.0;
        vertices[crindex+4] = 0.0;
        vertices[crindex+5] = 0.0;
        vertices[crindex+6] = (0.5*cos(theta)) + 0.5;
        vertices[crindex+7] = (0.5*sin(theta)) + 0.5;
    }
    
    unsigned int indices[360*3];
    
    for(int i = 0; i<360; i++) {
        int crindex = i*3;
        indices[crindex] = 0;
        indices[crindex+1] = i+1;
        if (i==359) {
            indices[crindex+2] = 1;
        }
        else {
            indices[crindex+2] = i+2;
        }
    }
    
    
    //generating vao, vbo, ebo
    
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    
    //load and create a texture
    
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    //set texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    //set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    //load image, create texture and generate mipmaps
    int width, height, nrChannels;
    unsigned char *data = stbi_load("textures/mandala.jpg", &width, &height, &nrChannels, 0);
    
    //now that texture is bound, generating the texture using image data
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        //generate all required mipmaps for currently bound texture
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cout << "Failed to load texture" << endl;
    }
    
    //free the image memory now
    stbi_image_free(data);
    
    //uncomment below call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //change GL_LINE to GL_FILL to get default mode again

    
    // render loop
    
    while(!glfwWindowShouldClose(window)) {
        
        //input
        processInput(window);
        
        //render
        glClearColor(0.0f, 0.6f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        //activating shader program
        shaderProgram.use();
        
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        
        //drawing the object
        glDrawElements(GL_TRIANGLES, 1080, GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(0);
        
        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    //clear all previously allocated GLFW resources
    glfwTerminate();
    return 0;
    
}
