## Materials

Each material has a different reaction to light.
When describing a surface we can define a material color for each of the 3 lighting components: 
ambient, diffuse and specular lighting.
By specifying a color and shininess for each of the components,
we have fine-grained control over the final appearance of the surface.

- The ambient material vector defines what color the surface reflects under ambient lighting (usually the same as the surface's color). 

- The diffuse material vector defines the color of the surface under diffuse lighting. It is set to the desired surface's color. 

- The specular material vector sets the color of the specular highlight on the surface (or possibly even reflect a surface-specific color). 

- The shininess impacts the scattering/radius of the specular highlight.

### Light properties

A light source has a different intensity for its ambient, diffuse and specular components. 

The ambient light is usually set to a low intensity because we don't want the ambient color to be too dominant. 
The diffuse component of a light source is usually set to the exact color we'd like a light to have; often a bright white color. 
The specular component is usually kept at vec3(1.0) shining at full intensity.
