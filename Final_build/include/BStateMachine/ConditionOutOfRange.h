#pragma once

#include "Condition.h"

class Player_Actor;

class ConditionOutOfRange : public Condition
{

	private:
		float threshold;

	public:
		ConditionOutOfRange(NPC_Actor* actor, float threshold_ = 10) : Condition(actor){
			threshold = threshold_;
		}

	//bool test(std::shared_ptr<Player_Actor> player) ;
	bool test(Player_Actor* player) ;
};
