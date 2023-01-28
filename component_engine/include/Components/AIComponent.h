#pragma once

#include "Component.h"
#include <glm/glm.hpp>
#include <box2d/box2d.h>

#include <iostream>
#include <unordered_map>

//Path finding algorithms includes
#include "../Graphs/BFS_graph.h"

struct AIposition{
	bool destination;
	char key;
	b2Vec2 position;
}; 




using namespace glm;
class AIComponent : public Component
{
	public:
		AIComponent (Component* parent_ );
		~AIComponent ();
		bool onCreate()override {return false;}
		void onDestroy() override{}
		void update(const float delta) override;
		
		void draw() const override{}

		void Init(b2Body* body) 
		{       
			m_body = body; 
			beginningPosition = m_body->GetPosition().x;
			//Set AI initial velocity
			m_body->SetLinearVelocity(b2Vec2(0.0f, m_body->GetLinearVelocity().y));	
		}

		
		//Steering Algorithms:w
		b2Vec2 seek(b2Body *otherBody, float maxSpeed, float gravity);	
		b2Vec2 flee(b2Body *otherBody, float maxSpeed, float gravity);	
		b2Vec2 wander(float minDistance, float maxSpeed, float maxDistance);	


		//Move AI to set position in world
		bool movePosition(b2Vec2 positions)
		{
			if(m_body->GetPosition().x > beginningPosition + positions.x){
				m_body->SetLinearVelocity(b2Vec2(-10.0f, 0.0f));
				//std::cout << "MOVING LEFT NPC Position X : " << m_body->GetPosition().x   
				//		  << " \nNPC Position Y : " << m_body->GetPosition().y 
				//<< std::endl;  
			}
			else if(m_body->GetPosition().x < beginningPosition - positions.x){
				m_body->SetLinearVelocity(b2Vec2(10.0f, 0.0f));
				//std::cout << "MOVING RIGHT NPC Position X : " << m_body->GetPosition().x   
				//		  << " \nNPC Position Y : " << m_body->GetPosition().y 
				//<< std::endl;  
			}
			else
			{
				//std::cout << "STOP MOVING LEFT" << std::endl;
				m_body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
				return true;
			}
			return false;
		}

		bool moveLeftPosition(b2Vec2 positions)
		{
			if(m_body->GetPosition().x > positions.x){
				//m_body->SetLinearVelocity(b2Vec2(-10.0f, 0.0f));
				m_body->SetLinearVelocity(b2Vec2(-10.0f, m_body->GetLinearVelocity().y));
				//std::cout << "MOVING LEFT NPC Position X : " << m_body->GetPosition().x   
				//		  << " \nNPC Position Y : " << m_body->GetPosition().y 
				//<< std::endl;  
			}
			else
			{
				//std::cout << "STOP MOVING LEFT" << std::endl;
				m_body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
				return true;
			}
			return false;
		}
		
		//Move AI to set position in world
		bool moveRightPosition(b2Vec2 positions)
		{
			if(m_body->GetPosition().x < positions.x){
				//m_body->SetLinearVelocity(b2Vec2(10.0f, 0.0f));
				m_body->SetLinearVelocity(b2Vec2(10.0f, m_body->GetLinearVelocity().y));
				//std::cout << "MOVING RIGHT NPC Position X : " << m_body->GetPosition().x   
				//		  << " \nNPC Position Y : " << m_body->GetPosition().y 
				//<< std::endl;  
			}
			else
			{
				//std::cout << "STOP MOVING RIGHT" << std::endl;
				m_body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
				return true;
			}
			return false;
		}


		//Breadth first search
		std::vector<int> search()
		{
			bfs_graph = std::make_shared<Graph>(4);

			bfs_graph->addEdge(0, 1);
			bfs_graph->addEdge(0, 2);
			bfs_graph->addEdge(1, 2);
			bfs_graph->addEdge(2, 0);
			bfs_graph->addEdge(2, 3);
			bfs_graph->addEdge(3, 3);

			bfs_graph->BFS(2);

			return bfs_graph->getVisitedNodes();
		}

		std::shared_ptr<Graph> getGraph(){return bfs_graph;}

		void populateAIPositions(char key, b2Vec2 positions)
		{
			AIposition *aiP;

			aiP = new AIposition();

			aiP->key = key;
			aiP->position = positions;
			aiP->destination = false;

			//aiPositions.push_back(aiP);
			//aiPositions.insert(std::make_pair(key, aiP));
			aiPositions.push_back(aiP);
		}

		//std::unordered_map< char,AIposition> getAIPositions(){return aiPositions;}
		//std::unordered_map<std::string ,AIposition> getAIPositions(){return aiPositions;}
		std::vector<AIposition*> getAIPositions(){return aiPositions;}




	private:
		b2Vec2 m_position;
		b2Vec2 m_velocity;

		b2Body* m_body;

		float beginningPosition;

		std::shared_ptr<Graph> bfs_graph;

		std::vector<AIposition*> aiPositions;
		//std::unordered_map<char,AIposition> aiPositions;
		//std::unordered_map<std::string ,AIposition> aiPositions;
};
