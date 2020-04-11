## SOC OpenGL: Assignment 2

Operating System : OSX 

Libraries: GLFW 3.3 and GLEW 2.1

### Directory structure and description

Each problem folder contains:

- cpp code for each subquestion
- the shaders and textures used in the respective subfolders
- a readymade makefile for linking the libraries
- exe file in the bin subfolder (to run use bin/./filename)
- header files in the utility subfolder

### Usage instructions

The glm folder (downloaded from https://glm.g-truc.net/0.9.8/index.html) containing the required header files must be present in the system's 'include' folder.

#### Problem 1

- use W/S/A/D keys to move forward/backward/left/right
- move the mouse to change the viewing angle
- scroll to zoom in or out

#### Problem 2

Same instructions as problem 1.

#### Problem 3

Same intstructions as problem 1, plus:

- use the B key to toggle between Phong and Blinn-Phong shading
- the initial state of the program uses directional lighting; use P/O/I keys to switch to point light source/flashlight/directional lighting respectively
- note: to clearly observe the difference between Phong and Blinn-Phong shading in point light and spotlight mode, one must move the camera to very close to the cube's surface
