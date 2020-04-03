//
//  2D shape: Z
//  Created by Shabnam Sahay on 28/03/20.
//  Copyright © 2020 PAR. All rights reserved.
//

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"utility/readin.hpp"
#include"utility/shader.hpp"
#include"utility/stb_image.h"

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
    if (!glfwInit ()) { // glfwInit() attempts to initialize GLFW lib
        cerr << "ERROR: could not start GLFW3" << endl;
        return 1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Z strikes", NULL, NULL);
    
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
    
    float vertices[] = {
        // positions        // colors         // texture coords
         0.6f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.80f, 0.25f,
         0.6f, -0.6f, 0.0f, 0.0f, 0.0f, 0.0f, 0.80f, 0.20f,
        -0.6f, -0.6f, 0.0f, 0.0f, 0.0f, 0.0f, 0.20f, 0.20f,
        -0.6f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.20f, 0.25f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.25f, 0.25f,
         0.6f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.80f, 0.75f,
         0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.75f, 0.75f,
        -0.6f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.20f, 0.75f,
        -0.6f,  0.6f, 0.0f, 0.0f, 0.0f, 0.0f, 0.20f, 0.80f,
         0.6f,  0.6f, 0.0f, 0.0f, 0.0f, 0.0f, 0.80f, 0.80f
    };
    
    unsigned int indices[] = { // we start from 0
        0, 1, 2,
        0, 2, 3,
        3, 4, 5,
        3, 5, 6,
        5, 7, 8,
        5, 8, 9
    };
    
    //generating vao and vbo
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    
    //bind the Vertex Array Object first, then bind and set vertex buffer(s)
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    //configure vertex attributes / copy defined vertex data into buffer's memory
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    //copy our index array in a element buffer for OpenGL to use
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
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("textures/geo.jpg", &width, &height, &nrChannels, 0);
    
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
    
    
    // render loop
    
    while(!glfwWindowShouldClose(window)) {
        
        //input
        processInput(window);
        
        //render
        glClearColor(0.0f, 0.4f, 0.7f, 0.3f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        //activating shader program
        shaderProgram.use();
        
        //bind texture
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        
        //drawing the object
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
        
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
