#include "../../include/Actors/Shader_Actor.h""
#include "../../include/Components/ShaderComponent.h"
#include <memory>


Shader_Actor::Shader_Actor(Component* parent_) : Actor(parent_)
{
	AddComponent<ShaderComponent>(nullptr);
	std::cout << "######################Shader Actor Created#######################" << std::endl;
	ListComponents();

}  

Shader_Actor::~Shader_Actor()
{

}

bool Shader_Actor::onCreate(const char* vShader, const char* fShader)
{
	GetComponent<ShaderComponent>()->loadShader(vShader, fShader);
}

void Shader_Actor::onDestroy()
{

}