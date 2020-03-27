Rendering pipeline overview

1. Vertex specification
2. Vertex shader
3. Tessellation
4. Geometry shader
5. Vertex post-processing
6. Primitive assembly
7. Rasterization
8. Fragment shader
9. Per-sample operations

A) Vertex specification

Vertices define boundaries of a primitive: shapes like triangles, Fs, etc.

Vertex array objects: define what data each vertex has
Vertx buffer objects: store the actual vertex data

Vertex data: series of attributes, need not be position. 
Once it is specified, primitive is rendered by drawing command.

B) Vertex processing

Shader operation: a certain stage/kind of vertex processing. 

Vertex shader: one-one mapping of input vertex to output vertex. 
Performs basic processing on each vertex via user-defined program.

Tessellation: subdividing a patch of vertex data into smaller primitives, 
and computing vertex data for the new vertices generated. 
Ensures continuity across patches. (optional)

Geometry shader: takes single primitve input, outputs zero or more primitives. 
E.g. points to triangle, line to points. (optional)

C) Vertex post-processing

Fixed, not user defined.

Transform feedback: prev step outputs written to a series of buffer objects
Clipping: splitting boundary primitives into smaller parts so the final result lies within defined volume

D) Primitive assembly

Input: run of vertex data from prev stages
Output: ordered sequence of simple primitives

Face culling: avoids rendering of triangles facing away from user

E) Rasterization

Input: primitives generated in prev stage
Output: sequence of fragments 
Fragment: set of state used to compute final data for pixel

F) Fragment processing

Done by fragment shader.
Output: list of colors for each color buffer being written to, 
and a depth value + stencil value 
(no shader then these two get their default value)

G) Per-sample operations

First, sequence of culling tests - if fragment fails one, pixel not updated.
Then color blending: operation b/w current and new color.
Last, fragment data is written to the frame buffer.
