//
//  tut01.cpp
//
//  Created by Shabnam Sahay on 26/03/20.
//  Copyright © 2020 PAR. All rights reserved.
//

# include "gl_framework.hpp"
# include "shader_util.hpp"

#include<iostream>
using namespace std;

//array giving coordinates of triangle vertices
//first three entries correspond to one vertex and so on
float points[] = {
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
};

//declaring unsigned integers using OGL enums to make code portable across different OSs
GLuint shaderProgram; //to become ID used by OGL for a compiled shader program obj
GLuint vbo, vao; //vertex buffer obj and vertex array obj

void initShadersGL(void) {
    
    string vertex_shader_file("simple_vs.glsl");
    string fragment_shader_file("simple_fs.glsl");
    
    vector<GLuint> shaderList;
    shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
    shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));
    //fn inside pushback sets up a shader that OGL can use and returns a GLuint
    
    shaderProgram = csX75::CreateProgramGL(shaderList);
    //links the vertex and fragment shaders - compiles them into a single program
    //
    
}

void initVertexBufferGL(void) {
    
    //create a vbo
    glGenBuffers(1, &vbo);
    
    //set it as the current buffer to be used by binding it
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    //alternate first arg is GL_ELEMENT_ARRAY_BUFFER
    //former for vertices, latter for reusing vertices when creating mesh of polygons
    
    //copy the points into the current buffer - 9 float values, start pointer and static data
    glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), points, GL_STATIC_DRAW);
    //GL_STATIC_DRAW indicates vertex data not going to be changed repeatedly
    //to make animation of some sort, would use GL_DYNAMIC_DRAW
    
    //create a vao
    glGenVertexArrays(1, &vao);
    
    //set it as the current array to be used by binding it
    glBindVertexArray(vao);
    
    //enable the vertex attribute
    glEnableVertexAttribArray(0);
    
    //This the layout of our first vertex buffer
    
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    //"0" means define the layout for attribute number 0
    
    //"3" means that the variables are vec3 made from every 3 floats
    //i.e. 3 elements of vbo correspond to single vertex
    
    //GL_FLOAT specifies that vbo has floatingpoint values
    //GL_FALSE specifies that normalisation should not be done
    //should be used when either GL_FLOAT or GL_DOUBLE are there
    
    //fifth parameter is stride of vbo
    //tells OGL how much gap there is between data for consecutive vertices
    
    //sixth parameter specifies byte offset from front of vbo
    
}

void renderGL(void) {
    
    //clear the color and depth buffers (the bit strings are orthogonal)
    //wiping the screen clean
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //tell OGL to use shader program we had created earlier
    //use this if you have different shader programs and want to switch between
    glUseProgram(shaderProgram);
    
    //bind the vao
    glBindVertexArray(vao);
    //check what happens if this line is shifted to the while loop, just above renderGL()
    
    //draw points 0-3 from the currently bound vao with current in-use shader
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
}

int main (int argc, char** argv) {
    
    //pointer to the GLFW window
    GLFWwindow* window;
    
    //setting up the GLFW error callback
    //takes function pointer as argument
    //calls the fn when something goes wrong with GLFW
    glfwSetErrorCallback(csX75::error_callback);
    
    //initialize GLFW
    if(!glfwInit()) {
        return -1;
    }
    
    //we want OGL 4.0
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    
    //this is for OSX, can be omitted otherwise
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    //we don't want the old OGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    //create a windowed mode window and its OGL context
    window = glfwCreateWindow(640, 480, "OGL Framework: Triangle", NULL, NULL);
    
    if(!window) {
        glfwTerminate();
        return -1;
    }
    
    //make window's context current
    glfwMakeContextCurrent(window);
    
    //initalize GLEW
    //turn this on to get shader based OGL
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    
    if(GLEW_OK!=err) {
        //problem: glewInit failed, something is seriousy wrong
        cerr << "GLEW Init Failed : %s" << endl;
    }
    
    //print and see what context got enabled
    cout << "Vendor: " << glGetString(GL_VENDOR) << endl;
    cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
    cout << "Version: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
    
    //keyboard callback: called when user presses a key
    glfwSetKeyCallback(window, csX75::key_callback);
    
    //framebuffer resize callback: called whenever window resized
    glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);
    
    //ensure we can capture the escape key being pressed
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    //a polling fn called glfwGetKey() is used to determine if a key is pressed or not
    //turning on sticky keys tells GLFW to act as though a key is kept pressed
    //until glfwGetKey() is called
    
    //initialize GL state
    csX75::initGL();
    initShadersGL();
    initVertexBufferGL();
    
    //loop unti the user closes the window
    while (glfwWindowShouldClose(window)==0) {
        
        //render here
        renderGL();
        
        //swap front and back buffers
        glfwSwapBuffers(window);
        
        //poll for and process events
        glfwPollEvents();
        
    }
    
    glfwTerminate();
    return 0;
    
}
