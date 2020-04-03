//
//  shader.cpp
//  glinat0
//
//  Created by Shabnam Sahay on 29/03/20.
//  Copyright © 2020 PAR. All rights reserved.
//


#include<GL/glew.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include "shader.hpp"

Shader::Shader (const char* vertexPath, const char* fragmentPath)
{
    
    //1. retrieve the vertex/fragment source code from filePath
    std::string vShaderInput = readFile(vertexPath);
    std::string fShaderInput = readFile(fragmentPath);
    
    const char* vShaderCode = vShaderInput.c_str();
    const char* fShaderCode = fShaderInput.c_str();
    
    //2. compile shaders
    unsigned int vertex, fragment;
    
    //vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    
    //fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    
    //shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    //print linking errors if any
    
    //delete shaders, now redundant
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type!= "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << std::endl;
        }
    }
}
