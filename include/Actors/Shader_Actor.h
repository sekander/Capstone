#pragma once

#include "../Components/Component.h"
#include "Actor.h"
#include <glm/fwd.hpp>
#include <memory>




class Shader_Actor : public Actor {

public:
	Shader_Actor(Component* parent_);
	~Shader_Actor();

	bool onCreate(const char* vShader, const char* fShader);
	void onDestroy();

  


private:
};
