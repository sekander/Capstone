#pragma once

#include "../Components/Component.h"
#include "Actor.h"
#include <box2d/b2_world.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <sys/types.h>

#include "../BStateMachine/BState.h"
#include "../BStateMachine/BStateMachine.h"
#include "../BStateMachine/Condition.h"
#include "../BStateMachine/ConditionInRange.h"
#include "../BStateMachine/ConditionOutOfRange.h"
#include "Tent_Actor.h"

class ObjectCounter;
class Shader_Actor;
class Projectile_Actor;
class Player_Actor;
class Tent_Actor;

class NPC_Actor : public Actor {

public:
	NPC_Actor(Component* parent_);
	~NPC_Actor();

	void InitalizeActor(const char* fileName,
						b2World *world,
						glm::vec2 positon,
						glm::vec2 size,
						glm::vec2 boxSize,
						int currentframeX,
						int currentframeY,
						int totalXFrames,
						int totalYFrames);
	
	void InitalizeActor(
						b2World *world,
						glm::vec2 positon,
						glm::vec2 size,
						glm::vec2 boxSize,
						int currentframeX,
						int currentframeY,
						int totalXFrames,
						int totalYFrames);

	bool onCreate(int num_x_frame, int num_y_frame, int curr_x_frame, int curr_y_frame);



	void onDestroy();
	//void basic_update( std::shared_ptr<Player_Actor> player, const float deltaTime_, b2World *world, int increase = 0);
	void basic_update( std::shared_ptr<Tent_Actor> actor, std::shared_ptr<Player_Actor> player, const float deltaTime_, b2World *world, int increase = 0);
	void update( std::shared_ptr<Player_Actor> player, const float deltaTime_, b2World *world, bool stateMachineExist);
	void input();
	void draw(std::shared_ptr<Shader_Actor> shader, glm::mat4 projection, float xpos, float ypos, float boxWidth, float bowHeight, float rot) const;



	//Update collision with bullets
	void collison_update(std::shared_ptr<Projectile_Actor> projectile);

	//Getters and Setters	
	int get_health(){return health;}
	void set_health(int health_){health = health_;}

	bool get_isWalking(){return isWalking;}
	void set_isWalking(bool walking){isWalking = walking;}

	bool get_isRunning(){return isRunning;}
	void set_isRunning(bool running){isRunning = running;}

	bool get_isAttacking(){return isAttacking;}
	void set_isAttacking(bool attack){isAttacking = attack;}



	bool get_collision(){return npc_collision;}	
	void set_collision(bool collision){ npc_collision = collision; }
	void set_colour(glm::vec3 colour){npc_colour = colour;}


	//bool checkDistanceBetweenPlayer(std::shared_ptr<Player_Actor> player, float distance);
	//bool checkDistanceBetweenPlayer(Player_Actor* player, float distance);
	bool checkDistanceBetweenPlayer(Actor* player, float distance);


	//This method creates memory leaks 
	//Behaviour State Machine
	bool readStateMachine(string fileName){
		stateMachine = new BStateMachine(this);
		seekPlayer = new BState(STATE::SEEK);
		wander = new BState(STATE::WANDER);
		attack = new BState(STATE::ATTACK);
	

		ifInRange = new ConditionInRange(this, 20.0f);
		inAttackRange = new ConditionInRange(this, 3.0f);

		wander->addTransition(new Transition(ifInRange, seekPlayer));
		seekPlayer->addTransition(new Transition(inAttackRange, attack));
		//inTransition = new Transition(ifInRange, seekPlayer);
		//wander->addTransition(inTransition);

		outAttackRange = new ConditionOutOfRange(this, 3.0f);
		outOfRange = new ConditionOutOfRange(this, 20.0f);

		//seekPlayer->addTransition(std::make_shared<Transition>(outOfRange, wander));
		//seekPlayer->addTransition(new Transition(outOfRange, wander));
		
		//outTransition = new Transition(outOfRange, wander);
		//seekPlayer->addTransition(inTransition);
		//seekPlayer->addTransition(outTransition);
		attack->addTransition(new Transition(outAttackRange, seekPlayer));
		seekPlayer->addTransition(new Transition(outOfRange, wander));

		stateMachine->setInitialState(wander);

		return true;
	}
	void set_attackPosition(int pos){attackLocation = pos;}


private:
	int health;
	glm::vec3 npc_colour;
	bool npc_collision;
	BStateMachine* stateMachine;
	BState* seekPlayer;
	BState* wander;
	BState* attack;
	Condition* inAttackRange;
	Condition* outAttackRange;
	Condition* ifInRange;		
	Condition* outOfRange;
	Transition* inTransition;
	Transition* outTransition;

	bool isWalking;
	bool isRunning;
	bool isAttacking;

	int attackLocation;


};
