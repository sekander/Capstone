#pragma once

#include "../Components/Component.h"
#include "Actor.h"
#include <glm/fwd.hpp>


class Shader_Actor;
class Edge_Actor : public Actor {

public:
	Edge_Actor(Component* parent_);
	~Edge_Actor();

	bool onCreate(glm::vec2 orign, glm::vec2 dest, float r_ = 1.0f, float g_ = 0.0f, float b_ = 0.0f);
	void onDestroy();
	void update(const float deltaTime_);
	void input();
	void draw(std::shared_ptr<Shader_Actor> shader, glm::mat4 projection) const;


	bool get_edge_collision(){return edge_collision;}
	void set_xo(float xo_){xo = xo_;}
	float get_xo(){return xo;}
	void set_xd(float xd_){xd = xd_;}
	float get_xd(){return xd;}
	void set_yo(float yo_){yo = yo_;}
	float get_yo(){return yo;}
	void set_yd(float yd_){yd = yd_;}
	float get_yd(){return yd;}

private:
	float r, g, b;
	bool edge_collision;
	float xo, yo, xd, yd;

};
