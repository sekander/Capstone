#include "../../include/Actors/Tent_Actor.h"
#include "../../include/Components/PhysicsComponent.h"
#include <box2d/b2_world.h>
#include <string>




Tent_Actor::Tent_Actor(Component* parent_) : Actor(parent_)
{
	AddComponent<PhysicsComponent>(nullptr);
}  

Tent_Actor::~Tent_Actor()
{

}

bool Tent_Actor::onCreate(b2World *world) 
{
	GetComponent<PhysicsComponent>()->create_body(
			world, false, false, glm::vec2(5, 20), 0.0f, 
			glm::vec2(20, 20));
	health = 1000;
	fortfied = 0;
}

void Tent_Actor::onDestroy()
{

}

void Tent_Actor::update(const float deltaTime_)
{

}

void Tent_Actor::draw(glm::mat4 projection, std::string text, float xpos, float ypos, float r, float g,float b) const
{
}
