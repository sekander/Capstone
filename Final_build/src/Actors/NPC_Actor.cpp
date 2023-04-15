#include "../../include/Actors/Shader_Actor.h"
#include "../../include/Actors/Projectile_Acotr.h"
#include "../../include/Actors/Player_Actor.h"
#include "../../include/Actors/Tent_Actor.h"
#include "../../include/Actors/NPC_Actor.h"

#include "../../include/Components/TransformComponent.h"
#include "../../include/Components/ShaderComponent.h"
#include "../../include/Components/RenderComponent.h"
#include "../../include/Components/PhysicsComponent.h"
#include "../../include/Components/AIComponent.h"

#include "../../include/GameData/ObjectCounter.h"


#include <box2d/b2_math.h>
#include <box2d/b2_world.h>
#include <box2d/box2d.h>
#include <memory>
NPC_Actor::NPC_Actor(Component* parent_) : Actor(parent_)
{
	AddComponent<TransformComponent>(nullptr);
	AddComponent<RenderComponent>(nullptr);
	AddComponent<PhysicsComponent>(nullptr);
	AddComponent<AIComponent>(nullptr);
	//std::cout << "######################NPC Player Actor Created#######################" << std::endl;
	//ListComponents();
	ObjectCounter::npc_actor_counter++;
}  

NPC_Actor::~NPC_Actor()
	{
		stateMachine = nullptr;
		seekPlayer = nullptr;
		wander = nullptr;
		ifInRange = nullptr;		
		outOfRange = nullptr;
		inTransition = nullptr;
		outTransition = nullptr;


		delete stateMachine;
		delete seekPlayer;
		delete wander;
		delete ifInRange;		
		delete outOfRange;
		delete inTransition;
		delete outTransition;

		ObjectCounter::npc_actor_counter--;
		
	}


bool NPC_Actor::onCreate(int num_x_frame, int num_y_frame, int curr_x_frame, int curr_y_frame)
{
	GetComponent<RenderComponent>()->initRenderData();
	//GetComponent<RenderComponent>()->renderData(num_x_frame, num_y_frame, curr_x_frame, curr_y_frame);

//	dimensions();
}

void NPC_Actor::InitalizeActor(const char* fileName,
							   b2World *world,
							   glm::vec2 position,
							   glm::vec2 size,
							   glm::vec2 boxSize,
							   int currentFrameX,
							   int currentFrameY,
							   int totalXFrames,
							   int totalYFrames)
{
	GetComponent<RenderComponent>()->LoadSprite(fileName, position, size, currentFrameX, currentFrameY);
	GetComponent<RenderComponent>()->renderData(totalXFrames, totalYFrames, currentFrameX, currentFrameY);
	GetComponent<PhysicsComponent>()->create_body(world, true, true, position, 0.0f, boxSize, currentFrameX, currentFrameY, 0x0004, 0x0008 | 0x0016 | 0x0004);
	//GetComponent<PhysicsComponent>()->create_body(world, true, true, position, 0.0f, boxSize, currentFrameX, currentFrameY, 0x0004, 0x0008 | 0x0016 );
	//GetComponent<PhysicsComponent>()->create_body(world, true, true, position, 0.0f, boxSize, currentFrameX, currentFrameY, 
	//0x0004, 0x004 | 0x0128);
	//0x0004, 0x0008 | 0x0128);
	GetComponent<AIComponent>()->Init(GetComponent<PhysicsComponent>()->get_body());
	//set_health(100);
}

void NPC_Actor::InitalizeActor(
							   b2World *world,
							   glm::vec2 position,
							   glm::vec2 size,
							   glm::vec2 boxSize,
							   int currentFrameX,
							   int currentFrameY,
							   int totalXFrames,
							   int totalYFrames)
{
	GetComponent<PhysicsComponent>()->create_body(world, 
												true, 
												true, 
												position, 
												0.0f, 
												boxSize, 
												currentFrameX, 
												currentFrameY, 
												//0x0004, 0x0004 | 0x0008 | 0x0128);
												0x0004, 0x0008 | 0x0128);
	GetComponent<AIComponent>()->Init(GetComponent<PhysicsComponent>()->get_body());
	//set_health(100);
	attackLocation = 1;
}


void NPC_Actor::onDestroy()
{

}

void NPC_Actor::input()
{
}

//bool NPC_Actor::checkDistanceBetweenPlayer(Player_Actor* player, float distance)
bool NPC_Actor::checkDistanceBetweenPlayer(Actor* player, float distance)
{
    	auto s = sqrt(pow(this->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 
						  player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x , 2) + 
					  pow(this->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 
					  	  player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y, 2) * 1.0);

		if(s < distance){
			return true;
		}
		else if(s > distance)
		{
			return false;
		}
		return false;
}


//void NPC_Actor::basic_update(std::shared_ptr<Player_Actor> player, const float deltaTime_, b2World *world, int increase)
void NPC_Actor::basic_update(std::shared_ptr<Tent_Actor> actor, std::shared_ptr<Player_Actor> player, const float deltaTime_, b2World *world, int increase)
{
	//b2Vec2 ai_vel = GetComponent<AIComponent>()->seek(player->GetComponent<PhysicsComponent>()->get_body(), 						5.5f, world->GetGravity().y);
	//GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(ai_vel);

	//isWalking = true;

	if(attackLocation == 1)
	{
		if(checkDistanceBetweenPlayer(player.get(), 3.0f))
		{
			//GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));

			isWalking = false;
			isRunning = false;
			isAttacking = true;
			int random = 1 + (rand() % 1000);
		
			if(random == 1)
				player->set_playerIsPoisoned(true);
			if(player->get_playerAdrenalineOn())
				player->set_player_health(player->get_player_health() - 0);
			else if(player->get_player_armor() <= 0)
				player->set_player_health(player->get_player_health() - 0.0001f );
			else
				player->set_player_armor(player->get_player_armor() - 0.0001f );
		}

		else if(!checkDistanceBetweenPlayer(player.get(), 10.0f))
		{
			//this->GetComponent<AIComponent>()->wander(10.0f, 10.0f, 50.0f);
			b2Vec2 ai_vel = GetComponent<AIComponent>()->seek(player->GetComponent<PhysicsComponent>()->get_body(), 
							5.5f + increase * 0.1, world->GetGravity().y);
			GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(ai_vel);
			isWalking = true;
			isRunning = false;
			isAttacking = false;
		}
		else if(checkDistanceBetweenPlayer(player.get(), 10.0f))
		{
			b2Vec2 ai_vel = GetComponent<AIComponent>()->seek(player->GetComponent<PhysicsComponent>()->get_body(), 
							12.5f + increase * 0.01, world->GetGravity().y);
			GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(ai_vel);
			isWalking = false;
			isRunning = true;
			isAttacking = false;
		
		}
		
	}

	else if(attackLocation == 2)
	{
		if(checkDistanceBetweenPlayer(actor.get(), 7.0f))
		{
			//GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
			isWalking = false;
			isRunning = false;
			isAttacking = true;
			if(actor->get_fortify() > 0)
				actor->set_fortify(actor->get_fortify() - 0.0001f );
			else
				actor->set_health(actor->get_health() - 0.0001f );
		}
		else if(!checkDistanceBetweenPlayer(actor.get(), 10.0f))
		{
			//this->GetComponent<AIComponent>()->wander(10.0f, 10.0f, 50.0f);
			b2Vec2 ai_vel = GetComponent<AIComponent>()->seek(actor->GetComponent<PhysicsComponent>()->get_body(), 
							5.5f + increase * 0.1, world->GetGravity().y);
			GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(ai_vel);
			isWalking = true;
			isRunning = false;
			isAttacking = false;
		}
		else if(checkDistanceBetweenPlayer(actor.get(), 60.0f))
		{
			b2Vec2 ai_vel = GetComponent<AIComponent>()->seek(actor->GetComponent<PhysicsComponent>()->get_body(), 
							12.5f + increase * 0.01, world->GetGravity().y);
			GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(ai_vel);
			isWalking = false;
			isRunning = true;
			isAttacking = false;
		

		}
	}


}



void NPC_Actor::update( std::shared_ptr<Player_Actor> player,  const float deltaTime_, b2World *world, bool stateMachineExist)
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

		b2Vec2 ai_vel = GetComponent<AIComponent>()->seek(player->GetComponent<PhysicsComponent>()->get_body(), 						5.5f, world->GetGravity().y);
		GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(ai_vel);

		if(get_health() <=  0)
		{
			 cout << "NPC Physics Removed" << endl;
			 //GetComponent<PhysicsComponent>()->get_body()->/DestroyFixture(GetComponent<PhysicsComponent>()->get_body()->GetFixtureList());
			 //npc_ = nullptr;
			 cout << "NPC DESTROYED!!!" << endl;
		}



if(stateMachineExist){
	//State Machine implementation
	if(stateMachine)
	{
		stateMachine->update(player.get());
		switch(stateMachine->getCurrentStateName())
		{
			case STATE::SEEK:
				this->GetComponent<AIComponent>()->seek(player->GetComponent<PhysicsComponent>()->get_body(), 20.0f, 10.0f);
				//std::cout << "CURRENT STATE : " << " SEEK" << std::endl;
				set_isWalking(false);
				set_isRunning(true);
				break;
			case STATE::WANDER:
				this->GetComponent<AIComponent>()->wander(10.0f, 10.0f, 50.0f);
				//std::cout << "CURRENT STATE : " << " WANDER" << std::endl;
				set_isWalking(true);
				set_isRunning(false);
				break;
			case STATE::ATTACK:
				//GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(b2Vec2_zero);
				//set_isRunning(true);
				//this->GetComponent<AIComponent>()->wander(10.0f, 10.0f, 50.0f);
				//set_isWalking(false);
				//set_isRunning(false);
				player->set_player_health(player->get_player_health() - 0.001f);
				//std::cout << "CURRENT STATE : " << "ATTACK" << std::endl;
				break;
		}
	}
}


}

void NPC_Actor::collison_update(std::shared_ptr<Projectile_Actor> projectile)
{

		if(projectile->checkDistanceBetween(this, 3.0f))
		{
			std::cout << "Projectile Pos " << GetComponent<PhysicsComponent>()->get_body()->GetPosition().x << std::endl;
			std::cout << "Hitting NPC " << std::endl;
			set_health(get_health() - 5);
			projectile->set_projectile_collision(false);

			projectile->GetComponent<PhysicsComponent>()->get_body()->SetTransform(b2Vec2(5, 100 ), 0.0f);
			projectile->GetComponent<PhysicsComponent>()->get_body()->SetEnabled(false);
			projectile->GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
			//projectile->resetBulletPos(10);
		}

	

	//Update the health on the 
	//NEW COLLISION DETECTION
	/*
	for(auto ce = GetComponent<PhysicsComponent>()->get_body()->GetContactList(); ce; ce->next)
	{
		if(ce->other == projectile->GetComponent<PhysicsComponent>()->get_body() && ce->contact->IsTouching())
		{
			std::cout << "GETTING HIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
			set_health(get_health() - 5);
			//projectile->set_projectile_collision(false);
			//npc_collision = false;
		}
		break;
	}
	*/
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
		*/
		















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
