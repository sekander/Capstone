#include "../../include/Components/AIComponent.h"
#include <box2d/b2_math.h>
#include <iostream>
#include "../../include/GameData/ObjectCounter.h"


AIComponent::AIComponent(Component* parent_  ) : Component(parent_)
{
	ObjectCounter::ai_component_counter++;

	//std::cout << "AI Component Attached : " << ObjectCounter::ai_component_counter << std::endl;

}

AIComponent::~AIComponent()
{
	ObjectCounter::ai_component_counter--;
	//std::cout << "AI Component Removed\n";

	for(auto &pos : aiPositions)
	{
		delete pos;
	}

	aiPositions.clear();
}

void AIComponent::update(const float delta)
{

}

//Seek algorithm impleentation
//otherBody : seeking b2Body
//y : added gravity vector
b2Vec2 AIComponent::seek(b2Body *otherBody, float maxSpeed, float gravity)
{
	//Find the vector between AI and otherbody
	auto result = otherBody->GetPosition() - m_body->GetPosition();
	//Calculate the direction of given vector
	result.Normalize();

	//Tranform unit vector to add velocity 
	//Max Speed
	result *= maxSpeed;

	//AI jump velocity
	//Copy otherbody velocity
	//auto ai_jump = otherBody->GetLinearVelocity().y * 0.80;

	//Set the new vector to AI body physic 	
	//return b2Vec2(result.x, ai_jump + gravity);
	return b2Vec2(result.x, m_body->GetLinearVelocity().y + gravity);
//	m_body->SetLinearVelocity(b2Vec2(result.x,  ai_jump + y));
}

//Flee algorithm impleentation
//otherBody : seeking b2Body
//y : added gravity vector
b2Vec2 AIComponent::flee(b2Body *otherBody, float maxSpeed, float gravity)
{
	//Find the vector between AI and otherbody
	auto result = m_body->GetPosition() - otherBody->GetPosition()  ;
	//Calculate the direction of given vector
	result.Normalize();
	//Tranform unit vector to add velocity 
	result *= maxSpeed;

	//AI jump velocity
	//Copy otherbody velocity
	auto ai_jump = otherBody->GetLinearVelocity().y * 0.80;

	//Set the new vector to AI body physic 	
	return b2Vec2(result.x, ai_jump + gravity);
}

//Basic wander algorithm
//
//Future Implementation
//Add Randomness to the distance
b2Vec2 AIComponent::wander( float minDistance, float maxSpeed, float maxDistance)
{
	m_position = m_body->GetPosition();

//	std::cout << "Pos x : " << m_position.x << std::endl; 
//	std::cout << "Pos y : " << m_position.y << std::endl; 

	/*
	//Change position once AI reached minDistance
	if(m_position.x < beginningPosition - minDistance )
		m_body->SetLinearVelocity(b2Vec2(maxSpeed,0.0f));	
	//Change position once AI reached minDistance
	else if(m_position.x > beginningPosition + maxDistance)
		m_body->SetLinearVelocity(b2Vec2(-maxSpeed, 0.0f));	
	//Update AI position
	return b2Vec2(m_position);



	m_position = m_body->GetPosition();
	*/




 /*
	std::cout << "Pos x : " << m_body->GetPosition().x << std::endl; 
	std::cout << "Pos y : " << m_body->GetPosition().y << std::endl; 
 
//Change position once AI reached minDistance
 
if(m_position.x < beginningPosition - minDistance )
	m_body->SetLinearVelocity(b2Vec2(10.0f,0.0f)); 
else
	m_body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
//Change position once AI reached minDistance
if(m_position.x > beginningPosition + maxDistance)
	m_body->SetLinearVelocity(b2Vec2(-10.0f, 0.0f)); 
else
	m_body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
 
	//Update AI position
	m_body->SetTransform(m_position, 0.0f);

*/



populateAIPositions('A', b2Vec2(m_body->GetPosition().x - minDistance, m_body->GetPosition().y));
populateAIPositions('B', b2Vec2(m_body->GetPosition().x + maxDistance, m_body->GetPosition().y));






		auto ai_positions = getAIPositions();
		for(int i = 0; i < ai_positions.size(); i++)
		{
			if(!ai_positions[0]->destination)
			{
				//std::cout << "Pos " << ai_positions[0]->key << " : " << ai_positions[0]->position.x << ", " << ai_positions[0]->position.y << std::endl;
				if(moveLeftPosition(ai_positions[0]->position))
				//if(ai->movePosition(ai_positions[0]->position))
				{
					//std::cout << "AI Reached Destination" << std::endl;
					ai_positions[0]->destination = true;
					if(ai_positions[1]->destination)
						ai_positions[1]->destination = false;
				}
			}
			else if(!ai_positions[1]->destination)
			{
				//std::cout << "Pos " << ai_positions[1]->key << " : " << ai_positions[1]->position.x << ", " << ai_positions[1]->position.y << std::endl;
				if(moveRightPosition(ai_positions[1]->position))
				//if(ai->movePosition(ai_positions[0]->position))
				{
					//std::cout << "AI Reached Destination" << std::endl;
					ai_positions[1]->destination = true;
					if(ai_positions[2]->destination)
						ai_positions[2]->destination = false;
				}
			}
			else
			{
				//Restart the loop
				printf("AI finished its path"); 
				ai_positions[0]->destination = false;
			}
		}















}

