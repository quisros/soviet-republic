//main.cpp
//window creation

#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main (void) {
    
    GLFWwindow *window;
    
    //initialise the library
    if (!glfwInit()) {
        return -1;
    }
    
    //create a windowed mode window and its OpenGL Context
    window = glfwCreateWindow(640,480,"timing", NULL,NULL);
    
    if (!window) {
        glfwTerminate();
        return -1;
    }
    
    //make the window's context current
    glfwMakeContextCurrent(window);
    
    //loop until the user closes the window
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        //render the OpenGL,put all your OpenGL code right here
        
        //swap front and back buffers
        glfwSwapBuffers(window);
        
        //pool for and process events
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
    
}
