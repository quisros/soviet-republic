## Basic Lighting

OpenGL's lighting is based approximations of real lighting
using simplified models which are easier to process.

The Phong lighting model has 3 main components:

1. Ambient lighting: from a constant background light source (e.g. moon)
2. Diffuse lighting: simulates directional impact of the light (parts more facing the light source are brighter)
3. Specular lighting: simulates bright spot of source which appears on shiny objects

### Ambient lighting

It is a very simplistic model of global illumination.

On only application of this, the object is quite dark, but not completely,
since ambient lighting is applied.

### Diffuse lighting

The larger the angle between the light ray incident on a fragment and that fragment's normal vector,
the less of an impact the light should have on the fragment's colour.

Directed light ray: direction vector that is the difference between the 
light's position vector and the fragment's position vector.

Since a vertex by itself has no surface, we retrieve a normal vector by using its surrounding vertices 
to figure out the surface of the vertex. We can calculate the normal vectors for all the cube's vertices 
by using the cross product, but not required for a relatively simple shape.

Since lighting calculations are done in world space, we want vertex positions in world space first 
in order to get the fragment positions. This can be done by multiplying the vertex position attribute 
with only the model matrix.

Normalizing relevant vectors during lighting calculations is important.

While calculating the diffuse component, we use the max function in dot product calculation 
to ensure that the component doesn't become negative, as lighting for negative colors is not really defined.

#### Bringing normal vectors into worldspace

Normal vectors are only direction vectors and do not represent a specific position in space. 
Also, translations should not have any effect on the normal vectors. 

Second, if the model matrix would perform a non-uniform scale, 
the vertices would be changed in such a way that the normal vector is not perpendicular to the surface anymore.

To fix these problems, we use a normal matrix - the transpose of the inverse of the upper-left
3x3 part of the model matrix. Since we are working in world space and not view space, we derive the model matrix
from the model matrix and not the model-view matrix.

### Specular lighting

It depends on the view direction as well. The closer our viewing angle is to the angle at which the reflected ray travels,
the stronger the specular lighting effect is.

The reflect function expects the first vector to point from the light source towards the fragment's position.

The higher the shininess value of an object, the more it properly reflects the light instead of scattering it all around 
and thus the smaller the highlight becomes. 
