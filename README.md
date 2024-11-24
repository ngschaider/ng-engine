This is ng-engine. A small game engine, developed to learn more about C++, engine architecture 
and computer graphics.


Architecture description:
The engine relies heavily on object composition and also on inheritance and polymorphism.

The root object of the project is the Engine. 
It holds a reference to a scene (which can change during run-time).

The Scene class contains a list of GameObject instances.

The GameObject class contains a list of Component instances.

The Component class itself does not do much but instead relies on being sub-classed.

