#pragma once

#include <iostream>
//#include "NPC_Actor.h"

//abstract class 
class NPC_Actor;
class Player_Actor;


class Condition
{

	protected:
		NPC_Actor* actor;	


	public:
		Condition(NPC_Actor* owner){actor = owner;}
		~Condition(){}

		//virtual bool test(std::shared_ptr<Player_Actor> player) = 0;
		virtual bool test(Player_Actor* player) = 0;

};
