## Light casters

### Directional light

When a light source is modeled to be infinitely far away it is called a directional light since all its light rays have the same direction; it is independent of the location of the light source.

We can model such a directional light by defining a light direction vector instead of a position vector.  This vector indicates a direction **from** the light source.

The lighting calculations we used so far expect the light direction to be a direction from the fragment towards the light source, but people generally prefer to specify a directional light as a global direction pointing from the light source. 

Note: if we want to define all vectors as vec4s, then:
- if they are position vectors, w component must be 1.0 so translation and projections are properly applied
- if they are direction vectors, w component must be 0.0 so that translations don't have an effect

### Point lights

A point light is a light source with a given position somewhere in a world that illuminates in all directions, where the light rays fade out over distance. 

#### Attenuation

F(att) = 1.0/(Kc + Kl.d + Kq.d^2)

The light will diminish mostly at a linear fashion until the distance becomes large enough for the quadratic term to surpass the linear term and then the light intensity will decrease a lot faster. 

Kc is usually always kept as 1. Kq is smaller than Kl, and as the radial distance that needs to be covered increases, both of them decrease in magnitude.

Note: We could leave the ambient component alone so ambient lighting is not decreased over distance, but if we were to use more than 1 light source all the ambient components will start to stack up. In that case we want to attenuate ambient lighting as well. 

### Spotlight

A spotlight is a light source that is located somewhere in the environment that, instead of shooting light rays in all directions, only shoots them in a specific direction. 

A spotlight in OpenGL is represented by a world-space position, a direction and a cutoff angle that specifies the radius of the spotlight. For each fragment we calculate if the fragment is between the spotlight's cutoff directions and if so, we light the fragment accordingly. 

#### Flashlight

A flashlight is a spotlight located at the viewer's position and usually aimed straight ahead from the player's perspective. 

#### Smooth/soft edges

To create the effect of a smoothly-edged spotlight we want to simulate a spotlight having an inner and an outer cone. Calculated intensity values should then range from 1.0 for fragments inside the  inner cone, to between 1.0 and 0.0 for fragments between the cones, to 0.0 outside the outer cone.

I = (theta-gamma)/epsilon
Where epsilon is the cosine difference between the inner (phi) and outer (gamma) cone.

We use the clamp function to ensure that intensity values calculated lie only in [0,1].
