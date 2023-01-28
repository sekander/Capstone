//#include "BState.h"
#include "../../include/BStateMachine/BState.h"
#include <memory>

void BState::addTransition(Transition* transition)
{
	transitions.push_back(transition);
}


void BState::addTransition(std::shared_ptr<Transition> transition)
{
	Stransitions.push_back(transition);
}
