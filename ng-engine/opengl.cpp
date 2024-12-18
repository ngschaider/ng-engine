#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include "vector3.h"
#include <map>
#include "color.h"
#include "matrix4x4.h"
#include "shader.h"
#include <ft2build.h>
#include FT_FREETYPE_H

//std::map<char, Character> loadCharacters() {
//	FT_Library ft;
//	if (FT_Init_FreeType(&ft)) {
//		throw new std::exception("Could not init FreeType Library");
//	}
//
//	std::map<char, Character> characters;
//
//	FT_Face face;
//	if (FT_New_Face(ft, "C:/Windows/Fonts/arial.ttf", 0, &face)) {
//		throw new std::exception("Failed to load font");
//	}
//
//	FT_Set_Pixel_Sizes(face, 0, 48);
//
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//	for (unsigned char c = 0; c < 128; c++) {
//		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
//			throw new std::exception("Failed to load glyph");
//		}
//
//		unsigned int texture;
//		glGenTextures(1, &texture);
//		glBindTexture(GL_TEXTURE_2D, texture);
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		Character character = {
//			texture,
//			Vector2(face->glyph->bitmap.width * 1.0f, face->glyph->bitmap.rows * 1.0f),
//			Vector2(face->glyph->bitmap_left, face->glyph->bitmap_top),
//			(int)face->glyph->advance.x
//		};
//		characters.insert(std::pair<char, Character>(c, character));
//
//	}
//
//	FT_Done_Face(face);
//	FT_Done_FreeType(ft);
//
//	return characters;
//}




//
//void OpenGL::text(std::string text) {
//	this->textShader->use();
//
//	this->textShader->setMatrix4x4("projection", this->transformationMatrix);
//	
//	GLint vertexAttribLoc = glGetAttribLocation(this->textShader->id, "vertex");
//
//	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 6, nullptr, GL_DYNAMIC_DRAW);
//
//	glEnableVertexAttribArray(vertexAttribLoc);
//	glVertexAttribPointer(vertexAttribLoc, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	this->textShader->setVector3("textColor", Vector3(255, 0, 0));
//
//	glActiveTexture(GL_TEXTURE0);
//
//	float x = 0;
//
//	for (std::string::const_iterator c = text.begin(); c != text.end(); c++) {
//		Character ch = this->characters[*c];
//
//		float xPos = ch.bearing.x() + x;
//		float yPos = -ch.size.y() + ch.bearing.y();
//
//		float w = ch.size.x();
//		float h = ch.size.y();
//
//		float vertices[6][4] = {
//			{ xPos, yPos + h, 0.0f, 0.0f },
//			{ xPos, yPos, 0.0f, 1.0f },
//			{ xPos + w, yPos, 1.0f, 1.0f },
//
//			{ xPos, yPos + h, 0.0f, 0.0f },
//			{ xPos + w, yPos, 1.0f, 1.0f },
//			{ xPos + w, yPos + h, 1.0f, 0.0f },
//		};
//
//		glBindTexture(GL_TEXTURE_2D, ch.textureId);
//
//		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
//		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
//
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//
//		x += ch.advance >> 6;
//	}
//
//	glBindTexture(GL_TEXTURE_2D, 0);
//}

//void OpenGL::triangle() {
//	Vector3 vertices[] = {
//		Vector3(-0.5f, -0.5f, 0.0f),
//		Vector3(0.5f, -0.5f, 0.0f),
//		Vector3(0.0f, 0.5f, 0.0f),
//	};
//
//	std::vector<Vector3> verticesAsVector = std::vector<Vector3>(vertices, vertices + sizeof(vertices) / sizeof(vertices[0]));
//	this->draw(verticesAsVector, GL_TRIANGLES);
//}
//
//void OpenGL::cube() {
//	Vector3 vertices[] = {
//		Vector3(-0.5f, 0.5f, 0.5f), // left top front
//		Vector3(0.5f, 0.5f, 0.5f), // right top front
//		Vector3(-0.5f, -0.5f, 0.5f), // left bottom front
//		Vector3(0.5f, -0.5f, 0.5f), // right bottom front
//		Vector3(0.5f, -0.5f, -0.5f), // right bottom back
//		Vector3(0.5f, 0.5f, 0.5f), // right top front
//		Vector3(0.5f, 0.5f, -0.5f), // right top back
//		Vector3(-0.5f, 0.5f, 0.5f), // left top front
//		Vector3(-0.5f, 0.5f, -0.5f), // left top back
//		Vector3(-0.5f, -0.5f, 0.5f), // left bottom front
//		Vector3(-0.5f, -0.5f, -0.5f), // left bottom back
//		Vector3(0.5f, -0.5f, -0.5f), // right bottom back
//		Vector3(-0.5f, 0.5f, -0.5f), // left top back
//		Vector3(0.5f, 0.5f, -0.5f), // right top back
//	};
//
//	this->transformationMatrix = Matrix4x4::identity();
//
//	std::vector<Vector3> verticesAsVector = std::vector<Vector3>(vertices, vertices + sizeof(vertices) / sizeof(vertices[0]));
//	this->draw(verticesAsVector, GL_TRIANGLE_STRIP);
//}
//
