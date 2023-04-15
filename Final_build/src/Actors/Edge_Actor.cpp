#include "../../include/Actors/Shader_Actor.h"
#include "../../include/Actors/Edge_Actor.h"
#include "../../include/Components/TransformComponent.h"
#include "../../include/Components/ShaderComponent.h"
#include "../../include/Components/RenderComponent.h"
#include "../../include/Components/PhysicsComponent.h"




Edge_Actor::Edge_Actor(Component* parent_) : Actor(parent_)
{
	AddComponent<TransformComponent>(nullptr);
	AddComponent<RenderComponent>(nullptr);
	AddComponent<PhysicsComponent>(nullptr);
	std::cout << "######################Edge Actor Created#######################" << std::endl;
	ListComponents();

	edge_collision = false;
}  

Edge_Actor::~Edge_Actor()
{

}

bool Edge_Actor::onCreate(vec2 origin, vec2 dest, float r_, float g_, float b_)
{
	r = r_;
	g = g_;
	b = b_;

	GetComponent<RenderComponent>()->initLineRenderData(origin, dest);

}

void Edge_Actor::onDestroy()
{

}

void Edge_Actor::input()
{
}
void Edge_Actor::update(const float deltaTime_)
{

				auto square_physics = GetComponent<PhysicsComponent>();
				for(auto ce = square_physics->get_body()->GetContactList(); ce; ce->next)
				{
					auto c = ce->contact;
					if(c->IsTouching())
					{
						edge_collision = true;
						break;
					}
					else 
					{
						break;
					}
        }
}

void Edge_Actor::draw(std::shared_ptr<Shader_Actor> shader, glm::mat4 projection) const
{
	shader->GetComponent<ShaderComponent>()->Use();
        shader->GetComponent<ShaderComponent>()->SetMatrix4("projection", projection);
                glm::mat4 model;
  				model = glm::mat4(1.0f);
  		shader->GetComponent<ShaderComponent>()->SetMatrix4("model", model);
		shader->GetComponent<ShaderComponent>()->SetVector3f("color", vec3(r, g, b));
    GetComponent<RenderComponent>()->drawLine();
}
