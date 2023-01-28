#pragma once

#include "../Components/Component.h"
#include "Actor.h"
#include <glm/fwd.hpp>
#include <memory>
#include <box2d/box2d.h>

class Projectile_Actor;
class Shader_Actor;

class Gun_Actor : public Actor {

public:
	Gun_Actor(Component* parent_);
	~Gun_Actor();

	bool onCreate(b2World& world);
	void onDestroy(b2World& world);
	void update(const float deltaTime_);
	void input();
	void draw(std::shared_ptr<Shader_Actor> shader, std::shared_ptr<Shader_Actor> bullet_shader,
	glm::mat4 projection, float xpos, float ypos, float boxWidth, float bowHeight, float rot) const;

	void shoot_projectiles();

	std::vector<std::shared_ptr<Projectile_Actor>> get_projectile_list()
	{return bullets;}

private:



	std::vector<std::shared_ptr<Projectile_Actor>> bullets;
};
