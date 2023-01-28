#include "../../include/Actors/Shader_Actor.h"
#include "../../include/Actors/Projectile_Acotr.h"
#include "../../include/Components/TransformComponent.h"
#include "../../include/Components/ShaderComponent.h"
#include "../../include/Components/RenderComponent.h"
#include "../../include/Components/PhysicsComponent.h"
#include <memory>


Projectile_Actor::Projectile_Actor(Component* parent_) : Actor(parent_)
{
	AddComponent<TransformComponent>(nullptr);
	AddComponent<RenderComponent>(nullptr);
	AddComponent<PhysicsComponent>(nullptr);
	std::cout << "######################Projectile Actor Created#######################" << std::endl;
	ListComponents();

	//in Ball class constructor
	projectile_collision = false;	
	//GetComponent<PhysicsComponent>()->get_body()->GetUserData()


  	projectile_counter = 0.0f;
	
	projectile_shooting_right = false;
	projectile_shooting_up = false;
	projectile_shooting_left = false;
	projectile_shooting_down = false;
}  

Projectile_Actor::~Projectile_Actor()
{

}

bool Projectile_Actor::onCreate()
{
	GetComponent<RenderComponent>()->initRenderData();

}

void Projectile_Actor::onDestroy()
{

}

void Projectile_Actor::input()
{
}
void Projectile_Actor::update(const float deltaTime_)
{
    //projectile_count++;


//auto square_physics = boxes[i]->GetComponent<PhysicsComponent>();

	int i = 0;
	auto square_physics = GetComponent<PhysicsComponent>();
	for(auto ce = square_physics->get_body()->GetContactList(); ce; ce->next)
	{
		auto c = ce->contact;
		if(c->IsTouching())
		{
			projectile_collision = true;
			
			std::cout << "Bullet Collided" << std::endl;

			square_physics->get_body()->SetTransform(b2Vec2(5, 20 + i*1), 0.0f);
			square_physics->get_body()->SetEnabled(false);
			square_physics->get_body()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
			i++;
			//if(i > MAX_BOXES/2)
		     		//square_physics->create_body(_data->world, true, false, 
				//vec2(30 , 200 + (i - MAX_BOXES/2)*10), 0.0f, vec2(10.0f, 10.0f), 1, 1);      
			

			break;
		}
		else 
		{
			//std::cout << "Not touching"  << std::endl;
			projectile_collision = false;
			break;
		}
	}

}


void Projectile_Actor::projectile_firing(float projectil_vel_x, float projectile_vel_y, std::shared_ptr<Gun_Actor> spawnLoc)
{
	auto square_physics = GetComponent<PhysicsComponent>();
			square_physics->get_body()->SetBullet(true);
			square_physics->get_body()->SetEnabled(true);


			if(square_physics->get_body()->GetLinearVelocity().x ==  0 && projectil_vel_x > 0.0f)
			{
				projectile_shooting_right = true;					
				projectile_shooting_up = false;					
				square_physics->get_body()->SetTransform(b2Vec2(spawnLoc->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x + 2.0f, 
										spawnLoc->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 0.2f), 0.0f);
				
				square_physics->get_body()->SetLinearVelocity(b2Vec2(projectil_vel_x, projectile_vel_y ));
			}
			else if(square_physics->get_body()->GetLinearVelocity().x ==  0 && projectil_vel_x < 0.0f)
			{
				projectile_shooting_left = true;					
				projectile_shooting_right = false;					
				projectile_shooting_up = false;					
				square_physics->get_body()->SetTransform(b2Vec2(spawnLoc->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 4.0f, 
										spawnLoc->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 0.2f), 0.0f);
				
				square_physics->get_body()->SetLinearVelocity(b2Vec2(projectil_vel_x, projectile_vel_y ));
			}
			else if(square_physics->get_body()->GetLinearVelocity().x ==  0 && projectile_vel_y < 0.0f)
			{
				projectile_shooting_right = false;					
				projectile_shooting_left = false;					
				projectile_shooting_up = true;					
				square_physics->get_body()->SetTransform(b2Vec2(spawnLoc->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x  + 0.5f, 
										spawnLoc->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 1.2f), 0.0f);
				
				square_physics->get_body()->SetLinearVelocity(b2Vec2(projectil_vel_x, projectile_vel_y ));
			}
}

void Projectile_Actor::projectile_collision_update(std::shared_ptr<NPC_Actor> actor)
{

	int i = 0;
	auto square_physics = GetComponent<PhysicsComponent>();
	for(auto ce = square_physics->get_body()->GetContactList(); ce; ce->next)
	{
		auto c = ce->contact;
		if(c->IsTouching())
		{
			projectile_collision = true;
			if(actor){
				if(projectile_collision && actor->get_collision())
				{
					std::cout << "NPC GOT HIT!!!" << std::endl;
					auto new_health = actor->get_health() - 1;
					actor->set_health(new_health);
					actor->set_colour(vec3(1.0f, 0.0f, 0.0f));
				}
			}

			square_physics->get_body()->SetTransform(b2Vec2(5, 20 + i*1), 0.0f);
			square_physics->get_body()->SetEnabled(false);
			square_physics->get_body()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
			i++;
			//if(i > MAX_BOXES/2)
		     		//square_physics->create_body(_data->world, true, false, 
				//vec2(30 , 200 + (i - MAX_BOXES/2)*10), 0.0f, vec2(10.0f, 10.0f), 1, 1);      
			

			projectile_collision = false;
			break;
		}
		else 
		{
			//std::cout << "Not touching"  << std::endl;
			projectile_collision = false;
			break;
		}
	}
}

void Projectile_Actor::resetBulletPos(int i)
{
	auto square_physics = GetComponent<PhysicsComponent>();
	square_physics->get_body()->SetBullet(true);
	if(projectile_shooting_right)
		square_physics->get_body()->SetLinearVelocity(b2Vec2(square_physics->get_body()->GetLinearVelocity().x, -1.0f)); 
	if(projectile_shooting_up)
		square_physics->get_body()->SetLinearVelocity(b2Vec2(0.0f, square_physics->get_body()->GetLinearVelocity().y)); 
	
	
	
	//			player->GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().x, -1));
	if(square_physics->get_body()->GetPosition().x > 9000)
	{
		square_physics->get_body()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
		square_physics->get_body()->SetEnabled(false);
		square_physics->get_body()->SetTransform(b2Vec2(5, 20 + i*1), 0.0f);
		//if(i > MAX_BOXES/2)
		//	square_physics->create_body(_data->world, true, false, vec2(30 , 200 + (i - MAX_BOXES/2)*10), 0.0f, vec2(10.0f, 10.0f), 1, 1);      
	}

/*	
	if(square_physics->get_body()->GetLinearVelocity().y > 1.0f || 
	   square_physics->get_body()->GetLinearVelocity().y < -1.0f)
	{
		square_physics->get_body()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
		square_physics->get_body()->SetEnabled(false);
		square_physics->get_body()->SetTransform(b2Vec2(5, 20 + i*1), 0.0f);
		//if(i > MAX_BOXES/2)
		//	square_physics->create_body(_data->world, true, false, vec2(30 , 200 + (i - MAX_BOXES/2)*10), 0.0f, vec2(10.0f, 10.0f), 1, 1);      
	}
*/
}

void Projectile_Actor::draw(std::shared_ptr<Shader_Actor> shader, glm::mat4 projection, float xpos, float ypos, float boxWidth, float boxHeight, float rot) const
{
	shader->GetComponent<ShaderComponent>()->Use();
         	shader->GetComponent<ShaderComponent>()->SetMatrix4("projection", projection);
          	shader->GetComponent<ShaderComponent>()->SetMatrix4("model", GetComponent<TransformComponent>()->transform(
					vec2(xpos, ypos), 
					vec2(boxWidth, boxHeight), rot));
            shader->GetComponent<ShaderComponent>()->SetVector3f("color", vec3(0.0f, 0.8f, 0.8f));
        GetComponent<RenderComponent>()->drawSquare();
}
