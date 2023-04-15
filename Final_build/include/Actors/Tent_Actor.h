#pragma once

#include "../Components/Component.h"
#include "Actor.h"
#include <box2d/b2_world.h>
#include <glm/fwd.hpp>

class Tent_Actor : public Actor {

public:
	Tent_Actor(Component* parent_);
	~Tent_Actor();

	//bool onCreate(const char* vShader, const char* fShader, std::string textFile, unsigned int fontSize);
	bool onCreate(b2World* world);
	void onDestroy();
	void update(const float deltaTime_);
	void draw(glm::mat4 projection, std::string text, float xpos, float ypos, 
		       	float r = 0.0f, float g = 1.0f, float b = 0.0f) const;
	int get_health(){return health;}
	void set_health(int h){health = h;}
	
	int get_fortify(){return fortfied;}
	void set_fortify(int h){fortfied = h;}

private:
	int health;
	int fortfied;

};
