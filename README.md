# ng-engine

A small game engine, developed to learn more about C++, engine architecture and computer graphics.


I tried to document everything well, so please have a look at the code comments. 

## Used libraries

All dependencies are contained in the "Dependencies" directory. The libraries currently used by the project are:

- [GLFW](https://github.com/glfw/glfw) - Window Management and Input System
- [glad](https://github.com/Dav1dde/glad) - OpenGL bindings
- [FreeType](http://freetype.org/) - Font Loading
- [Dear ImGui](https://github.com/ocornut/imgui) - Debug Rendering and Debugging Utilities

## Core Architecture

The core consists of the following classes:
- Engine - Hosts the main loop and owns zero or one scene
- Scene - Owns a zero or more game objects
- GameObject - Owns one  or more components

The engine (usually only one is required per application) invokes the update/fixedUpdate methods on the scene.
The scene invokes these methods on it's enabled game objects.
The game object invokes these methods on it's enabled components.

Therefore, core objects relay the core signals (earlyUpdate, update, lateUpdate, fixedUpdate) to the hierarchy objects it owns.

## The Hierarchy

Each game object MUST hold a specific component called Transform. This component is automatically added to the game obejct on instantiation.
Each transform component can hold a reference to another transform representing the game object's parent in the hierarchy.

## Spaces / Coordinate Systems

The following spaces (or coordinates systems, if you will) are defined and used:
- Local - 3-dimensional, relative to the game object's parent
- World (or Global, or Model) - 3-dimensional, relative to the world origin
- Camera (or View, or Eye) - 3-dimensional, relative to the scene's active camera
- Clip - 2-dimensional, projected version of the camera's view, ranging from -1 to +1
- Screen (or Window) - 2-dimensional, units in this coordinate system represent pixels on screen relative to the window origin (bottom-left)

The transformation between local and world space is defined by the transform component.
The transformation between world and camera space is defined by the scene's active camera.
The transformation between camera and clip space is defined by the scene's active camera.
The transformation between clip and screen space is defined by the rendering system.
