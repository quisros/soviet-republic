//GLSL is a C-like shading language used to write shaders for OGL

//define GLSL version being used
#version 400

in vec3 vp;
//vertex shader will get one input
//a vector of three elements named 'vp'

void main () {
    
    gl_Position = vec4(vp,1.0);
    
    //1.0f appended to end of the 3-vector to turn it into a 4-vector
    //OGL uses homogenous coordinates
    //so output of vertex shader needs to be a 4-vector
    //which is the coordinates of the vertex in clip space
    
}
