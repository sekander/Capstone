#pragma once

#include "../Components/Component.h"
#include "Actor.h"
#include <glm/fwd.hpp>
#include <memory>



class Shader_Actor;
class Gun_Actor;
class Edge_Actor;
class Animate_Actor;
class GameData;


class Animated_Player_Actor : public Actor {

public:
	Animated_Player_Actor(Component* parent_);
	~Animated_Player_Actor();

	bool onCreate(int num_x_frame, int num_y_frame, int curr_x_frame, int curr_y_frame);
	void onDestroy();
	void update(const float deltaTime_);
	void input(GameData* data);
	void draw(std::shared_ptr<Shader_Actor> shader, glm::mat4 projection, float xpos, float ypos, float boxWidth, float bowHeight, float rot) const;

	void jump();
	void moveLeft();
	void moveRight();
	void stop();

	void check_collision_edge(std::shared_ptr<Edge_Actor> edge);

	void pressure_sensitve_jump(float pressure);
	bool pick_up_gun(std::shared_ptr<Gun_Actor> gun);

	bool get_jump_flag() const {return jump_flag;}
	void set_jump_flag(bool jump){jump_flag = jump;}
	
	bool get_shooting_flag() const {return shooting_flag;}
	void set_shooting_flag(bool jump){shooting_flag = jump;}
	
	bool get_move_flag() const {return move_flag;}
	void set_move_flag(bool jump){move_flag = jump;}
	
	bool get_move_left_flag() const {return move_left_flag;}
	void set_move_left_flag(bool jump){move_left_flag = jump;}
	
	bool get_floor_flag() const {return floor_flag;}
	void set_floor_flag(bool bfloor){floor_flag= bfloor;}

	bool get_run_flag() const {return run_flag;}
	void set_run_flag(bool run){run_flag = run;}
	
	bool get_gun_equipped_flag() const {return gun_equipped;}
	void set_gun_equipped_flag(bool gun){gun_equipped = gun;}

	float force_x;
	float force;

private:
	u_int16_t counter = 0;
	bool move_flag;
	bool move_left_flag;
	bool jump_flag;
	bool shooting_flag;
	bool floor_flag;
	bool run_flag;
	bool gun_equipped;

	bool player_collision;
	
	std::shared_ptr<Animate_Actor> idle_animation;
	std::shared_ptr<Animate_Actor> run_animation;
	std::shared_ptr<Animate_Actor> runLeft_animation;
	std::shared_ptr<Animate_Actor> jump_animation;
	
/*
	double delay;
	double jump_delay;
	float counter;

	uint16_t platform_delay = 0;
	bool reachedPos = false;
	bool prevPos = true;


    //Levels level;


int x_pos;
int y_pos;

float xpos_o = 0.0f;
float ypos_o = 0.0f;
float xpos_d = 0.0f;
float ypos_d = 0.0f;

bool bullet_collides = false;
bool ncp_collides = false;

float gun_angle = 0.0f;

float jump_counter = 0.0f;
bool jump_press = false;

bool shooting_left = false;
bool shooting_right = true;
*/	
};
