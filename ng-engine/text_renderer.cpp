#include "text_renderer.h"
#include "resource_manager.h"
#include "vector2i.h"
#include "resource_manager.h"

TextRenderer::TextRenderer() : TextRenderer("") {
}

TextRenderer::TextRenderer(std::string text) : font(ResourceManager::arial()), text(text) {
	this->shader = ResourceManager::loadShader("text2d_vertex.glsl", "text2d_fragment.glsl");
	this->text = text;

	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(glGetAttribLocation(this->shader->id, "vertex"));
	glVertexAttribPointer(glGetAttribLocation(this->shader->id, "vertex"), 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void TextRenderer::render() {
	this->shader->use();

	this->shader->setMatrix4x4("transformationMatrix", this->getTransformationMatrix());
	this->shader->setVector3("textColor", Vector3(this->color.r() / 255.0f, this->color.g() / 255.0f, this->color.b() / 255.0f));

	glBindVertexArray(this->VAO);

	glActiveTexture(GL_TEXTURE0);

	float x = 0;

	for (std::string::const_iterator c = text.begin(); c != text.end(); c++) {
		// Character ch = this->characters[*c];

		std::map<char, LoadedCharacter>::iterator it = this->font->characters.find(*c);
		if (it == this->font->characters.end()) throw new std::exception();

		LoadedCharacter ch = (*it).second;

		float xPos = ch.bearing.x() + x;
		float yPos = -ch.size.y() + ch.bearing.y();

		float w = ch.size.x();
		float h = ch.size.y();

		float vertices[6][4] = {
			{ xPos, yPos + h, 0.0f, 0.0f },
			{ xPos, yPos, 0.0f, 1.0f },
			{ xPos + w, yPos, 1.0f, 1.0f },

			{ xPos, yPos + h, 0.0f, 0.0f },
			{ xPos + w, yPos, 1.0f, 1.0f },
			{ xPos + w, yPos + h, 1.0f, 0.0f },
		};

		glBindTexture(GL_TEXTURE_2D, ch.textureId);

		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		x += ch.advance >> 6;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}