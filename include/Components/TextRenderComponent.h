#pragma once

#include <cstdio>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <map>

#include "Component.h"
#include <memory>


#include <ft2build.h>
#include FT_FREETYPE_H



/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // size of glyph
    glm::ivec2   Bearing;   // offset from baseline to left/top of glyph
    unsigned int Advance;   // horizontal offset to advance to next glyph
};



class TextRenderComponent : public Component
{
	public:
		 // holds a list of pre-compiled Characters
    		std::map<char, Character> Characters; 


		TextRenderComponent(Component* parent_ );
		~TextRenderComponent();
		bool onCreate() override;
		void onDestroy() override{
			printf("Deleting Text VAO\n");
//			glDeleteVertexArrays(1, &this->quadVAO);
			glDeleteVertexArrays(1, &this->VAO);
			glDeleteBuffers(1, &VBO);
		}
		void update(const float delta) override{}

    		// pre-compiles a list of characters from the given font
    		void Load(std::string font, unsigned int fontSize);
    		// renders a string of text using the precompiled list of characters
    		//void RenderText(std::string text, float x, float y, float scale ,glm::mat4 matrix, glm::vec3 color = glm::vec3(1.0f));
    		void RenderText(std::string text, float x, float y, float scale);
		void draw() const override;


	private:
		 // render state
    		unsigned int VAO, VBO;

};
