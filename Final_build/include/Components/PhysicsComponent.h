#pragma once

#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_settings.h>
#include <box2d/b2_types.h>
#include <box2d/b2_world.h>
#include <box2d/b2_world_callbacks.h>
#include <cstdio>
#include <glm/glm.hpp>


#include "Component.h"
#include <box2d/box2d.h>
#include <memory>


class PhysicsComponent : public Component
{

enum _entityCategory {
        ALL     =           0x0001,
        PLAYER  =           0x0002,
        NPC     =           0x0004,
        FLOOR   =           0x0008,
        BULLETS =           0x0016
};


	public:
		PhysicsComponent (Component* parent_ );
		~PhysicsComponent ();
		bool onCreate()override {return false;} 
		bool create_kinematic_body(b2World* world, bool set_physics, glm::vec2 position, float rotation, glm::vec2 size, unsigned int num_x_frames = 1, unsigned int num_y_frames = 1, uint16 categoryBits = 0x0001, uint16 maskBits = 0xFFFF);
		bool create_body(b2World* world, bool dynamic, bool set_physics, glm::vec2 position, float rotation, glm::vec2 size, unsigned int num_x_frames = 1, unsigned int num_y_frames = 1, uint16 categoryBits = 0x0001, uint16 maskBits = 0xFFFF);
		void createEdeg(b2World* world, float x_point_origin, float y_point_origin, float x_point_dest, float y_point_dest, 
				uint16 categoryBits = 0x0001, uint16 maskBits = 0xFFFF);
		void createOneEdeg(b2World* world, float x_point_origin, float y_point_origin, float x_point_dest, float y_point_dest, 
				uint16 categoryBits = 0x0001, uint16 maskBits = 0xFFFF);
		void onDestroy() override{
//			printf("Deleting Box2D objects \n");
//			glDeleteVertexArrays(1, &this->quadVAO);
//			printf( "DEBUG DELETION\n");
//			edge = nullptr;
//			delete edge;
			//this->fixtureDef = nullptr;
			//this->shape = nullptr; 
			//this->bodyDef = nullptr;
			//delete fixtureDef;
			//delete shape;
			//delete bodyDef;
//			printf("LAST DEBUG DELETION######\n");
		}
		
		void update(const float delta) override{}
		void update_body(const float delta, glm::vec2 position, float rotation);
		void draw() const override;

		b2Body* get_body(){return body;}
		//b2Body get_body(){return body;}
		//std::shared_ptr<b2Body> get_body(){return body;}

		bool get_physics_enable(){return m_physics_enable;}
		b2FixtureDef get_fixture(){return fixtureDef;}

		b2EdgeShape get_edge(){return edge;}	
		b2PolygonShape get_shape(){return shape;}

	private:		
		b2Body* body;
		b2BodyDef bodyDef;
		b2PolygonShape shape;
		b2FixtureDef fixtureDef;
	
		
		bool m_physics_enable;

		b2EdgeShape edge;
		b2CircleShape* circle;

		float xo, yo, xd, yd;

};
