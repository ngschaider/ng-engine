#pragma once

#include "resource_manager.h"
#include "shader.h"
#include "stb_image.h"

std::vector<LoadedShader> ResourceManager::loadedShaders;
std::map<std::string, Texture2D*> ResourceManager::loadedTextures;

ResourceManager::ResourceManager() {

}

/**
* Deallocates and cleans up all the memory used by resources loaded by the ResourceManager
*/
void ResourceManager::clear() {
	for (LoadedShader l : ResourceManager::loadedShaders) {
		delete l.shader;
	}
	for (std::pair<std::string, Texture2D*> tex : ResourceManager::loadedTextures) {
		delete tex.second;
	}
}

Shader* ResourceManager::loadShader(const std::string vertexShaderFile, const std::string fragmentShaderFile) {
	for (LoadedShader l : ResourceManager::loadedShaders) {
		if (l.vertexShaderFile == vertexShaderFile && l.fragmentShaderFile == fragmentShaderFile) {
			return l.shader;
		}
	}

	Shader* shader = new Shader(vertexShaderFile.c_str(), fragmentShaderFile.c_str());
	ResourceManager::loadedShaders.push_back({ vertexShaderFile, fragmentShaderFile, shader });
	return shader;
}

Texture2D* ResourceManager::loadTexture(const std::string file, bool alpha) {
	if (ResourceManager::loadedTextures.count(file) == 0) {
		int width, height, numChannels;
		unsigned char* data = stbi_load(file.c_str(), &width, &height, &numChannels, 0);

		Texture2D* tex = new Texture2D();
		tex->generate(Vector2i(width, height), data);

		ResourceManager::loadedTextures[file] = tex;
	}
	
	return ResourceManager::loadedTextures[file];
}