#include "../../include/Actors/Shader_Actor.h"
#include "../../include/Actors/PickUps_Actor.h"


#include "../../include/Components/TransformComponent.h"
#include "../../include/Components/ShaderComponent.h"
#include "../../include/Components/RenderComponent.h"
#include "../../include/Components/PhysicsComponent.h"
#include <memory>


#define MAX_BOXES 250
//#define MAX_BOXES 1

PickUps_Actor::PickUps_Actor(Component* parent_) : Actor(parent_)
{
	AddComponent<TransformComponent>(nullptr);
	AddComponent<RenderComponent>(nullptr);
	AddComponent<PhysicsComponent>(nullptr);
	std::cout << "######################Projectile Actor Created#######################" << std::endl;
	ListComponents();

}  
PickUps_Actor::~PickUps_Actor()
{

}

void PickUps_Actor::InitalizeActor(const char* fileName,
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
       						  									0x0064, 0x0004 ); 
       						  									//0x0064, 0x0008 | 0x0032); 
    GetComponent<PhysicsComponent>()->get_body()->SetFixedRotation(true);
}

void PickUps_Actor::InitalizeActor(Texture_Actor *texture,
											b2World *world, 
											glm::vec2 positon,
											glm::vec2 size,
											glm::vec2 boxSize,
											int totalXFrames,
											int totalYFrames,
											int currentXFrame,
											int currentYFrame)
{
	/*
		GetComponent<RenderComponent>()->LoadSprite(fileName,
													positon, 
													size, 
													currentXFrame, 
													currentYFrame, 0.0f);
													*/
	
 

    onCreate(*world);
    GetComponent<PhysicsComponent>()->create_body(world, true, true, 
       	    					  		texture->GetComponent<TransformComponent>()->getPosition(), 0.0f, 
       						  				boxSize, 
									texture->GetComponent<RenderComponent>()->get_sprite()->get_frame().x, 
									texture->GetComponent<RenderComponent>()->get_sprite()->get_frame().y, 
									//currentYFrame, 
       						  															0x0064, 0x0008 | 0x0032); 
    GetComponent<PhysicsComponent>()->get_body()->SetFixedRotation(true);


	//GetComponent<TransformComponent>()->setTranform(vec2 pos, float rot)
}



bool PickUps_Actor::onCreate(b2World& world)
{
	GetComponent<RenderComponent>()->initRenderData();

}

void PickUps_Actor::onDestroy(b2World& world)
{
}

void PickUps_Actor::input()
{
}
void PickUps_Actor::update(const float deltaTime_)
{
}

//Can update and make this better 

void PickUps_Actor::draw(std::shared_ptr<Shader_Actor> shader,
glm::mat4 projection, float xpos, float ypos, float boxWidth, float boxHeight, float rot) const
{
	shader->GetComponent<ShaderComponent>()->Use();
         	shader->GetComponent<ShaderComponent>()->SetMatrix4("projection", projection);
          	shader->GetComponent<ShaderComponent>()->SetMatrix4("model", GetComponent<TransformComponent>()->transform(
					vec2(xpos, ypos), 
					vec2(boxWidth, boxHeight), rot));
            shader->GetComponent<ShaderComponent>()->SetVector3f("color", vec3(1.0f, 1.0f, 1.0f));
        GetComponent<RenderComponent>()->drawSprites();
        //GetComponent<RenderComponent>()->drawSquare();
	
}

void PickUps_Actor::draw(Texture_Actor *texture, std::shared_ptr<Shader_Actor> shader,
glm::mat4 projection, float xpos, float ypos, float boxWidth, float boxHeight, float rot) const
{
	shader->GetComponent<ShaderComponent>()->Use();
         	shader->GetComponent<ShaderComponent>()->SetMatrix4("projection", projection);
          	shader->GetComponent<ShaderComponent>()->SetMatrix4("model", GetComponent<TransformComponent>()->transform(
					vec2(xpos, ypos), 
					vec2(boxWidth, boxHeight), rot));
            shader->GetComponent<ShaderComponent>()->SetVector3f("color", vec3(1.0f, 1.0f, 1.0f));
        texture->GetComponent<RenderComponent>()->drawSprites();
        //GetComponent<RenderComponent>()->drawSquare();
	
}
