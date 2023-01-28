#pragma once

#include "../Components/Component.h"
#include "Actor.h"
#include <glm/fwd.hpp>
#include <memory>



class Shader_Actor;
class Texture_Actor: public Actor {

public:
	Texture_Actor(Component* parent_);
	~Texture_Actor();

	bool onCreate(int num_x_frames, int num_y_frames, int current_x_frame, int current_y_frame);
	void onDestroy();
	void update(const float deltaTime_);
	void input();
	void draw(std::shared_ptr<Shader_Actor> shader, glm::mat4 projection, float xpos, float ypos, float boxWidth, float bowHeight, float rot) const;

  
	float get_currFrame(){return curr_frame;}
	void set_currFrame(float frame){curr_frame = frame;}
	void change_currGrame(){
		curr_frame = curr_frame + 1;
	}

private:

	double animation_last_time;
	float curr_frame;
};
