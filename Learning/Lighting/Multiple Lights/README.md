## Multiple lights

To use more than one light source in the scene we want to encapsulate the lighting calculations into GLSL functions. 

When using multiple lights in a scene the approach is usually as follows: we have a single color vector that represents the fragment's output color. For each light, the light's contribution to the fragment is added to this output color vector. So each light in the scene will calculate its individual impact and contribute that to the final output color.
