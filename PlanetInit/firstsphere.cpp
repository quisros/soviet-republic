//
//  Created by Shabnam Sahay on 28/03/20.
//  Copyright © 2020 PAR. All rights reserved.
//

#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include"utility/stb_image.h"
#include"utility/shader.hpp"
#include"utility/texture2D.hpp"
#include"utility/camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include<iostream>
#include<cmath>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

unsigned int loadCubemap(vector<std::string> faces);

float degtorad(int degrees) {
    const float pi = 3.14159;
    return (degrees*pi)/180;
}
const float radius = 1.5f;
const int sectorCount = 90;
const int stackCount = 90;



// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH/2.0f;
float lastY = SCR_HEIGHT/2.0f;
bool firstMouse = true;


// timing
float deltaTime = 0.0f; //time between current frame and last frame
float lastFrame = 0.0f; //time of last frame


//light source location in world space coordinates
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);


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
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "colors of life", NULL, NULL);
    
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glViewport(0,0,SCR_WIDTH,SCR_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    
    //tell GLFW to hide the cursor and capture it
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    
    //start GLEW extension handler
    glewExperimental = GL_TRUE; //enables experimental extensions
    glewInit();
    
    //enable depth testing for z buffer
    glEnable(GL_DEPTH_TEST);
    
    
    Shader containerShader("shaders/diffusestart.vs", "shaders/specularstart.fs");
    Shader lightsrcShader("shaders/lightingstart.vs", "shaders/lightsource.fs");
    Shader skyboxShader("shaders/skyboxinit.vs", "shaders/skyboxinit.fs");
    
    
    // set up vertex data (and buffer(s)) and configure vertex attributes
    
    float verticesSp[(sectorCount+1)*(stackCount+1)*8];
    int crindex = 0;
    
    float x,y,z,xy;                           //vertex position
    float nx,ny,nz;                           //vertex normal
    float lengthInv = 1.0f/radius;
    float s, t;                               //vertex texCoords
    
    float sectorStep = 2*180.0f/sectorCount;
    float stackStep = 180.0f/stackCount;
    float sectorAngle, stackAngle;
    
    for (int i = 0; i<=stackCount; ++i) {
        
        stackAngle = degtorad(180.0f/2 - i*stackStep);   //going from 90 deg to -90 deg
        xy = radius*cos(stackAngle);           //r*cos(u)
        z = radius*sin(stackAngle);            //r*sin(u)
        
        //add (sectorCount+1) vertices per stack
        //the first and last vertices have same posn and normal, but different tex coords
        
        for (int j = 0; j<=sectorCount; ++j) {
            
            sectorAngle = degtorad(j*sectorStep);        //going from 0 deg to 360 deg
            
            //vertex position (x,y,z)
            x = xy*cos(sectorAngle);           // r * cos(u) * cos(v)
            y = xy*sin(sectorAngle);           // r * cos(u) * sin(v)
            verticesSp[crindex] = x;
            verticesSp[crindex+1] = y;
            verticesSp[crindex+2] = z;
            
            //normalized vertex normal (nx,ny,nz)
            
            nx = x*lengthInv;
            ny = y*lengthInv;
            nz = z*lengthInv;
            verticesSp[crindex+3] = nx;
            verticesSp[crindex+4] = ny;
            verticesSp[crindex+5] = nz;
            
            //vertex tex coord (s,t) range between [0,1]
            s = (float)j/sectorCount;
            t = (float)i/stackCount;
            verticesSp[crindex+6] = s;
            verticesSp[crindex+7] = t;
            
            crindex = crindex + 8;
            
        }
        
    }
    
    int compVerts = sectorCount*2*(stackCount-1)*3;
    unsigned int indices[compVerts];
    int indindex = 0;
    
    int k1,k2;
    
    for (int i = 0; i<stackCount; ++i) {
        
        k1 = i*(sectorCount + 1);     //beginning of current stack
        k2 = k1 + sectorCount + 1;    //beginning of next stack
        
        for (int j = 0; j<sectorCount; ++j, ++k1, ++k2) {
            
            //2 triangles per sector excluding first and last stacks
            
            //k1 => k2 => k1+ 1
            if(i!=0) {
                indices[indindex] = k1;
                indices[indindex+1] = k2;
                indices[indindex+2] = k1+1;
                indindex += 3;
            }
            
            //k1+1=>k2=>k2+1
            if (i!=(stackCount-1)) {
                indices[indindex] = k1 + 1;
                indices[indindex+1] = k2;
                indices[indindex+2]= k2 + 1;
                indindex = indindex + 3;
            }
            
        }
        
    }
   
  
    
    
    float skyboxVertices[] = {
        // positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };
    
    
    
    //generating container vao and vbo
    unsigned int containerVAO, VBO, containerEBO;
    glGenVertexArrays(1,&containerVAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&containerEBO);
    
    //bind the Vertex Array Object first, then bind and set vertex buffer(s)
    glBindVertexArray(containerVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    //configure vertex attributes / copy defined vertex data into buffer's memory
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesSp), verticesSp, GL_STATIC_DRAW);
    
    //copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, containerEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    
    //generating light source vao and vbo
    unsigned int lightsrcVAO, lightsrcEBO;
    glGenVertexArrays(1,&lightsrcVAO);
    glGenBuffers(1,&lightsrcEBO);
    
    //bind the Vertex Array Object first, then bind and set vertex buffer(s)
    glBindVertexArray(lightsrcVAO);
    
    // we only need to bind to the VBO, the container's VBO already contains the data.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    //copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightsrcEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    
    
    //generating skybox vao and vbo
    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1,&skyboxVAO);
    glGenBuffers(1,&skyboxVBO);
    
    //bind the Vertex Array Object first, then bind and set vertex buffer(s)
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    
    //configure vertex attributes / copy defined vertex data into buffer's memory
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
    
    // position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
                  
    
    //declaring vector containing filepaths of skybox images
    vector<std::string> faces =
    {
        "skyboxes/nightchanges/right.jpg",
        "skyboxes/nightchanges/left.jpg",
        "skyboxes/nightchanges/top.jpg",
        "skyboxes/nightchanges/bottom.jpg",
        "skyboxes/nightchanges/front.jpg",
        "skyboxes/nightchanges/back.jpg"
    };
    
    //load and create a cubemap
    unsigned int cubemapTexture = loadCubemap(faces);
    
    skyboxShader.use();
    skyboxShader.setInt("skybox", 0);

    
    
    containerShader.use();
    containerShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    containerShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    containerShader.setVec3("lightPos", lightPos);

    
    
    // render loop
    
    while(!glfwWindowShouldClose(window)) {
        
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        //input
        processInput(window);
        
        //render
        
        glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //also clear depth buffer
        
        
        //activate shader
        containerShader.use();
        containerShader.setVec3("viewPos", camera.Position);
        
        //pass projection matrix to shader
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/SCR_HEIGHT, 0.1f, 100.0f);
        containerShader.setMat4("projection", projection);
        
        //camera transformation
        glm::mat4 view = camera.GetViewMatrix();
        containerShader.setMat4("view", view);
        
        glBindVertexArray(containerVAO);
        glm::mat4 model = glm::mat4(1.0f);
        containerShader.setMat4("model", model);
        glDrawElements(GL_TRIANGLES, compVerts, GL_UNSIGNED_INT,0);
        glBindVertexArray(0);
        
        
        //activate shader
        lightsrcShader.use();
        lightsrcShader.setMat4("projection", projection);
        lightsrcShader.setMat4("view", view);
        
        glBindVertexArray(lightsrcVAO);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        //model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.3f, 0.5f));
        lightsrcShader.setMat4("model", model);
        glDrawElements(GL_TRIANGLES, compVerts, GL_UNSIGNED_INT,0);
        glBindVertexArray(0);
        
        
        glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content
        skyboxShader.use();
        
        //pass projection matrix to shader
        glm::mat4 skyboxProjection = glm::mat4(1.0f);
        skyboxProjection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/SCR_HEIGHT, 0.1f, 100.0f);
        skyboxShader.setMat4("projection", skyboxProjection);
        
        //camera transformation
        glm::mat4 skyboxView = glm::mat4(glm::mat3(camera.GetViewMatrix()));
        skyboxShader.setMat4("view", skyboxView);
        
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // set depth function back to default
        
        
        
        // check and call events and swap the buffers
        glfwSwapBuffers(window); //swaps color buffer used to render
        glfwPollEvents(); //checks if events are triggered and calls corresp fns
        
    }
    
    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &skyboxVAO);
    glDeleteBuffers(1, &skyboxVBO);
    glDeleteVertexArrays(1, &containerVAO);
    glDeleteVertexArrays(1, &lightsrcVAO);
    glDeleteBuffers(1, &VBO);

    //clear all previously allocated GLFW resources
    glfwTerminate();
    return 0;
    
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if(glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    
    if(glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    
    if(glfwGetKey(window, GLFW_KEY_A)==GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    
    if(glfwGetKey(window,GLFW_KEY_D)==GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    
    if(firstMouse) { //initially set to true
        
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
        
    }
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; //reversed simce y coords range from bottom to top
    lastX = xpos;
    lastY = ypos;
    
    camera.ProcessMouseMovement(xoffset, yoffset);
    
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    
    camera.ProcessMouseScroll(yoffset);
    
}

unsigned int loadCubemap(vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}
