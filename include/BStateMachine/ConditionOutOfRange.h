#pragma once

#include "Condition.h"

class Player_Actor;

class ConditionOutOfRange : public Condition
{

	private:

	public:
		ConditionOutOfRange(NPC_Actor* actor) : Condition(actor){}

	//bool test(std::shared_ptr<Player_Actor> player) ;
	bool test(Player_Actor* player) ;
};
