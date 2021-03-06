#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec2 TexCoords;
out mat3 TBN;

void main()
{
    vec3 T = normalize(vec3(model*vec4(aTangent, 0.0)));
    vec3 N = normalize(vec3(model*vec4(aNormal, 0.0)));
    
    //re-orthogonalize T with respect to N
    T = normalize(T-dot(T,N)*N);
    //then retrieve perpendicular vector B with cross product of T and N
    vec3 B = cross(N, T);
    
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    FragPos = vec3(model*vec4(aPos, 1.0));
    TexCoords = aTexCoords;
    TBN = mat3(T, B, N);
}




