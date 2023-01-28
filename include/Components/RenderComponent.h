#pragma once

#include <cstdint>
#include <cstdio>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include <map>


#include "Component.h"
#include "../Graphics/sprite.h"
#include "../Graphics/texture.h"
#include <memory>






class RenderComponent : public Component
{
	private:
		std::shared_ptr<sprite> smart_sprite;
		unsigned int VBO, VAO;
 		unsigned int quadVAO;
		std::shared_ptr<Texture2D>  texture;

	
	
	public:
		RenderComponent(Component* parent_ );
		~RenderComponent();
		void onDestroy() override{
			printf("Deleting VAO\n");
			glDeleteVertexArrays(1, &this->quadVAO);
			glDeleteVertexArrays(1, &this->VAO);
			glDeleteBuffers(1, &VBO);
		}
		void update(const float delta) override{}
		void draw() const override;

		void initLineRenderData(vec2 start, vec2 end);
		bool onCreate() override;
		void initRenderData();
		void renderData(uint8_t num_x_frame,uint8_t num_y_frames, uint8_t x_frame, uint8_t y_frame);

		void LoadTexture(const char* fileName)
		{
			sprite s;
			texture = s.loadSmartTexture(fileName, true);
		}
		
		std::shared_ptr<Texture2D> get_texture(){return texture;}
	

		void LoadSprite(
		       const char* fileName,
		       vec2 position, 
		       vec2 size, 
		       unsigned int x_frame = 0, 
		       unsigned int y_frame = 0, 
		       float rotation = 0.0f, 
		       vec3 colour = vec3(1.0f), 
		       vec2 frames = vec2(1.0f),
			   bool isAlpha = true);

		void LoadTiles(
			std::shared_ptr<Texture2D> texture,
		       vec2 position, 
		       vec2 size, 
		       unsigned int x_frame = 0, 
		       unsigned int y_frame = 0, 
		       float rotation = 0.0f, 
		       vec3 colour = vec3(1.0f), 
		       vec2 frames = vec2(1.0f));

		void drawSquare();
		void drawSprites();
		void drawLine();
		void drawLine(glm::vec2 origin, glm::vec2 dest);
		void drawTexture(Texture2D& );
		std::shared_ptr<sprite> get_sprite(){return smart_sprite;}




};

