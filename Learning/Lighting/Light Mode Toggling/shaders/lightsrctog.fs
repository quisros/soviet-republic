#version 330 core

in vec3 FragPos;
in vec2 TexCoords;
in mat3 TBN;

out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normalMap;
    float shininess;
};


struct DirLight {
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);



struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
#define NR_POINT_LIGHTS 1

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);



struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutoff;
    float outerCutoff;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);


uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform vec3 viewPos;

uniform bool blinn;
uniform bool dirnl;
uniform bool flash;
uniform bool point;



void main()
{
    //properties
    vec3 norm = vec3(texture(material.normalMap, TexCoords).rgb);
    norm = norm*2.0-1.0;
    norm = normalize(TBN*norm);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    vec3 result = norm*0.0;
    
    if(dirnl) {
        //directional lighting implemented
        result += CalcDirLight(dirLight, norm, viewDir);
    }
    
    else if(point) {
        //point light(s) implemented
        for (int i = 0; i<NR_POINT_LIGHTS; i++) {
            result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
        }
    }
    
    else if(flash) {
        //spotlight implemented
        result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
    }
    
    FragColor = vec4(result, 1.0);
    
}


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    
    vec3 lightDir = normalize(-light.direction);
    
    //diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    
    //specular shading
    float spec = 0.0;
    if (blinn) {
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess*2.5f);
    }
    else {
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    }
    
    //combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    
    return (ambient + diffuse + specular);
    
}


vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    
    vec3 lightDir = normalize(light.position - fragPos);
    
    //diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    
    //specular shading
    float spec = 0.0;
    if (blinn) {
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    }
    else {
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    }
    
    
    //attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0/(light.constant + light.linear*distance + light.quadratic*(distance*distance));
    
    //combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
    
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    
    //creating a smooth edge flashlight
    
    vec3 lightDir = normalize(light.position-fragPos);
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutoff - light.outerCutoff;
    float intensity = clamp((theta-light.outerCutoff)/epsilon, 0.0, 1.0);
        
    //ambient section
    
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
        
    //diffuse section
        
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    diffuse  *= intensity;
        
    //specular section
    float spec = 0.0;
    if (blinn) {
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    }
    else {
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    }
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    specular *= intensity;
        
    //obtaining final color

    return (ambient + diffuse + specular);
    
}




