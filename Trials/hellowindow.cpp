//
//  hellowindow.cpp
//  glinat0
//
//  Created by Shabnam Sahay on 26/03/20.
//  Copyright © 2020 PAR. All rights reserved.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include<iostream>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0,0,width,height);
}

int main () {
    
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    
    if(window==NULL) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    //telling OpenGL size of rendering window so stuff displayed wrt it
    glViewport(0,0,800,600);
    
    //viewport should get adjusted when user resizes the window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    while(!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window); //swaps color buffer used to render
        glfwPollEvents(); //checks if events are triggered and calls corresp fns
    }
    
    glfwTerminate();
    return 0;
    
}
