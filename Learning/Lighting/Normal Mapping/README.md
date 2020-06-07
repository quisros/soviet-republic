## Normal mapping

From the lighting technique's point of view, the only way it determines the shape of an object is by its perpendicular normal vector. By using per-fragment normals we can trick the lighting into believing a surface consists of tiny little planes (perpendicular to the normal vectors) giving the surface an enormous boost in detail.

To enable us to use the same normal map, regardless of orientation, we use a coordinate space called the tangent space, where the normal map vectors always point towards the positive z direction; all other lighting vectors are then transformed relative to this positive z direction.

### Tangent space

Tangent space is a space that's local to the surface of a triangle: the normals are relative to the local reference frame of the individual triangles. Using a specific matrix we can then transform normal vectors from this local tangent space to world or view coordinates, orienting them along the final mapped surface's direction.

Such a matrix is called a TBN matrix where the letters depict a Tangent, Bitangent and Normal vector. These are the vectors we need to construct this matrix. To construct it, we need three vectors: up, right and forward.

- tangent ~ right
- bittangent ~ forward
- normal ~ up

We can calculate tangents and bitangents from a triangle's vertices and its texture coordinates (since texture coordinates are in the same space as tangent vectors) .

We transform all the TBN vectors to the coordinate system we'd like to work in, which in this case is world-space as we multiply them with the model matrix. 

There are two ways we can use a TBN matrix for normal mapping:

1. We take the TBN matrix that transforms any vector from tangent to world space, give it to the fragment shader, and transform the sampled normal from tangent space to world space using the TBN matrix; the normal is then in the same space as the other lighting variables.

2. We take the inverse of the TBN matrix that transforms any vector from world space to tangent space, and use this matrix to transform not the normal, but the other relevant lighting variables to tangent space; the normal is then again in the same space as the other lighting variables.

Using a mathematical trick called the Gram-Schmidt process, we can re-orthogonalize the TBN vectors such that each vector is again perpendicular to the other vectors. 
