#pragma once

#include <list>
#include <memory>

class Transition;

enum class STATE {SEEK, WANDER, FLEE, ATTACK};

using namespace std;
class BState
{
	private:
		list<Transition*> transitions;
		list<std::shared_ptr<Transition>> Stransitions;
		STATE name;

	public:
		BState(STATE name_){name = name_;}
		~BState(){}
		list<Transition*> getTransitions(){return transitions;}
		list<std::shared_ptr<Transition>> getSTransitions(){return Stransitions;}
		void addTransition(Transition* transition);
		void addTransition(std::shared_ptr<Transition> transition);

		STATE getName() {return name;}
};
