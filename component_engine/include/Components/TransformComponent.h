#pragma once

#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using glm::vec2;
using glm::vec3;
using glm::mat4;

class TransformComponent : public Component
{
private: 
	vec2 m_position;
	vec2 m_scale;
	float m_rotation;

public:
	TransformComponent(Component* parent_);	
	TransformComponent(Component* parent_, vec2 pos, float rot, vec2 scale = vec2(1.0f, 1.0f));
	
	~TransformComponent();
	bool onCreate();
	void onDestroy();
	void update(const float deltat);
	void draw() const;

	vec2 getPosition(){return m_position;}
	vec2 getScale(){return m_scale;}
	float getRotation(){return m_rotation;}

	void setTranform(vec2 pos, float rot, vec2 scale = vec2(1.0f, 1.0f))
	{
		m_position = pos;
		m_scale = scale;
		m_rotation = rot;	
	}

	mat4 transform( vec2 position, vec2 size, float rotation, vec3 colour = vec3(1.0f));
};
