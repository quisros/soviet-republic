### Blinn-Phong shading

Specular reflections in Phong shading break down when the shininess property is low, resulting in a large (rough) specular area.

When the angle between the view and reflection vector is larger than 90 degrees, the specular contribution gets nullified. This can be a problem if we use a low specular exponent, as the specular radius is then large enough that is should have a contribution under these contribution.

In the Blinn-Phong model, we use a **halfway vector**: a unit vector exactly halways between the view and light direction. The closer this halfway vector aligns with the surface's normal vector, the higher the specular contribution.

Another subtle is that the angle between the halfway vector and the surface normal is often shorter than the angle between the view and reflection vector. So to get visuals similar to Phong shading the specular shininess exponent has to be set a bit higher. A general rule of thumb is to set it between 2 and 4 times the Phong shininess exponent.
