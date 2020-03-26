//
//  tut00.cpp
//  sets up a OpenGL context and queries for the available GL version
//  glinat0
//
//  Created by Shabnam Sahay on 25/03/20.
//  Copyright © 2020 PAR. All rights reserved.
//

#include <GL/glew.h> //include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> //GLFW helper library

#include <iostream>
using namespace std;

int main (int argc, char** argv) {
    
    if (!glfwInit ()) { // glfwInit() attempts to initialize GLFW lib
        cerr << "ERROR: could not start GLFW3" << endl;
        return 1;
    }
    
    // hints to GLFW about OGL version, profile and forward compatibility
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //above 4 lines can be commented out if not using OS X
    
    GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL Initialization Example", NULL, NULL);
    // window width, height, name, 4th parameter - don't want fullscreen
    
    if (!window) {
        cerr << "ERROR: could not open window with GLFW3" << endl;
        glfwTerminate();
        return 1;
    }
    
    glfwMakeContextCurrent (window);
    //context contained by window set as current context
    
    //start GLEW extension handler
    glewExperimental = GL_TRUE; //enables experimental extensions
    glewInit();
    
    //get version info
    const GLubyte* renderer = glGetString (GL_RENDERER); //get renderer string
    const GLubyte* version = glGetString (GL_VERSION); //version as a string
    cout << "Renderer: " << renderer << endl;
    cout << "OpenGL version supported " << version << endl;
    
    // close GL context and any other GLFW resources
    glfwTerminate();
    return 0;
    
}
