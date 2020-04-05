### Camera space

View matrix: transforms world coords into coords which are relative to camera's posn and dirn

To define a camera, we need:
- its position in world space
- the direction it's looking at
- a vector pointing to its right
- a vector pointing upwards from it

Subtracting the camera position vector from the scene's origin vector results in the camera direction vector. 
For the view matrix's coordinate system we want its z-axis to be positive, 
and because by convention (in OpenGL) the camera points towards the negative z-axis we want to negate the direction vector. 
If we switch the subtraction order around we now get a vector pointing towards the camera's positive z-axis:

So the camera direction vector actually points in the reverse direction of what it is targeting,
i.e. from the target to the camera.

Right vector is obtained by crossing an up vector (upwards in world space) with the direction vector.
Camera up vector obtained by crossing camera direction vector with right vector.

### Look at

LookAt matrix transforms any vector to the coordinate space defined by above three vectors.
LookAt = [4x4 identity with upper left 3x3 as R(row1), U(row2), D(row3)]
*[4x4 identity with top three of col 4 as negative camera posn vector]

glm::lookAt creates a lookAt matrix/view matrix with
- first arg: camera posn vector
- second arg: camera target posn vector
- third arg: worldspace up vector

## Walk around

Define a cameraFront vector which is used to ensure that direction vector 
always remains constant (here in e.g. the negative of it).

Normalizing the 'right' vector created for sideways camera movement is necessary
as otherwise we would move slow or fast based on camera's orientation instead of
at a consistent movement speed.

Some machines render faster than others. To balance out camera velocities across
hardware, deltaTime value is used (time taken to render the just previous frame).

### Look around

Euler angles
- Pitch: up or down angle
- Yaw: left or right angle
- Roll: roll like planes doo

For our camera system, only need pitch and yaw value. 
These will be used to form a 3D vector that represents a new direction vector.

Pitch and yaw obtained from mouse movement: last frame's mouse positions are stored,
and in the current frame, it is calculated how much the mouse values have changed.

Capturing a cursor means that, once the application has focus, the mouse cursor 
stays within the center of the window (unless the application loses focus or quits).

When handling mouse input for an fly style camera there are several steps we have to take before we're able to fully calculate the camera's direction vector:

Calculate the mouse's offset since the last frame.
Add the offset values to the camera's yaw and pitch values.
Add some constraints to the minimum/maximum pitch values.
Calculate the direction vector.

### Zoom

Field of view or fov largely defines how much we can see of the scene. 
When the field of view becomes smaller, the scene's projected space gets smaller. 
This smaller space is projected over the same NDC, giving the illusion of zooming in. 
