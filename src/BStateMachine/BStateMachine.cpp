#include "../../include/BStateMachine/BStateMachine.h"
#include "../../include/BStateMachine/Transition.h"
#include "../../include/Actors/NPC_Actor.h"
#include "../../include/Actors/Player_Actor.h"


void BStateMachine::setInitialState(BState* initial)
{
	initialState = initial;
	currentState = initialState;
}

//void BStateMachine::update(std::shared_ptr<Player_Actor> player)
void BStateMachine::update(Player_Actor* player)
{
	Transition* triggered = nullptr;

	//store first transition that triggered
	for(auto transition : currentState->getTransitions())
	{
		if(transition->isTriggered(player))
		{
			triggered = transition;
			break;
		}
	}

	if(triggered)
	{
		BState* targetState = triggered->getTargetState();
		//collect exit actions, transition action, and target state actions
		currentState = targetState;
		
		std::cout << "TRIGGERED !!!!!!!!!" << std::endl;
		return;
	}
	else
	{
		//process action
		return;
		
	}
	//return actions
	return;

}

