#pragma once

#include "../Components/Component.h"
#include "Actor.h"
#include <glm/fwd.hpp>
#include <memory>

class Shader_Actor;
class Gun_Actor;
class Edge_Actor;

class Player_Actor : public Actor {

public:
	Player_Actor(Component* parent_);
	~Player_Actor();

	bool onCreate(int num_x_frame, int num_y_frame, int curr_x_frame, int curr_y_frame);
	void onDestroy();
	void update(const float deltaTime_);
	void input();
	void draw(std::shared_ptr<Shader_Actor> shader, glm::mat4 projection, float xpos, float ypos, float boxWidth, float bowHeight, float rot) const;

	void jump();
	void moveLeft();
	void moveRight();
	void stop();

	void check_collision_edge(std::shared_ptr<Edge_Actor> edge);

	void pressure_sensitve_jump(float pressure);
	bool pick_up_gun(std::shared_ptr<Gun_Actor> gun);

	bool get_jump_flag(){return jump_flag;}
	void set_jump_flag(bool jump){jump_flag = jump;}
	
	bool get_floor_flag(){return floor_flag;}
	void set_floor_flag(bool bfloor){floor_flag= bfloor;}

	bool get_run_flag(){return run_flag;}
	void set_run_flag(bool run){run_flag = run;}
	
	bool get_gun_equipped_flag(){return gun_equipped;}
	void set_gun_equipped_flag(bool gun){gun_equipped = gun;}

	float force_x;
	float force;

private:
	u_int16_t counter = 0;
	bool jump_flag;
	bool floor_flag;
	bool run_flag;
	bool gun_equipped;

	bool player_collision;
};
