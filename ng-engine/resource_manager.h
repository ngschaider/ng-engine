#pragma once

#include "shader.h"
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
	ResourceManager(); // 100% static classs
public:
	static Shader* loadShader(const std::string vertexShaderFile, const std::string fragmentShaderFile);
	static Texture2D* loadTexture(const std::string file, bool alpha);
	static void clear();
};