//#include "Transition.h"
#include "../../include/BStateMachine/Transition.h"
#include "../../include/BStateMachine/Condition.h"
#include "../../include/Actors/Player_Actor.h"

Transition::Transition(Condition* condition_, BState* targetState_)
{
	condition = condition_;
	targetState = targetState_;
}

Transition::~Transition()
{}

//bool Transition::isTriggered(std::shared_ptr<Player_Actor> player)
bool Transition::isTriggered(Player_Actor* player)
{
	//return condition->test(player.get());
	return condition->test(player);
}

