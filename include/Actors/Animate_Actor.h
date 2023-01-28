#pragma once

#include "../Components/Component.h"
#include "Actor.h"
#include <glm/fwd.hpp>
#include <memory>


class Texture_Actor;
class Shader_Actor;
class Animate_Actor: public Actor {

public:
	Animate_Actor(Component* parent_);
	~Animate_Actor();

	//bool onCreate();
	bool onCreate(const char* fileName, glm::vec2 position, glm::vec2 size, int numXFrames, int numYFrames, float rotate, glm::vec3 colour, glm::vec2 currentFrame, bool isAlpha);
	void onDestroy();
	void update(const float deltaTime_);
	void input();
	void draw(std::shared_ptr<Shader_Actor> shader, glm::mat4 projection, float xpos, float ypos, float boxWidth, float bowHeight, float rot) const;

	std::vector<std::shared_ptr<Texture_Actor>> getAnimation(){return animation;}

private:

	double animation_last_time;
	int curr_frame;
	int animation_frame;
	int max_frame;

	std::vector<std::shared_ptr<Texture_Actor>> animation;
	std::shared_ptr<Texture_Actor> texture;

};
