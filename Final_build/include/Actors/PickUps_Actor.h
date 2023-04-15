#pragma once

#include "../Components/Component.h"
#include "Actor.h"
#include "Texture_Actor.h"
#include <glm/fwd.hpp>
#include <memory>
#include <box2d/box2d.h>

class Shader_Actor;
class Texture_Actor;

class PickUps_Actor : public Actor {


public:
	PickUps_Actor (Component* parent_);
	~PickUps_Actor ();

	void InitalizeActor(const char* fileName, 
						b2World *world,
						glm::vec2 positon,
						glm::vec2 size,
						glm::vec2 boxSize,
						int totalXFrames,
						int totalYFrames,
						int currentXFrame,
						int currentYFrame);

	void InitalizeActor(Texture_Actor *texture, 
						b2World *world,
						glm::vec2 positon,
						glm::vec2 size,
						glm::vec2 boxSize,
						int totalXFrames,
						int totalYFrames,
						int currentXFrame,
						int currentYFrame);

	bool onCreate(b2World& world);
	void onDestroy(b2World& world);
	void update(const float deltaTime_);
	void input();
	void draw(std::shared_ptr<Shader_Actor> shader,
	glm::mat4 projection, float xpos, float ypos, float boxWidth, float bowHeight, float rot) const;
	
	void draw(Texture_Actor *texture, std::shared_ptr<Shader_Actor> shader,
	glm::mat4 projection, float xpos, float ypos, float boxWidth, float bowHeight, float rot) const;

	void shoot_projectiles();


private:


};
