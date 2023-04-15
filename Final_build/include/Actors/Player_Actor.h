#pragma once

#include "../Components/Component.h"
#include "Actor.h"
#include "PickUps_Actor.h"
#include "Tent_Actor.h"
#include <glm/fwd.hpp>
#include <memory>
#include <box2d/b2_world.h>
#include <vector>

class Shader_Actor;
class Gun_Actor;
class Edge_Actor;
class GameData;
class PickUps_Actor;
class Tent_Actor;

class Player_Actor : public Actor {

public:
	Player_Actor(Component* parent_);
	~Player_Actor();

	void InitalizeActor(const char* fileName, 
										  b2World *world, 
											glm::vec2 position, 
											glm::vec2 size, 
											glm::vec2 boxSize, 
											int totalXFrames,
											int totalYFrames,
											int currentXFrame,
											int currentYFrame);
	

	bool onCreate(int num_x_frame, int num_y_frame, int curr_x_frame, int curr_y_frame);
	void onDestroy();
	void update(const float deltaTime_, GameData* _data, Tent_Actor* tent);
	void input(GameData* _data );
	void draw(std::shared_ptr<Shader_Actor> shader, glm::mat4 projection, float xpos, float ypos, float boxWidth, float bowHeight, float rot) const;

	//bool checkDistanceBetween(std::shared_ptr<PickUps_Actor> pickUps, float distance);
	bool checkDistanceBetween(std::shared_ptr<Actor> pickUps, float distance);

	void jump();
	void moveLeft();
	void moveRight();
	void stop();

	void check_collision_edge(std::shared_ptr<Edge_Actor> edge);

	void pressure_sensitve_jump(float pressure);
	bool pick_up_gun(std::shared_ptr<Gun_Actor> gun);

	bool get_notMoving_flag(){return notMoving_flag;}
	void set_notMoving_flag(bool notMoving){notMoving_flag = notMoving;}


	bool get_MoveRight_flag(){return moveRight_flag;}
	void set_MoveRight_flag(bool moveRight){moveRight_flag = moveRight;}

	bool get_MoveLeft_flag(){return moveLeft_flag;}
	void set_MoveLeft_flag(bool moveLeft){moveLeft_flag = moveLeft;}

	bool get_shooting_flag(){return shooting_flag;}
	void set_shooting_flag(bool shooting){shooting_flag = shooting;}

	bool get_jump_flag(){return jump_flag;}
	void set_jump_flag(bool jump){jump_flag = jump;}
	
	bool get_floor_flag(){return floor_flag;}
	void set_floor_flag(bool bfloor){floor_flag= bfloor;}

	bool get_run_flag(){return run_flag;}
	void set_run_flag(bool run){run_flag = run;}
	
	bool get_gun_equipped_flag(){return gun_equipped;}
	void set_gun_equipped_flag(bool gun){gun_equipped = gun;}


	int get_player_health(){return player_health;}
	void set_player_health(int health){player_health = health;}
	
	int get_player_armor(){return player_armor;}
	void set_player_armor(int a){player_armor = a;}


	float force_x;
	float force;

	std::vector<std::shared_ptr<Actor>> get_inventory(){
		return inventory;
	}

	int get_totalMedkits(){return totalMedkit;}
	void set_totalMedkits(int med){totalMedkit = med;}
	
	int get_totalEmergencykits(){return totalEmergencykit;}
	void set_totalEmergencykits(int med){totalEmergencykit = med;}

	int get_totalAntidotes(){return totalAntidotes;}
	void set_totalAntidotes(int ant){totalAntidotes = ant;}

	bool get_player_right_direction(){return player_right_direction;}
	void set_player_right_direction(bool right){player_right_direction = right;}
	
	bool get_player_left_direction(){return player_left_direction;}
	void set_player_left_direction(bool left){player_left_direction = left;}

	bool get_itemAmimation(){return playItemAnimation;}
	//void set_medkit_used(bool left){player_left_direction = left;}
	
	bool get_playerHealedAnimation(){return playerHealedAnimation;}
	void set_playerHealedAnimation(bool heal){playerHealedAnimation = heal;}
	
	bool get_playerReviedAnimation(){return playerReviedAnimation;}
	void set_playerReviedAnimation(bool revive){playerReviedAnimation = revive;}
	
	bool get_playerIsPoisoned(){return playerIsPoisoned;}
	void set_playerIsPoisoned(bool poison){playerIsPoisoned = poison;}


	int get_totalAdrenaline(){return totalAdrenaline;}
	void set_totalAdrenaline(int ant){totalAdrenaline = ant;}

	int get_totalRepairKit(){return totalRepairKit;}
	void set_totalRepairKit(int ant){totalRepairKit = ant;}

	int get_totalTraps(){return totalTraps;}
	void set_totalTraps(int ant){totalTraps = ant;}

	int get_totalFortify(){return totalFortify;}
	void set_totalFortify(int ant){totalFortify = ant;}


	bool get_playerAdrenalineOn(){return playerAdrenalineOn;}
	bool get_usedRepairKit(){return useRepairKit;}
	bool get_usedFortify(){return useFortify;}
	bool get_usedTrap(){return useTrap;}



private:
	u_int16_t counter = 0;
	bool jump_flag;
	bool floor_flag;
	bool run_flag;
	bool gun_equipped;
	float jump_counter = 0.0f;
	bool jump_press = false;

	bool notMoving_flag;

	bool player_collision;

	bool moveRight_flag;
	bool moveLeft_flag;

	bool player_right_direction;
	bool player_left_direction;



	bool shooting_flag;




	int player_health;
	int player_armor;


	//- Add armor, repair kit, traps, adrenaline, fortify, grenades, molotov cocktail 


	//Player ITEMS
	int totalFortify = 0;
	bool useFortify = false;
	bool itemFortifyUsed;
	double itemFortifyUsedTimeStamp;
	bool playFortifyAnimation;

	int totalTraps = 0;
	bool useTrap = false;
	bool itemTrapUsed;
	double itemTrapUsedTimeStamp;

	int totalRepairKit = 0;
	bool useRepairKit = false;
	bool itemRepairKitUsed;
	double itemRepairKitUsedTimeStamp;
	bool playItemRepairKitAnimation;

	int totalAdrenaline = 0;
	bool useAdrenaline = false;
	bool itemAdrenalineUsed;
	double itemAdrenalineUsedTimeStamp;
	bool playAdrenalineAnimation;
	bool playerAdrenalineOn = false;




	int totalMedkit = 0;
	int totalEmergencykit = 0;
	int totalAntidotes = 0;

	bool useMeditKit = false;
	bool itemMedkitUsed;
	int itemUsedTimeStamp;

	bool playItemAnimation;
	bool playerHealedAnimation;
	bool playerReviedAnimation;

	bool useAntidote = false;
	bool itemAntidoteUsed;
	int itemAntidoteUsedTimeStamp;

	bool playerIsPoisoned;

	//Add antiodote to cure poision
	//Add adrenaline to tempararily increase players speed


	//Add more projectiles 

	std::vector<std::shared_ptr<Actor>> inventory;
};
