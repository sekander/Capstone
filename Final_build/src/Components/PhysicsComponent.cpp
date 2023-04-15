#include "../../include/Components/PhysicsComponent.h"

#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_math.h>
#include <box2d/b2_types.h>
#include <iostream>
#include <memory>


#include "../../include/GameData/ObjectCounter.h"

using std::cout;
PhysicsComponent::PhysicsComponent(Component* parent_  ) : Component(parent_)
{
	ObjectCounter::physic_component_counter++;
	//Will change implementation
}

PhysicsComponent::~PhysicsComponent()
{
	ObjectCounter::physic_component_counter--;
	
//	onDestroy();
//	cout << "Physics Component Removed\n";
//	glDeleteVertexArrays(1, &this->quadVAO);
}


//bool PhysicsComponent::onCreate(b2World* world,  
bool PhysicsComponent::create_body(b2World* world,  
				bool dynamic, 
				bool set_physics, 
				glm::vec2 position,
				float rotate,
				glm::vec2 size, 
				unsigned int num_x_frames, 
				unsigned int num_y_frames,
				uint16 categoryBits,
				uint16 maskBits)
{

		if (dynamic)
		{
			bodyDef.type = b2_dynamicBody;
		}
		else
		{
			bodyDef.type = b2_staticBody;
		}

		this->body = world->CreateBody(&bodyDef);
		this->body->SetTransform(b2Vec2(position.x, position.y), rotate);
		
		m_physics_enable = set_physics;

		if(set_physics)
			this->body->SetEnabled(true);
		else
		 this->body->SetEnabled(false);
	  	
		this->shape = b2PolygonShape();
	
		
		shape.SetAsBox(size.x/num_x_frames * 0.5f - b2_polygonRadius, 
				      		  size.y/num_y_frames * 0.5f - b2_polygonRadius);

		//this->fixtureDef = new b2FixtureDef();
		fixtureDef = b2FixtureDef();
		//this->fixtureDef = std::make_shared<b2FixtureDef>();
		//this->fixtureDef->shape = this->shape;
		fixtureDef.shape = &shape;
		
		//this->fixtureDef->density = 0.1f;
		//fixtureDef.density = 0.1f;
		fixtureDef.density = 1.0f;

		bodyDef.userData = body->GetUserData();

		fixtureDef.filter.categoryBits = categoryBits;
		fixtureDef.filter.maskBits     = maskBits;		

		//fixtureDef.isSensor = true;
				

		if (dynamic)
		{
			//this->fixtureDef->density = 1.0f;
			fixtureDef.density = 1.0f;
			//this->fixtureDef->friction = 0.3f;
			fixtureDef.friction = 0.3f;
			//this->body->CreateFixture(this->fixtureDef);
			body->CreateFixture(&fixtureDef);
			//this->body->CreateFixture(fixtureDef.get());
		}
		else
		{
			fixtureDef.density = 1.0f;
			//this->fixtureDef->friction = 0.3f;
			fixtureDef.friction = 0.3f;
			//this->body->CreateFixture(this->shape, 0);
			//body->CreateFixture(&shape, 0);
			body->CreateFixture(&fixtureDef);
		}
return true;
}

bool PhysicsComponent::create_kinematic_body(b2World* world,  
				bool set_physics,
				glm::vec2 position,
				float rotate,
				glm::vec2 size, 
				unsigned int num_x_frames, 
				unsigned int num_y_frames,
				uint16 categoryBits,
				uint16 maskBits)
{
		bodyDef.type = b2_kinematicBody;
		
		this->body = world->CreateBody(&bodyDef);
		this->body->SetTransform(b2Vec2(position.x, position.y), rotate);
		
		m_physics_enable = set_physics;

		if(set_physics)
			this->body->SetEnabled(true);
		else
		 this->body->SetEnabled(false);
	  	
		this->shape = b2PolygonShape();
	
		
		shape.SetAsBox(size.x/num_x_frames * 0.5f - b2_polygonRadius, 
				      		  size.y/num_y_frames * 0.5f - b2_polygonRadius);

		//this->fixtureDef = new b2FixtureDef();
		fixtureDef = b2FixtureDef();
		//this->fixtureDef = std::make_shared<b2FixtureDef>();
		//this->fixtureDef->shape = this->shape;
		fixtureDef.shape = &shape;
		
		//this->fixtureDef->density = 0.1f;
		//fixtureDef.density = 0.1f;
		fixtureDef.density = 1.0f;

		bodyDef.userData = body->GetUserData();

		fixtureDef.filter.categoryBits = categoryBits;
		fixtureDef.filter.maskBits     = maskBits;		
			
		{
			//this->fixtureDef->density = 1.0f;
			fixtureDef.density = 1.0f;
			//this->fixtureDef->friction = 0.3f;
			fixtureDef.friction = 0.3f;
			//this->body->CreateFixture(this->fixtureDef);
			body->CreateFixture(&fixtureDef);
			//this->body->CreateFixture(fixtureDef.get());
		}
return true;
}
void PhysicsComponent::createEdeg(b2World* world, float x_point_origin, float y_point_origin, float x_point_dest, float y_point_dest,
		uint16 categoryBits, uint16 maskBits){

	bodyDef = b2BodyDef();
        bodyDef.type = b2_dynamicBody;
	fixtureDef = b2FixtureDef();

        fixtureDef.density = 1;
        fixtureDef.friction = 0;

	fixtureDef.filter.categoryBits = categoryBits;
	fixtureDef.filter.maskBits     = maskBits;

	body = world->CreateBody(&bodyDef);


	edge = b2EdgeShape();
        fixtureDef.shape = &edge;
        
	edge.SetTwoSided( b2Vec2(x_point_origin, y_point_origin),
 				 b2Vec2(x_point_dest, y_point_dest));

        body->CreateFixture(&fixtureDef);
}

void PhysicsComponent::createOneEdeg(b2World* world, float x_point_origin, float y_point_origin, float x_point_dest, float y_point_dest,
		uint16 categoryBits, uint16 maskBits){

	bodyDef = b2BodyDef();
        bodyDef.type = b2_dynamicBody;
	fixtureDef = b2FixtureDef();

        fixtureDef.density = 1;
        fixtureDef.friction = 0;

	fixtureDef.filter.categoryBits = categoryBits;
	fixtureDef.filter.maskBits     = maskBits;

	body = world->CreateBody(&bodyDef);


	edge = b2EdgeShape();
        fixtureDef.shape = &edge;
        
	edge.SetOneSided( b2Vec2(0.0f, 0.0f),
			  b2Vec2(x_point_origin, y_point_origin),
 			  b2Vec2(x_point_dest, y_point_dest),
			  b2Vec2(0.0f, 0.0f));

        body->CreateFixture(&fixtureDef);
}


//void PhysicsComponent::update(const float delta, glm::vec2 position, float rotation) 
void PhysicsComponent::update_body(const float delta, glm::vec2 position, float rotation) 
{
	position.x = this->body->GetPosition().x;
	position.y = this->body->GetPosition().y;
	rotation = this->body->GetAngle();

}

void PhysicsComponent::draw() const
{

}
