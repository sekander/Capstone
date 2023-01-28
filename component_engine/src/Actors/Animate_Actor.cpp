#include "../../include/Actors/Shader_Actor.h"

#include "../../include/Actors/Texture_Actor.h"
#include "../../include/Actors/Animate_Actor.h"
#include "../../include/Components/TransformComponent.h"
#include "../../include/Components/ShaderComponent.h"
#include "../../include/Components/RenderComponent.h"
#include <memory>
#include <GLFW/glfw3.h>


Animate_Actor::Animate_Actor(Component* parent_) : Actor(parent_)
{
	AddComponent<TransformComponent>(nullptr);
	AddComponent<RenderComponent>(nullptr);
	std::cout << "######################ANIMATION Actor Created#######################" << std::endl;
	ListComponents();
	curr_frame = 0;

}  

Animate_Actor::~Animate_Actor()
{
	std::cout << "#####################################################################################ANIAMTION Destroyed#####################################################################################\n";
	animation.clear();
	animation.resize(0);
	animation.shrink_to_fit();
}

//bool Animate_Actor::onCreate()
bool Animate_Actor::onCreate(const char* fileName, glm::vec2 position, glm::vec2 size, int numXFrames, int numYFrames, float rotate, glm::vec3 colour, glm::vec2 currentFrame, bool isAlpha)
{
	max_frame = numXFrames;

	GetComponent<RenderComponent>()->initRenderData();
	while(curr_frame <= numXFrames)
	{
		std::cout << "########################################FRAME IS BEING CREATED######################################" << std::endl;
		texture = std::make_shared<Texture_Actor>(nullptr);
		texture->GetComponent<RenderComponent>()->LoadSprite(fileName, position, size, numXFrames, numYFrames, rotate, colour, glm::vec2(curr_frame, currentFrame.y), isAlpha);
	
		texture->GetComponent<RenderComponent>()->renderData(
			numXFrames,
			numYFrames,
			curr_frame, 
			currentFrame.y);
		
		animation.push_back(texture);
		curr_frame++;
	}
}

void Animate_Actor::onDestroy()
{

}

void Animate_Actor::input()
{
}
void Animate_Actor::update(const float deltaTime_)
{
	double current_time = glfwGetTime();
	if(current_time - animation_last_time >= 0.1)
	{
		if(animation_frame >= max_frame)
			animation_frame = 0;
		
		//std::cout <<  " Animation Frame : " << animation_frame << std::endl;
		
		++animation_frame;
		//slower
		//last_time += 0.5;
		animation_last_time += 0.1;
		//Faster animation
		//last_time += 0.01;
	
	}
}

void Animate_Actor::draw(std::shared_ptr<Shader_Actor> shader,  glm::mat4 projection, float xpos, float ypos, float boxWidth, float boxHeight, float rot) const
{
	if(animation_frame <= max_frame)
		animation[animation_frame]->draw(shader, projection, xpos, ypos, boxWidth, boxHeight, rot);
}
