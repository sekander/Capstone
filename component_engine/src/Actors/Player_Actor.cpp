#include "../../include/Actors/Shader_Actor.h"
#include "../../include/Actors/Player_Actor.h"
#include "../../include/Actors/Gun_Actor.h"
#include "../../include/Actors/Edge_Actor.h"
#include "../../include/Components/TransformComponent.h"
#include "../../include/Components/ShaderComponent.h"
#include "../../include/Components/RenderComponent.h"
#include "../../include/Components/PhysicsComponent.h"
#include <box2d/b2_math.h>



float jumP_pos;

Player_Actor::Player_Actor(Component* parent_) : Actor(parent_)
{
	AddComponent<TransformComponent>(nullptr);
	AddComponent<RenderComponent>(nullptr);
	AddComponent<PhysicsComponent>(nullptr);
	std::cout << "######################Player Actor Created#######################" << std::endl;
	jump_flag = false;
	floor_flag = false;
	player_collision = false;

	ListComponents();
}  

Player_Actor::~Player_Actor()
{

}

//bool Player_Actor::onCreate()
bool Player_Actor::onCreate(int num_x_frame, int num_y_frame, int curr_x_frame, int curr_y_frame)
{
	GetComponent<RenderComponent>()->renderData(num_x_frame, num_y_frame, curr_x_frame, curr_y_frame);
	//GetComponent<RenderComponent>()->initRenderData();
	//GetComponent<RenderComponent>()->renderData();

}

void Player_Actor::onDestroy()
{

}

void Player_Actor::input()
{
}

bool Player_Actor::pick_up_gun(std::shared_ptr<Gun_Actor> gun)
{

		gun->GetComponent<PhysicsComponent>()->get_body()->SetTransform(b2Vec2(
				GetComponent<PhysicsComponent>()->get_body()->GetPosition().x + 2.0f,
				GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 1.2f ), 0.0f);	

	return true;
}

void Player_Actor::pressure_sensitve_jump(float pressure)
{

	std::cout << "Pressure test : " << pressure << std::endl;	
	auto physics = GetComponent<PhysicsComponent>()->get_body();
	
	//auto force_y = physics->GetMass() * ((0.25f + pressure) / (1/60.0f));
	auto force_y = physics->GetMass() * ((0.25f + pressure) / (1/60.0f));
	auto force_x = physics->GetMass() * (physics->GetLinearVelocity().x/50 / (1/60.0f));
	physics->ApplyLinearImpulse(b2Vec2(force_x, -force_y), physics->GetWorldCenter(), true);
}

//Update jump so that it checks the edge contatact, player contact, and player y velocity == 0 

void Player_Actor::jump()
{
	auto physics = GetComponent<PhysicsComponent>()->get_body();
	jumP_pos = physics->GetPosition().y;

}

void Player_Actor::moveLeft()
{
	auto vel = GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity();
	if(run_flag)
	{
		vel.x = b2Max( vel.x - 0.1f, -15.0f );
	}
	else {
		if(vel.x < -5.0f)
			vel.x += 0.05f;	
		else if(vel.x >= -5.0f)
			vel.x = b2Max( vel.x - 1.0f, -5.0f );
	}
	GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(vel);

}

void Player_Actor::moveRight()
{
	auto vel = GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity();
	if(run_flag)
	{
		vel.x = b2Min( vel.x + 0.1f, 15.0f );
	}
	else {
		if(vel.x > 5.0f)
			vel.x -= 0.05f;	
		else if(vel.x <= 5.0f)
			vel.x = b2Min( vel.x + 1.0f, 5.0f );
	}
	GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(vel);

}

void Player_Actor::stop()
{
	auto vel = GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity();

	if(vel.x > 0)
		vel.x -= 0.5f;	
	if(vel.x < 0)
		vel.x += 0.5f;	

	if(jump_flag)	
	{
		
		if(vel.x > 0)
			vel.x -= 1.0f;	
		if(vel.x < 0)
			vel.x += 1.0f;	
	}
	
	GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(vel);
}


void Player_Actor::update(const float deltaTime_)
{
		auto physics = GetComponent<PhysicsComponent>()->get_body();
		for(auto ce = physics->GetContactList(); ce; ce->next)
		{
			auto c = ce->contact;
			if(c->IsTouching())
			{
				player_collision = true;
				
				break;
			}
			else 
			{
				player_collision = false;
				break;
			}
		}
}

void Player_Actor::check_collision_edge(std::shared_ptr<Edge_Actor> edge)
{
		if(player_collision && edge->get_edge_collision())
		{
				if(GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().y <  0.001f && 
				GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().y >  -0.001f )
				{
						jump_flag = true;
				}
		}
		else
			jump_flag = false;
}

void Player_Actor::draw(std::shared_ptr<Shader_Actor> shader, glm::mat4 projection, float xpos, float ypos, float boxWidth, float boxHeight, float rot) const
{
	shader->GetComponent<ShaderComponent>()->Use();
         	shader->GetComponent<ShaderComponent>()->SetMatrix4("projection", projection);
          	shader->GetComponent<ShaderComponent>()->SetMatrix4("model", GetComponent<TransformComponent>()->transform(
					vec2(xpos, ypos), 
					vec2(boxWidth, boxHeight), rot));
            shader->GetComponent<ShaderComponent>()->SetVector3f("color", vec3(1.0f, 1.0f, 1.0f));
    //GetComponent<RenderComponent>()->drawSquare();
    GetComponent<RenderComponent>()->drawSprites();
}
