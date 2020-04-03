#version 330 core

layout(location = 0) in vec3 aPos;    //posn variable has attribute posn 0
layout(location = 1) in vec3 aColor;  //color variable has attribute posn 1

out vec3 ourColor;  //output a color to the fragment shader

void main ()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;  //set ourColor to the input color we got from vertex data
}
