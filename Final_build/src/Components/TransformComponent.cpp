#include <iostream>
#include "../../include/Components/Component.h"
#include "../../include/Components/TransformComponent.h"

#include "../../include/GameData/ObjectCounter.h"

using std::cout;
TransformComponent::TransformComponent(Component* parent_)
: Component(parent_)
{
	m_position = glm::vec2(0.0f, 0.0f);
	m_scale = glm::vec2(1.0f, 1.0f);
	m_rotation = 0.0f;

	ObjectCounter::transform_component_counter++;
}

TransformComponent::TransformComponent(Component* parent_, 
				       glm::vec2 pos_,
				       float rot_,
				       glm::vec2 scale_) :
					Component{parent_},
					m_position{pos_},
					m_rotation{rot_},
					m_scale{scale_}	{}

TransformComponent::~TransformComponent(){
	//cout << "Tranform Component Removed\n";
	ObjectCounter::transform_component_counter--;
}

bool TransformComponent::onCreate(){return true;}

void TransformComponent::onDestroy(){}

void TransformComponent::update(const float delta)
{
	std::cout << "Hello from Transform " << delta << std::endl;
}

void TransformComponent::draw()const {}

mat4 TransformComponent::transform(vec2 position, vec2 size, float rotate, vec3 colour)
{
	mat4 model = mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to center of quad
    	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
//    	model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale
    	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back



    	model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale
	
	
	return model;
}
