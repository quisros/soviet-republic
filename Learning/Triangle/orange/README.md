Graphics pipeline:
- Input: set of 3D coordinates
- Output: colored 2D pixels on screen

Different steps in the pipeline can be executed in parallel.
Programs which execute these some of these steps are called shaders.

Primitives: hints given to OpenGL while calling a drawing command,
which help it understand what to make out of the vertex data provided.
E.g. GL_POINTS, GL_TRIANGLES and GL_LINE_STRIP.

1) Vertex shader
- input: single vertex
- transforms 3D coordinates into different 3D coordinates
- does basic processing on the vertex attributes

2) Primitive assembly
- input: vertex/vertices which forms/form a primitve
- assembles all the point(s) in the primitive shape given

3) Geometry shader

- input: collection of vertices which form a primitive
- can generate other shapes by emitting new vertices to form other primitives

4) Rasterization
- input: resulting primitive(s) from previous step
- the primitive(s) are mapped to the corresponding pixels on the final screen
- fragments are results of this process
- clipping is done to discard fragments outside your view

5) Fragment shader
- fragment: all the data required for OpenGL to render a single pixel
- the shader calculates the final color of the pixel whose corresponding fragment is being processed
- it contains data about the 3D scene like lights, shadows that it can use to calculate the color
- advanced OpenGL effects occur here too

6) Alpha test and blending
- depth and stencil values of fragment checked
- determines whether fragment is in front of/behind other objects
- alpha values which define the opacity of an object also checked
- so some fragments may be discarded, and remaining objects blended
- the final pixel color thus may be different from that calculated in fragment shader
