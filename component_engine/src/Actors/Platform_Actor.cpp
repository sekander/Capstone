#include "../../include/Actors/Shader_Actor.h"
#include "../../include/Actors/Platform_Actor.h"
#include "../../include/Components/TransformComponent.h"
#include "../../include/Components/ShaderComponent.h"
#include "../../include/Components/RenderComponent.h"
#include "../../include/Components/PhysicsComponent.h"


Platform_Actor::Platform_Actor(Component* parent_) : Actor(parent_)
{
	AddComponent<TransformComponent>(nullptr);
	AddComponent<RenderComponent>(nullptr);
	AddComponent<PhysicsComponent>(nullptr);
	std::cout << "######################Projectile Actor Created#######################" << std::endl;
	ListComponents();

    //projectile_count = 0;
}  

Platform_Actor::~Platform_Actor()
{

}

bool Platform_Actor::onCreate()
{
	GetComponent<RenderComponent>()->initRenderData();

}

void Platform_Actor::onDestroy()
{

}

void Platform_Actor::input()
{
}
void Platform_Actor::update(const float deltaTime_)
{
    //projectile_count++;

				auto square_physics = GetComponent<PhysicsComponent>();
				for(auto ce = square_physics->get_body()->GetContactList(); ce; ce->next)
				{
					auto c = ce->contact;
					if(c->IsTouching())
					{
						std::cout << "Bullet Touched Another Body\n";
						square_physics->get_body()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
						square_physics->get_body()->SetEnabled(false);
						//square_physics->get_body()->SetTransform(b2Vec2(50, 200 + Projectile_Actor::projectile_count * 10), 0.0f);
						square_physics->get_body()->SetTransform(b2Vec2(50, 200 + 10), 0.0f);
						//if(i > MAX_BOXES/2)
			     				//square_physics->create_body(_data->world, true, false, 
							//vec2(30 , 200 + (i - MAX_BOXES/2)*10), 0.0f, vec2(10.0f, 10.0f), 1, 1);      
						break;
					}
					else 
					{
						//std::cout << "Not touching"  << std::endl;
						break;
					}
                }
}

void Platform_Actor::draw(std::shared_ptr<Shader_Actor> shader, glm::mat4 projection, float xpos, float ypos, float boxWidth, float boxHeight, float rot) const
{
	shader->GetComponent<ShaderComponent>()->Use();
         	shader->GetComponent<ShaderComponent>()->SetMatrix4("projection", projection);
          	shader->GetComponent<ShaderComponent>()->SetMatrix4("model", GetComponent<TransformComponent>()->transform(
					vec2(xpos, ypos), 
					vec2(boxWidth, boxHeight), rot));
            shader->GetComponent<ShaderComponent>()->SetVector3f("color", vec3(0.0f, 1.0f, 0.2f));
    GetComponent<RenderComponent>()->drawSquare();
}
