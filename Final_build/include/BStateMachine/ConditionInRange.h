#pragma once

#include "Condition.h"
//#include "NPC_Actor.h"

class NPC_Actor;
class Player_Actor;


class ConditionInRange : public Condition {

	private:
		float threshold;

	public:
		ConditionInRange(NPC_Actor* actor, float threshold_ = 10) :
			Condition(actor)
	{
		threshold = threshold_;

	}

	//bool test(std::shared_ptr<Player_Actor> player);
	bool test(Player_Actor* player);
};
