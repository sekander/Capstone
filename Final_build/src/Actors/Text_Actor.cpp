#include "../../include/Actors/Text_Actor.h"
#include "../../include/Components/TransformComponent.h"
#include "../../include/Components/ShaderComponent.h"
#include "../../include/Components/TextRenderComponent.h"
#include <string>




Text_Actor::Text_Actor(Component* parent_) : Actor(parent_)
{
	AddComponent<TransformComponent>(nullptr);
	AddComponent<TextRenderComponent>(nullptr);
	AddComponent<ShaderComponent>(nullptr);
	std::cout << "######################Text Actor Created#######################" << std::endl;
	ListComponents();
}  

Text_Actor::~Text_Actor()
{

}

bool Text_Actor::onCreate(const char* vShader, const char* fShader, std::string textFile, unsigned int fontSize) 
{
	GetComponent<ShaderComponent>()->loadShader(vShader, fShader);
	GetComponent<ShaderComponent>()->SetInteger("text", 0);
	GetComponent<TextRenderComponent>()->onCreate();
	GetComponent<TextRenderComponent>()->Load(textFile, fontSize);

}

void Text_Actor::onDestroy()
{

}

void Text_Actor::input()
{
}
void Text_Actor::update(const float deltaTime_)
{

}

void Text_Actor::draw(glm::mat4 projection, std::string text, float xpos, float ypos, float scale, float r, float g,float b) const
{
	GetComponent<ShaderComponent>()->SetInteger("text", 0);
	GetComponent<ShaderComponent>()->Use();
  		GetComponent<ShaderComponent>()->SetVector3f("textColor", vec3(r, g, b));
  		GetComponent<ShaderComponent>()->SetMatrix4("projection", projection);
  		glm::mat4 model;
  		model = glm::mat4(1.0f);
  		GetComponent<TextRenderComponent>()->RenderText(text, xpos, ypos, scale);
  		GetComponent<ShaderComponent>()->SetMatrix4("model", model);
  	GetComponent<TextRenderComponent>()->draw();
}
