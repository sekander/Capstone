//#include "ConditionInRange.h"

#include "../../include/BStateMachine/ConditionInRange.h"
#include "../../include/Actors/NPC_Actor.h"
#include "../../include/Actors/Player_Actor.h"

//bool ConditionInRange::test(std::shared_ptr<Player_Actor> player)
bool ConditionInRange::test(Player_Actor* player)
{
	float thresholdDistance = 10.0f;
	//threshold = 10.0f;
	//Use NPC position
//	if(thresholdDistance > 0.0f)
//		return true;
 
	if(actor->checkDistanceBetweenPlayer(player, threshold))
	//if(actor->checkDistanceBetweenPlayer(player, thresholdDistance))
	{
		std::cout << "IN RANGE\n";
		return true;
	}

	return false;
}
