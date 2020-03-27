//
//  gl_framework.hpp
//
//  Created by Shabnam Sahay on 27/03/20.
//  Copyright © 2020 PAR. All rights reserved.
//

#ifndef _GL_FRAMEWORK_HPP_
#define _GL_FRAMEWORK_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace csX75 {
    
// initialize GL state
void initGL(void);

//GLFW error callback
void error_callback(int error, const char* description);
//GLFW framebuffer resize callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//GLFW keyboard callback
void key_callback(GLFWwindow* window, int key, int scancode, int aciton, int mods);

};


#endif
