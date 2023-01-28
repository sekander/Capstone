#include "../../include/Actors/Shader_Actor.h"
#include "../../include/Actors/Projectile_Acotr.h"
#include "../../include/Actors/Player_Actor.h"
#include "../../include/Actors/NPC_Actor.h"

#include "../../include/Components/TransformComponent.h"
#include "../../include/Components/ShaderComponent.h"
#include "../../include/Components/RenderComponent.h"
#include "../../include/Components/PhysicsComponent.h"
#include "../../include/Components/AIComponent.h"


#include <box2d/b2_math.h>
#include <box2d/box2d.h>
NPC_Actor::NPC_Actor(Component* parent_) : Actor(parent_)
{
	AddComponent<TransformComponent>(nullptr);
	AddComponent<RenderComponent>(nullptr);
	AddComponent<PhysicsComponent>(nullptr);
	AddComponent<AIComponent>(nullptr);
	std::cout << "######################NPC Player Actor Created#######################" << std::endl;
	ListComponents();
}  

bool NPC_Actor::onCreate(int num_x_frame, int num_y_frame, int curr_x_frame, int curr_y_frame)
{
	GetComponent<RenderComponent>()->initRenderData();
	//GetComponent<RenderComponent>()->renderData(num_x_frame, num_y_frame, curr_x_frame, curr_y_frame);

//	dimensions();
}

void NPC_Actor::onDestroy()
{

}

void NPC_Actor::input()
{
}

//bool NPC_Actor::checkDistanceBetweenPlayer(std::shared_ptr<Player_Actor> player, float distance)
bool NPC_Actor::checkDistanceBetweenPlayer(Player_Actor* player, float distance)
{
//	if(player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - this->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x <= distance
//	|| this->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x <= distance)
//		return true;
//	return false;



    	auto s = sqrt(pow(this->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 
						  player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x , 2) + 
					  pow(this->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 
					  	  player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y, 2) * 1.0);

		if(s < distance){
			//std::cout << "WITHIN ATTACK RANGE " << std::endl;
			return true;
		}
		else if(s > distance)
		{
			//	std::cout << "DISTANCE BETWEEN PLAYER AND NPC : " << s << std::endl;
			return false;
		}
		return false;







}

void NPC_Actor::update( std::shared_ptr<Player_Actor> player,  const float deltaTime_)
{
	/*
		if(GetComponent<PhysicsComponent>()->get_body()->GetPosition().x > 900)
		{
			GetComponent<PhysicsComponent>()->get_body()->SetTransform(b2Vec2(200, 200), 0.0f);
		}
		*/
		
		//GetComponent<AIComponent>()->follow_player(player->GetComponent<PhysicsComponent>()->get_body());
		//for(auto ce = floor_edges.first->GetComponent<PhysicsComponent>()->get_body()->GetContactList(); ce; ce->next)
		//set_colour(vec3(1.0f, 0.4f, 0.6f));
		//
		//
		//Update the health on the 
		/*
		for(auto ce = GetComponent<PhysicsComponent>()->get_body()->GetContactList(); ce; ce->next)
		{
			auto c = ce->contact;
			if(c->IsTouching())
			{
				//std::cout << "NPC COLLISIONS " << std::endl;
				npc_collision = false;
				break;
			}
			else {
				std::cout << "NPC COLLISIONS FALSE" << std::endl;
				npc_collision = true;
				//health -= 1;


				break;
			}
		}	
		*/


	//State Machine implementation
	if(stateMachine)
	{
		stateMachine->update(player.get());
		switch(stateMachine->getCurrentStateName())
		{
			case STATE::SEEK:
				this->GetComponent<AIComponent>()->seek(player->GetComponent<PhysicsComponent>()->get_body(), 20.0f, 10.0f);
				//std::cout << "CURRENT STATE : " << " SEEK" << std::endl;
				break;
			case STATE::WANDER:
				this->GetComponent<AIComponent>()->wander(10.0f, 10.0f, 50.0f);
				//std::cout << "CURRENT STATE : " << " WANDER" << std::endl;
				break;
		}


	}

}

void NPC_Actor::collison_update(std::shared_ptr<Projectile_Actor> projectile)
{
	//Update the health on the 
	for(auto ce = GetComponent<PhysicsComponent>()->get_body()->GetContactList(); ce; ce->next)
	{
		auto c = ce->contact;
		if(c->IsTouching())
		{
			//std::cout << "NPC COLLISIONS " << std::endl;
			npc_collision = false;
			break;
		}
		else {
			//std::cout << "NPC COLLISIONS FALSE" << std::endl;
			npc_collision = true;
			//Check bullet position and npc position
			if(projectile->get_projectile_collision() )
			{
				//std::cout << "BULLET COLLISIONS FALSE" << std::endl;
				health -= 5;
				projectile->set_projectile_collision(false);
				npc_collision = false;
			}

			break;
		}
	}	
}


void NPC_Actor::draw(std::shared_ptr<Shader_Actor> shader, glm::mat4 projection, float xpos, float ypos, float boxWidth, float boxHeight, float rot) const
{
	shader->GetComponent<ShaderComponent>()->Use();
         	shader->GetComponent<ShaderComponent>()->SetMatrix4("projection", projection);
          	shader->GetComponent<ShaderComponent>()->SetMatrix4("model", GetComponent<TransformComponent>()->transform(
					vec2(xpos, ypos), 
					vec2(boxWidth, boxHeight), rot));
            shader->GetComponent<ShaderComponent>()->SetVector3f("color", npc_colour);
        GetComponent<RenderComponent>()->drawSquare();
        //GetComponent<RenderComponent>()->drawSprites();
}
