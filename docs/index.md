# Program Structure
game_engine.cpp
---------------
This is the main running code it contains many of the global data variables and runs the main game instance.

block.cpp
---------

This is the source file containing the logic surrounding blocks and chunks. The main world is handled here. Every frame the world object is called and it draws each block using mesh.cpp

camera.cpp
----------

This source file handles the camera and shader uniforms. It sets up the perspictive camera using void initCam(...) and the camera is rotated using void rotate_cam(...);

display.cpp
-----------
This source file sets up the opengl instance with int initDisplay(...) and updates it with void updateDisplay();

mesh.cpp
--------
This source file sends the mesh to opengl and tells opengl how and whick mesh to run.

loadfile.cpp
------------
Very simple file with one method (std::string loadFile(std::string filedir)) that loads a file specified by file dir and returns a std::string with the file contents

stb_image.c
-----------
A file not created by me that loads images.

texture.cpp
-----------
Handles the textures and sends them to opengl.

world_gen.cpp
-------------
Generates world. 



