#pragma once

#include "../Components/Component.h"
#include "Actor.h"
#include <glm/fwd.hpp>


class Shader_Actor;
class Platform_Actor : public Actor {

public:
	Platform_Actor(Component* parent_);
	~Platform_Actor();

	bool onCreate();
	void onDestroy();
	void update(const float deltaTime_);
	void input();
	void draw(std::shared_ptr<Shader_Actor> shader, glm::mat4 projection, float xpos, float ypos, float boxWidth, float bowHeight, float rot) const;


private:
    static uint16_t projectile_count;
};
