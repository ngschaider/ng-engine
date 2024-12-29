#pragma once

#include "shader.h"
#include "font.h"
#include "texture_2d.h"
#include "component.h"
#include <vector>
#include <map>

/**
* Holds a shader program and information from where it got loaded.
*/
typedef struct {
	const std::string vertexShaderFile; // path to the file containing the vertex shader program
	const std::string fragmentShaderFile; // path to the file containing the fragment shader program
	Shader* shader; // The compiled shader program
} LoadedShader;

/**
* The resource manager helps to ensure resources (shaders, textures, fonts) can be loaded from anywhere while all callers share the same instance when
* requesting the same resource.
*/
class ResourceManager : Component {
private:
	/**
	* Holds information about all loaded shaders
	*/
	static std::vector<LoadedShader> loadedShaders;

	/**
	* Holds information about all loaded textures
	*/
	static std::map<std::string, Texture2D*> loadedTextures;

	/**
	* Holds information about all loaded fonts
	*/
	static std::map<std::string, Font*> loadedFonts;

	ResourceManager() = delete; // 100% static
public:
	/**
	* Loads and returns a shader using the given paths to the vertex and fragment shader source.
	* If a shader from these sources has already been loaded, the already loaded shader is returned instead.
	*/
	static Shader* loadShader(const std::string vertexShaderFile, const std::string fragmentShaderFile);

	/**
	* Loads and returns a texture using the given path.
	* If a texture from this path has already been loaded, the already loaded shader is returned instead.
	*/
	static Texture2D* loadTexture(const std::string file);

	/**
	* Loads and returns a font using the given path.
	* If a font from this path has already been loaded, the already loaded shader is returned instead.
	*/
	static Font* loadFont(const std::string file);

	/**
	* Deallocates and cleans up all the memory used by resources loaded by the resource managers and clears cache.
	*/
	static void clear();

	/**
	* Loads and returns the font "Arial" from Window's default font path.
	* If the font has already been loaded, the loaded instance is returned.
	*/
	static Font* arial();
};