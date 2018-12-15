

# Introduction
The goal of this project is to create a space scene. The scene will be inside a skybox. The scene will also contain asteroids objects loaded from OBJ files. For shaders, the asteroid will be using Physically Based Rendering (PBR) shaders using Image Based Lighting (IBL) technique and emission mapping. The scene also contains two source of lighting, one white and another red. The two lightsource move around an orbit, the white clockwise, the red counterclockwise. The asteroids are animated in two ways. The emission glow fades in and out and the asteroid rotates in place, each around different axes and directions. To navigate this scene, keyboard and mouse controls are used in First Person Shooter (FPS) fashion, in addition to click and drag camera.

# Requirements
In addition to all the OpenGL libraries provided by the course, one additional library is required. The project requires the OpenGL Utility Toolkit (GLUT). Since the original GLUT was abandon is not under an open source license and hasn’t been updated since 1998, a free distribution version, last updated in 2015, was used called FreeGLUT. FreeGLUT needs to be compile by and setup the same way as the other libraries.

# SkyBox
The Skybox is just a simple cube primitive with six textures applied to the inside. In order to maintain the illusion of infinite space within the skybox, the object is place and moves with the camera.

# Asteroids
Five asteroid objects are loaded into the scene. The objects come from an OBJ file. All asteroids have different position, scales, and rotate in different directions.

# Light Source
There are two traditional light source, a white and a red source. The move in a circular orbit, white goes clockwise, red goes counterclockwise, on the XZ plane. Because of the shader been used, the skybox’s texture is used as a light source as well using a technique called IBL. This technique takes the skybox’s texture, blurs it, and applies it to reflecting object in the same way as environment mapping. This blurred environment map is called irradiance map.

# PBR Shader
The PBR is a technique used to make graphical objects appear hyper-realistic by combining several types of texture mapping. The implementation I uses requires albedo (diffused), normal, metallic, roughness, ambient occlusion, specular, emission, and irradiance mapping.

# Navigation
The FPS style camera controls are as follows:
* Keyboard Controls:
W: Forward
S: Backward
A: Left Strafe
D: Right Strafe
* Mouse Controls:
Left Click and Drag:
Pitch and Yaw
Right Click and Drag:
Drag camera up, down, left, and right

# Animation
There are three animation in the scene. The first is the emission glow of the asteroids. The emission glow fades in and out in a mostly linear style with a small plateau after it fades out before fading back in. 
The second animation is the asteroids rotation. Each asteroid rotates around different axes and different speeds without translation. 
The third animation is the light sources rotating in their own orbits around the scene. They are both rotating independent orbits on the XZ plane and in opposite directions. They use a simple circle trigonometry to move.
