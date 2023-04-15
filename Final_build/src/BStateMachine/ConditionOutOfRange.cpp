//#include "ConditionOutOfRange.h"

#include "../../include/BStateMachine/ConditionOutOfRange.h"
#include "../../include/Actors/NPC_Actor.h"
#include "../../include/Actors/Player_Actor.h"

//bool ConditionOutOfRange::test(std::shared_ptr<Player_Actor> player) 
bool ConditionOutOfRange::test(Player_Actor* player) 
{
	float thresholdDistance = 20.5f;
	//threshold = 20.0f;
	//Use NPC actor

	if(!actor->checkDistanceBetweenPlayer(player, threshold))
	//if(!actor->checkDistanceBetweenPlayer(player, thresholdDistance))
	{
		std::cout << "OUT OF RANGE\n";
		return true;
	}
//	if(thresholdDistance > 0.0f)
//		return true;


	//if(actor->)

	return false;
}
