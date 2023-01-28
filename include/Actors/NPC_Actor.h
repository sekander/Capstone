#pragma once

#include "../Components/Component.h"
#include "Actor.h"
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <sys/types.h>

#include "../BStateMachine/BState.h"
#include "../BStateMachine/BStateMachine.h"
#include "../BStateMachine/Condition.h"
#include "../BStateMachine/ConditionInRange.h"
#include "../BStateMachine/ConditionOutOfRange.h"


class Shader_Actor;
class Projectile_Actor;
class Player_Actor;

class NPC_Actor : public Actor {

public:
	NPC_Actor(Component* parent_);
	~NPC_Actor()
	{
		stateMachine = nullptr;
		seekPlayer = nullptr;
		wander = nullptr;
		ifInRange = nullptr;		
		outOfRange = nullptr;
		inTransition = nullptr;
		outTransition = nullptr;


		delete stateMachine;
		delete seekPlayer;
		delete wander;
		delete ifInRange;		
		delete outOfRange;
		delete inTransition;
		delete outTransition;
		
	}

	bool onCreate(int num_x_frame, int num_y_frame, int curr_x_frame, int curr_y_frame);
	void onDestroy();
	void update( std::shared_ptr<Player_Actor> player, const float deltaTime_);
	void input();
	void draw(std::shared_ptr<Shader_Actor> shader, glm::mat4 projection, float xpos, float ypos, float boxWidth, float bowHeight, float rot) const;



	//Update collision with bullets
	void collison_update(std::shared_ptr<Projectile_Actor> projectile);

	//Getters and Setters	
	int get_health(){return health;}
	void set_health(int health_){health = health_;}
	bool get_collision(){return npc_collision;}	
	void set_collision(bool collision){ npc_collision = collision; }
	void set_colour(glm::vec3 colour){npc_colour = colour;}


	//bool checkDistanceBetweenPlayer(std::shared_ptr<Player_Actor> player, float distance);
	bool checkDistanceBetweenPlayer(Player_Actor* player, float distance);


	//This method creates memory leaks 
	//Behaviour State Machine
	bool readStateMachine(string fileName){
		stateMachine = new BStateMachine(this);
		seekPlayer = new BState(STATE::SEEK);
		wander = new BState(STATE::WANDER);
	
		ifInRange = new ConditionInRange(this);		
		//wander->addTransition(std::make_shared<Transition>(ifInRange, seekPlayer));
		wander->addTransition(new Transition(ifInRange, seekPlayer));
		//inTransition = new Transition(ifInRange, seekPlayer);
		//wander->addTransition(inTransition);

		outOfRange = new ConditionOutOfRange(this);
		//seekPlayer->addTransition(std::make_shared<Transition>(outOfRange, wander));
		//seekPlayer->addTransition(new Transition(outOfRange, wander));
		
		outTransition = new Transition(outOfRange, wander);
		//seekPlayer->addTransition(inTransition);
		seekPlayer->addTransition(outTransition);

		stateMachine->setInitialState(wander);

		return true;
	}


private:
	int health;
	glm::vec3 npc_colour;
	bool npc_collision;
	BStateMachine* stateMachine;
	BState* seekPlayer;
	BState* wander;
	Condition* ifInRange;		
	Condition* outOfRange;
	Transition* inTransition;
	Transition* outTransition;



};
