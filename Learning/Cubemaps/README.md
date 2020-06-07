## Cubemaps

A texture that contains 6 distinct 2D textures, together forming a cube. They can be indexed/sampled using a direction vector (it's magnitude doesn't matter).

The cubemap can be sampled using the cube's actual position vectors as long as the cube is centered on the origin. So all vertex positions of the cube can be considered as texture coords when sampling the cubemap.

### Creating a cubemap

Each face of a cubemap has a special texture target. Their int values are linearly incremented, starting with GL_TEXTURE_CUBE_MAP_POSITIVE_X.

The clamp-to-edge texture wrapping method is used so OpenGL always return edge values when we sample texels between faces.

### Displaying a skybox

Because a skybox is drawn on a cube we'll need another VAO, VBO and a fresh set of vertices like any other 3D object. 

The incoming local posn vector in the vertex shader is set as the outcoming texture coordinate for interpolated use in the fragment shader.

Since we want the skybox to remain at approx the same distance no matter how far the player moves, we remove the translation part of its view matrix so only rotation affects its position vectors.

The skybox is rendered last. This way, the depth buffer is completely filled with all the scene's depth values so we only have to render the skybox's fragments wherever the early depth test passes, greatly reducing the number of fragment shader calls. 

We need to trick the depth buffer into believing that the skybox has the maximum depth value of 1.0 so that it fails the depth test wherever there's a different object in front of it. We can set the z of the output position equal to its w which will result in a z that is always equal to 1.0 after perspective division is applied.
