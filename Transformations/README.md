### Scalar vector operations
Adding/subtracting a vector with a scalar:
add/subtract each element of the vector with/by the scalar.

### Scaling a vector:
multiply by 4x4 matrix diag(s1, s2, s3, 1).

### Translation:
multiply by 4x4 identity matrix with top 3 values of 4th column as (tx, ty, tz).

### Homogenous coordinates:
To get the 3D vector from a homogeneous vector we divide the x, y and z coordinate by its w coordinate. 
Whenever the homogeneous coordinate is equal to 0, the vector is specifically known as a direction vector 
since a vector with a w coordinate of 0 cannot be translated.

### Rotations:
Rotations in 3D are specified with an angle and a rotation axis.
For rotation around an axis, take identity matrix, block out the row and column corresponding to it
and recreate normal 2D rotation matrix in the remaining main 3x3 section of the transformation matrix.

Since matrix multiplication is not commutative, it is advised to first 
do scaling, then rotation and lastly translation when combining (though obviously depends), 
otherwise the transformations could negatively affect each other.

### In practice
A mat4 declared but not initialized is the null matrix.

Common first argument to given three functions is name of matrix.
- glm::translate: second arg: 3D vector to be translated by
- glm::rotate: second arg: rotation angle in rad, third arg: 3D unit vector giving rotation axis
- glm::scale: second arg: 3 diagonal elements of scaling matrix

glUniformMatrix4fv fn
- first arg: uniform's location
- second arg: how many matrices being sent
- third arg: do we want to transpose matrix
- fourth arg: actual matrix data, converted from GLM's usual format to meet OpenGL's expectations
