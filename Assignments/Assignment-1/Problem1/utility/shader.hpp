//
//  shader.hpp
//  glinat0
//
//  Created by Shabnam Sahay on 29/03/20.
//  Copyright © 2020 PAR. All rights reserved.
//

#ifndef shader_h
#define shader_h

#include<GL/glew.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include"readin.hpp"

class Shader {
    
public:
    //the program ID
    unsigned int ID;
    
    //constructor reads and builds the shader
    Shader (const char* vertexPath, const char* fragmentPath);
    
    //use/activate the shader
    void use();
    
    //utility uniform functions: query a uniform location and set its value
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    
private:
    
    void checkCompileErrors(unsigned int shader, std::string type);
    
};


#endif /* shader_h */
