#pragma once

#include "../Components/Component.h"
#include "Actor.h"
#include <glm/fwd.hpp>

class Text_Actor : public Actor {

public:
	Text_Actor(Component* parent_);
	~Text_Actor();

	bool onCreate(const char* vShader, const char* fShader, std::string textFile, unsigned int fontSize);
	void onDestroy();
	void update(const float deltaTime_);
	void input();
	void draw(glm::mat4 projection, std::string text, float xpos, float ypos, float scale = 0.5f,
		       	float r = 0.0f, float g = 1.0f, float b = 0.0f) const;

private:
	//float red;
	//float green;
	//float blue;

};
