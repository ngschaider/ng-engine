#pragma once

#include "shader.h"
#include "font.h"
#include "texture_2d.h"
#include "component.h"
#include <vector>
#include <map>

typedef struct {
	const std::string vertexShaderFile;
	const std::string fragmentShaderFile;
	Shader* shader;
} LoadedShader;

class ResourceManager : Component {
private:
	static std::vector<LoadedShader> loadedShaders;
	static std::map<std::string, Texture2D*> loadedTextures;
	static std::map<std::string, Font*> loadedFonts;
	ResourceManager() = delete;
public:
	static Shader* loadShader(const std::string vertexShaderFile, const std::string fragmentShaderFile);
	static Texture2D* loadTexture(const std::string file, bool alpha);
	static Font* loadFont(const std::string file);
	static void clear();

	static Font* arial();
};