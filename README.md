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

## View Spaces

The following spaces (or coordinates systems, if you will) are defined:
- Local
- World (previously called Global)
- Camera
- Clip
- Screen

The transformation between local and world space is defined by the transform component.
The transformation between world and camera space is defined by the scene's first active camera.
The transformation between camera and clip space is defined by the scene's first active camera.
The transformation between clip and screen space is defined by the rendering system.
