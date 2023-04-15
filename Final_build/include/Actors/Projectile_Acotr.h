#pragma once

#include "../Components/Component.h"
#include "Actor.h"
//#include "NPC_Actor.h"
//#include "NPC_Actor.h"
#include "Player_Actor.h"
#include "Gun_Actor.h"
#include <glm/fwd.hpp>
#include <memory>



class Shader_Actor;
class NPC_Actor;
class Projectile_Actor: public Actor {

public:
	Projectile_Actor(Component* parent_);
	~Projectile_Actor();

	bool onCreate();
	void onDestroy();
	void update(const float deltaTime_ );
	void input();
	void draw(std::shared_ptr<Shader_Actor> shader, glm::mat4 projection, float xpos, float ypos, float boxWidth, float bowHeight, float rot) const;

  
  
 
	bool checkDistanceBetween(NPC_Actor* npc, float distance);

	void resetBulletPos(int i);
	void projectile_collision_update(std::shared_ptr<NPC_Actor> actor);
	void projectile_firing(float projectile_vel_x, float projectile_vel_y, std::shared_ptr<Gun_Actor> spawnLoc);


	bool get_projectile_collision(){return projectile_collision;}
	void set_projectile_collision(bool collision){projectile_collision = collision;}


private:
    static uint16_t projectile_count;
  
    //Ball class member variable
    bool projectile_collision;

    float projectile_counter;

	bool projectile_shooting_right;
	bool projectile_shooting_up;
	bool projectile_shooting_left;
	bool projectile_shooting_down;
};
