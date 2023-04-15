#include "../../include/Actors/Shader_Actor.h"
#include "../../include/Actors/Gun_Actor.h"
#include "../../include/Actors/Projectile_Acotr.h"


#include "../../include/Components/TransformComponent.h"
#include "../../include/Components/ShaderComponent.h"
#include "../../include/Components/RenderComponent.h"
#include "../../include/Components/PhysicsComponent.h"
#include <memory>


#define MAX_BOXES 250
//#define MAX_BOXES 1

Gun_Actor::Gun_Actor(Component* parent_) : Actor(parent_)
{
	AddComponent<TransformComponent>(nullptr);
	AddComponent<RenderComponent>(nullptr);
	AddComponent<PhysicsComponent>(nullptr);
	std::cout << "######################Projectile Actor Created#######################" << std::endl;
	ListComponents();

}  
Gun_Actor::~Gun_Actor()
{

}

void Gun_Actor::InitalizeActor(const char* fileName, 
											b2World *world, 
											glm::vec2 positon,
											glm::vec2 size,
											glm::vec2 boxSize,
											int totalXFrames,
											int totalYFrames,
											int currentXFrame,
											int currentYFrame)
{
	
		GetComponent<RenderComponent>()->LoadSprite(fileName,
																								positon, 
																								size, 
																								currentXFrame, 
																								currentYFrame, 0.0f);
    onCreate(*world);
    GetComponent<PhysicsComponent>()->create_body(world, true, true, 
       	    					  													positon, 0.0f, 
       						  															boxSize, 
																									currentXFrame, 
																									currentYFrame, 
       						  															0x0064, 0x0008 | 0x0032); 
    GetComponent<PhysicsComponent>()->get_body()->SetFixedRotation(true);
}



bool Gun_Actor::onCreate(b2World& world)
{
	GetComponent<RenderComponent>()->initRenderData();

     for(uint16_t i = 0; i < MAX_BOXES; i++)
     {
		std::shared_ptr<Projectile_Actor> bullet;
		bullet = std::make_shared<Projectile_Actor>(nullptr);
		bullet->onCreate();
	
     	//bullet->GetComponent<PhysicsComponent>()->create_body(&world, true, false, vec2(100 , 200 + i*10), 0.0f, vec2(0.5f, 0.25f), 1, 1, 0x0016, 0x0004 | 0x0002 | 0x0008);
     	bullet->GetComponent<PhysicsComponent>()->create_body(&world, 
		true, 
		false, 
		vec2(100 , 100 + i*10), 
		0.0f, 
		vec2(0.5f, 1.5f), 
		1, 1, 
		//0x0128, 0x0002 | 0x0008);
		0x0128, 0x0004 | 0x0002 | 0x0008);
		bullet->GetComponent<PhysicsComponent>()->get_body()->SetBullet(true);
		bullet->GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
		bullets.push_back(bullet);

	}
}

void Gun_Actor::onDestroy(b2World& world)
{
	for(auto bullet : bullets)
	{
		if(bullet){
		bullet->GetComponent<PhysicsComponent>()->onDestroy();	
		world.DestroyBody(bullet->GetComponent<PhysicsComponent>()->get_body());
		}
	}

	bullets.clear();
}

void Gun_Actor::input()
{
}
void Gun_Actor::update(const float deltaTime_)
{
    //projectile_count++;


//auto square_physics = boxes[i]->GetComponent<PhysicsComponent>();

	for(uint16_t i = 0; i < MAX_BOXES; ++i)
	{
		if(bullets[i])
		{
			//bullets[i]->projectile_collision_update(npc_);
			bullets[i]->resetBulletPos(i);
		}
	}
}

void Gun_Actor::shoot_projectiles()
{
	/*
	for(uint16_t i = 0; i < MAX_BOXES; ++i)
	{
		if(bullets[i])
		{
			auto square_physics = bullets[i]->GetComponent<PhysicsComponent>();
			if(!square_physics->get_physics_enable())
			{
				counter += 0.5f;
				//if(counter > 200.0f)
				if(counter > 700.0f)
				//if(counter > 400.0f)
				{
					bullets[i]->projectile_firing(0.0f, this);
					counter = 0;
				}	
			}
		}
		*/
}

//Can update and make this better 

void Gun_Actor::draw(std::shared_ptr<Shader_Actor> shader, std::shared_ptr<Shader_Actor> bullet_shader,   
glm::mat4 projection, float xpos, float ypos, float boxWidth, float boxHeight, float rot) const
{
	/*
	shader->GetComponent<ShaderComponent>()->Use();
         	shader->GetComponent<ShaderComponent>()->SetMatrix4("projection", projection);
          	shader->GetComponent<ShaderComponent>()->SetMatrix4("model", GetComponent<TransformComponent>()->transform(
					vec2(xpos, ypos), 
					vec2(boxWidth, boxHeight), rot));
            shader->GetComponent<ShaderComponent>()->SetVector3f("color", vec3(1.0f, 1.0f, 1.0f));
        GetComponent<RenderComponent>()->drawSprites();
		*/
        //GetComponent<RenderComponent>()->drawSquare();
	
	for(uint16_t i =0; i < MAX_BOXES; ++i)
	{
	       if(bullets[i])
	       {	
			   		bullets[i]->draw(bullet_shader, projection, 
			     	bullets[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x, 
			   	  	bullets[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 0.2f,
			   	  	//bullets[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y,
			     	0.5, 0.25f, 0.0f);
		   }
	}
}
