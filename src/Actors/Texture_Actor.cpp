#include "../../include/Actors/Shader_Actor.h"

#include "../../include/Actors/Texture_Actor.h"
#include "../../include/Components/TransformComponent.h"
#include "../../include/Components/ShaderComponent.h"
#include "../../include/Components/RenderComponent.h"
#include <memory>
#include <GLFW/glfw3.h>


Texture_Actor::Texture_Actor(Component* parent_) : Actor(parent_)
{
	AddComponent<TransformComponent>(nullptr);
	AddComponent<RenderComponent>(nullptr);
	std::cout << "######################Texture Actor Created#######################" << std::endl;
	ListComponents();

}  

Texture_Actor::~Texture_Actor()
{

}

//bool Texture_Actor::onCreate()
bool Texture_Actor::onCreate(int num_x_frames, int num_y_frames, int current_x_frame, int current_y_frame)
{
	//GetComponent<RenderComponent>()->initRenderData();
	GetComponent<RenderComponent>()->renderData(num_x_frames, num_y_frames, current_x_frame, current_y_frame);

	curr_frame = 1;
}

void Texture_Actor::onDestroy()
{

}

void Texture_Actor::input()
{
}
void Texture_Actor::update(const float deltaTime_)
{
    //projectile_count++;
			double current_time = glfwGetTime();
			if(current_time - animation_last_time >= 0.1)
			{
				//cout << "Old animation: "  << i << endl;
				++curr_frame;
				GetComponent<RenderComponent>()->get_sprite()->set_frames(
					glm::vec2(
						curr_frame,
						GetComponent<RenderComponent>()->get_sprite()->get_frame().y
						)
				);
				//slower
				//last_time += 0.5;
				animation_last_time += 0.1;
				//Faster animation
				//last_time += 0.01;

				if(curr_frame > 3)
					curr_frame = 0;
			}

}

void Texture_Actor::draw(std::shared_ptr<Shader_Actor> shader,  glm::mat4 projection, float xpos, float ypos, float boxWidth, float boxHeight, float rot) const
{
	shader->GetComponent<ShaderComponent>()->Use();
    		shader->GetComponent<ShaderComponent>()->SetMatrix4("projection", projection);
    		shader->GetComponent<ShaderComponent>()->SetMatrix4("model", GetComponent<TransformComponent>()->transform(
					vec2(xpos, ypos), 
					vec2(boxWidth, boxHeight), rot));
    		shader->GetComponent<ShaderComponent>()->SetVector3f("color", vec3(1.0f));
    GetComponent<RenderComponent>()->drawSprites();
}
