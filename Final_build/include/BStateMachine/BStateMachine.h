#pragma once

#include "BState.h"
#include "Transition.h"
#include "Condition.h"
#include "ConditionInRange.h"
//#include "NPC_Actor.h"

class NPC_Actor;
class Player_Actor;

class BStateMachine
{

	private:
		BState* initialState;
		BState* currentState;
		//Character* owner;
		//NPC actor actor;
		NPC_Actor* actor;

	public:
		//BStateMachine(Character* owner_){owner = owner;_}
		BStateMachine(NPC_Actor* owner_){actor = owner_;}
		~BStateMachine(){}
		void setInitialState(BState* initial);
		//void update(std::shared_ptr<Player_Actor> player);
		void update(Player_Actor* player);
		STATE getCurrentStateName(){return currentState->getName();}

};
