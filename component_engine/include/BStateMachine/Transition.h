#pragma once

//#include "BState.h"
//#include "Condition.h"

class Condition;
class BState;
class Player_Actor;

class Transition 
{
	private:
		//Ignoring action for this demo
		BState* targetState;
		Condition* condition;
	
	public:
		Transition(Condition* condition_, BState* targetState_);
		~Transition();
		//bool isTriggered(std::shared_ptr<Player_Actor> player);
		bool isTriggered(Player_Actor* player);
		BState* getTargetState(){return targetState;}
};
