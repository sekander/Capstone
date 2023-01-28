//////////////////////////////////////////////////////////////////////////////
///------------------------Component System---------------------------------
#include "../../include/Components/TransformComponent.h"
#include "../../include/Components/ShaderComponent.h"
#include "../../include/Components/RenderComponent.h"
#include "../../include/Components/TextRenderComponent.h"
#include "../../include/Components/PhysicsComponent.h"
#include "../../include/Components/AIComponent.h"


//////////////////////////////////////////////////////////////////////////////
///------------------------Actors---------------------------------
#include "../../include/Actors/Shader_Actor.h"
#include "../../include/Actors/Texture_Actor.h"

#include "../../include/Actors/Actor.h"
#include "../../include/Actors/Player_Actor.h"
#include "../../include/Actors/NPC_Actor.h"
#include "../../include/Actors/Text_Actor.h"
#include "../../include/Actors/Edge_Actor.h"
#include "../../include/Actors/Projectile_Acotr.h"
#include "../../include/Actors/Platform_Actor.h"
#include "../../include/Actors/Gun_Actor.h"


#include "../../include/Actors/Animate_Actor.h"




#include "../../include/GameData/GameData.h"
#include "../../include/States/game_play_state.h"
#include "../../include/Loaders/LoadingGameObjects.h"
#include <GLFW/glfw3.h>
#include <box2d/b2_math.h>
#include <glm/fwd.hpp>
#include <memory>
#include <string>


//#define MAX_BOXES 1
#define MAX_BOXES 250
//#define MAX_BOXES_TEST 1
#define MAX_BOXES_TEST 200 

// settings
const uint16_t SCR_WIDTH = 800;
const uint16_t SCR_HEIGHT = 600;


glm::mat4 projection1 = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH),
            static_cast<float>(SCR_HEIGHT), 0.0f, -1.0f, 1.0f);



//####################################################################################
//####################################################################################
//Organize all this 

//MY SHADERS
std::shared_ptr<Shader_Actor> shader;
std::shared_ptr<Shader_Actor> texture_shader;
std::shared_ptr<Text_Actor> text;

std::vector<std::shared_ptr<Projectile_Actor>> boxes;

std::shared_ptr<Player_Actor> player;
std::shared_ptr<Gun_Actor> gun;

//ALL OF THESES ACTORS WILL BE PLACED IN XML
std::shared_ptr<NPC_Actor> npc_;
std::shared_ptr<NPC_Actor> npc_1;
std::shared_ptr<NPC_Actor> npc_2;










std::shared_ptr<NPC_Actor> _npcFlee;


std::shared_ptr<Platform_Actor> platform;









std::shared_ptr<Animate_Actor> test_animation;
std::shared_ptr<Animate_Actor> test2_animation;
std::shared_ptr<Animate_Actor> red_animation;



double game_state_last_time = glfwGetTime();
int i = 0;

double game_play_last_time = glfwGetTime();

GamePlayState::GamePlayState(GameData &data) : _data(std::move(&data)) 
{
	shader = std::make_shared<Shader_Actor>(nullptr);
	shader->onCreate("shaders/sprite.vs", "shaders/simpleTriangle.fs");

	texture_shader = std::make_shared<Shader_Actor>(nullptr);
	texture_shader->onCreate("shaders/sprite.vs", "shaders/sprite.fs");
	

	//Physics Code Starts Here
	//###########################################################################################################################
    text = std::make_shared<Text_Actor>(nullptr);
    text->onCreate("shaders/text.vs", "shaders/text.fs", "assets/font/Antonio-Bold.ttf", 25);

    player = std::make_shared<Player_Actor>(nullptr);
	player->GetComponent<RenderComponent>()->LoadSprite("assets/images/red.png", vec2(400, 19), vec2(95, 128), 3, 4, 0.0f);
	//player->GetComponent<RenderComponent>()->LoadSprite("assets/images/red.png", vec2(20, 19), vec2(95, 128), 3, 4, 0.0f);
	//player->GetComponent<RenderComponent>()->renderData(3, 4, 1, 2);
	player->onCreate(3, 4, 1, 2);
	player->GetComponent<PhysicsComponent>()->create_body(_data->world, true, true, 
		    					  vec2(20, 19), 0.0f, 
		    					  //vec2(400, 19), 0.0f, 
							  vec2(2, 2), 1, 1, 
							  NPC, BULLETS | FLOOR | PLATFORM | 0x0004); 
							  //MAINPALYER, BULLETS | FLOOR | PLATFORM); 
    player->GetComponent<PhysicsComponent>()->get_body()->SetFixedRotation(true);
    player->GetComponent<PhysicsComponent>()->get_body()->SetGravityScale(5.25f);



	red_animation = std::make_shared<Animate_Actor>(nullptr);
	red_animation->onCreate("assets/images/red.png", vec2(50, 59), vec2(95, 128), 3, 4, 0.0f, vec3(1.0f), vec2(1, 0), true);

	test_animation = std::make_shared<Animate_Actor>(nullptr);
	test_animation->onCreate("assets/images/Cyborg_run.png", vec2(52, 59), vec2(288, 48), 6, 1, 0.0f, vec3(1.0f), vec2(1, 1), true);
//
	test2_animation = std::make_shared<Animate_Actor>(nullptr);
	test2_animation->onCreate("assets/images/Cyborg_run.png", vec2(55, 59), vec2(288, 48), 6, 1, 0.0f, vec3(1.0f), vec2(1, 1), true);

    gun = std::make_shared<Gun_Actor>(nullptr);
	gun->GetComponent<RenderComponent>()->LoadSprite("assets/images/2_1.png", vec2(15, 19), vec2(22, 8), 1, 1, 0.0f);

	//gun->GetComponent<RenderComponent>()->renderData(3, 4, 1, 2);
    gun->onCreate(*_data->world);
    gun->GetComponent<PhysicsComponent>()->create_body(_data->world, true, true, 
       	    					  vec2(15, 19), 0.0f, 
       						  vec2(2, 1), 1, 1, 
       						  GUN, FLOOR | PLATFORM ); 
    gun->GetComponent<PhysicsComponent>()->get_body()->SetFixedRotation(true);






//#############################################################################################################################################################
//#############################################################################################################################################################
//#############################################################################################################################################################
    npc_ = std::make_shared<NPC_Actor>(nullptr);
	npc_->GetComponent<RenderComponent>()->LoadSprite("assets/images/Idle.png", vec2(99, 19), vec2(192, 48), 1, 1, 0.0f);
	npc_->GetComponent<RenderComponent>()->renderData(4, 1, 1, 1);
    npc_->GetComponent<PhysicsComponent>()->create_body(_data->world, true, true, 
	     				vec2(99, 19), 0.0f, 
						vec2(2.3f, 4), 1, 1, NPC, FLOOR | BULLETS | 0x0004);      
    npc_->GetComponent<AIComponent>()->Init(npc_->GetComponent<PhysicsComponent>()->get_body());
    npc_->set_health(100);

	//npc_->readStateMachine("");
    
	npc_2 = std::make_shared<NPC_Actor>(nullptr);
	npc_2->GetComponent<RenderComponent>()->LoadSprite("assets/images/Idle.png", vec2(199, 19), vec2(192, 48), 1, 1, 0.0f);
	npc_2->GetComponent<RenderComponent>()->renderData(4, 1, 1, 1);
    npc_2->GetComponent<PhysicsComponent>()->create_body(_data->world, true, true, 
	     				vec2(500, 39), 0.0f, 
						vec2(2.3f, 4), 1, 1, NPC, FLOOR | BULLETS | 0x0004);      
    npc_2->GetComponent<AIComponent>()->Init(npc_2->GetComponent<PhysicsComponent>()->get_body());
    npc_2->set_health(100);
	npc_2->readStateMachine("");

/*    
	npc_1 = std::make_shared<NPC_Actor>(nullptr);
	npc_1->GetComponent<RenderComponent>()->LoadSprite("assets/images/Idle.png", vec2(199, 19), vec2(192, 48), 1, 1, 0.0f);
	npc_1->GetComponent<RenderComponent>()->renderData(4, 1, 1, 1);
    npc_1->GetComponent<PhysicsComponent>()->create_body(_data->world, true, true, 
	     				vec2(199, 19), 0.0f, 
						vec2(2.3f, 4), 1, 1, NPC, FLOOR | BULLETS | 0x0004);      
    npc_1->GetComponent<AIComponent>()->Init(npc_->GetComponent<PhysicsComponent>()->get_body());
    npc_1->set_health(100);
	npc_1->set_colour(vec3(1.0f, 0.0f, 0.0f));

*/


//Create 10 different NPC with animation 



































    _npcFlee = std::make_shared<NPC_Actor>(nullptr);
	_npcFlee->GetComponent<RenderComponent>()->LoadSprite("assets/images/Idle.png", vec2(38, 19), vec2(192, 48), 1, 1, 0.0f);
	_npcFlee->GetComponent<RenderComponent>()->renderData(4, 1, 1, 3);
    _npcFlee->GetComponent<PhysicsComponent>()->create_body(_data->world, true, true, 
		     			vec2(30, 19), 0.0f, 
						vec2(2.3f, 4), 1, 1, NPC, FLOOR | BULLETS | 0x0004);      
    _npcFlee->GetComponent<AIComponent>()->Init(_npcFlee->GetComponent<PhysicsComponent>()->get_body());
    _npcFlee->set_health(100);
    _npcFlee->GetComponent<AIComponent>()->populateAIPositions('A', b2Vec2(20.0f, 0.0f));
	_npcFlee->GetComponent<AIComponent>()->populateAIPositions('B', b2Vec2(50.0f, 0.0f));
	_npcFlee->GetComponent<AIComponent>()->populateAIPositions('C', b2Vec2(15.0f, 0.0f));
	_npcFlee->GetComponent<AIComponent>()->populateAIPositions('D', b2Vec2(30.0f, 0.0f));

//#############################################################################################################################################################
//#############################################################################################################################################################
//#############################################################################################################################################################
 
 
 
 
 
    //Can delete this code 
    platform = std::make_shared<Platform_Actor>(nullptr);
    platform->onCreate();
    platform->GetComponent<PhysicsComponent>()->create_kinematic_body(_data->world, true, vec2(380, 12), 0.0f, 
						vec2(10, 2), 1, 1, PLATFORM, PLAYER | NPC | FLOOR | GUN);      
    platform->GetComponent<PhysicsComponent>()->get_body()->SetGravityScale(0.0f);
	

    for(uint16_t i = 0; i < MAX_BOXES_TEST; i++)
    {
		std::shared_ptr<Projectile_Actor> box;
		box = std::make_shared<Projectile_Actor>(nullptr);
		box->onCreate();

		if(i < MAX_BOXES_TEST * 0.10)	
     		box->GetComponent<PhysicsComponent>()->create_body(_data->world, true, true, vec2(100 + i*1, 0 ), 0.0f, vec2(1.0f, 1.0f), 1, 1, BULLETS, NPC | PLAYER | FLOOR);      
		else if(i > MAX_BOXES_TEST * 0.10 && i < MAX_BOXES_TEST * 0.20)
     		box->GetComponent<PhysicsComponent>()->create_body(_data->world, true, true, vec2(101 + i*1 - MAX_BOXES_TEST * 0.1, 1), 0.0f, vec2(1.0f, 1.0f), 1, 1, BULLETS, NPC | PLAYER | FLOOR);      
		else if(i > MAX_BOXES_TEST * 0.20 && i < MAX_BOXES_TEST * 0.30)
     		box->GetComponent<PhysicsComponent>()->create_body(_data->world, true, true, vec2(101 + i*1 - MAX_BOXES_TEST * 0.2, 2), 0.0f, vec2(1.0f, 1.0f), 1, 1, BULLETS, NPC | PLAYER | FLOOR);      
		else if(i > MAX_BOXES_TEST * 0.30 && i < MAX_BOXES_TEST * 0.40)
     		box->GetComponent<PhysicsComponent>()->create_body(_data->world, true, true, vec2(101 + i*1 - MAX_BOXES_TEST * 0.3, 3), 0.0f, vec2(1.0f, 1.0f), 1, 1, BULLETS, NPC | PLAYER | FLOOR);      
		else if(i > MAX_BOXES_TEST * 0.40 && i < MAX_BOXES_TEST * 0.50)
     		box->GetComponent<PhysicsComponent>()->create_body(_data->world, true, true, vec2(101 + i*1 - MAX_BOXES_TEST * 0.4, 4), 0.0f, vec2(1.0f, 1.0f), 1, 1, BULLETS, NPC | PLAYER | FLOOR);      
		else if(i > MAX_BOXES_TEST * 0.50 && i < MAX_BOXES_TEST * 0.60)
     		box->GetComponent<PhysicsComponent>()->create_body(_data->world, true, true, vec2(101 + i*1 - MAX_BOXES_TEST * 0.5, 5), 0.0f, vec2(1.0f, 1.0f), 1, 1, BULLETS, NPC | PLAYER | FLOOR);      
		else if(i > MAX_BOXES_TEST * 0.60 && i < MAX_BOXES_TEST * 0.70)
     		box->GetComponent<PhysicsComponent>()->create_body(_data->world, true, true, vec2(101 + i*1 - MAX_BOXES_TEST * 0.6, 6), 0.0f, vec2(1.0f, 1.0f), 1, 1, BULLETS, NPC | PLAYER | FLOOR);      
		else if(i > MAX_BOXES_TEST * 0.7 && i < MAX_BOXES_TEST * 0.8)
     		box->GetComponent<PhysicsComponent>()->create_body(_data->world, true, true, vec2(101 + i*1 - MAX_BOXES_TEST * 0.7, 7), 0.0f, vec2(1.0f, 1.0f), 1, 1, BULLETS, NPC | PLAYER | FLOOR);      
		else if(i > MAX_BOXES_TEST * 0.8 && i < MAX_BOXES_TEST * 0.9)
     		box->GetComponent<PhysicsComponent>()->create_body(_data->world, true, true, vec2(101 + i*1 - MAX_BOXES_TEST * 0.8, 8), 0.0f, vec2(1.0f, 1.0f), 1, 1, BULLETS, NPC | PLAYER | FLOOR);      
		else
     		box->GetComponent<PhysicsComponent>()->create_body(_data->world, true, true, vec2(102 + i*1 - MAX_BOXES_TEST * 0.9, 13), 0.0f, vec2(1.0f, 1.0f), 1, 1, BULLETS, NPC | PLAYER | FLOOR);      

		boxes.push_back(box);

     }
    
    x_cam = -5.0f;
    y_cam = 180.0f;
	z_cam = 0.0f;
	r_cam = 0.0f;

	z_scale.x = 4.54f;
	z_scale.y = 4.54f;

    _data->o_cam->SetPosition(glm::vec3(x_cam, y_cam, z_cam));
}
GamePlayState::~GamePlayState()
{
    printf("Deleting GAME PLAY State\n");
}
void GamePlayState::DeleteData()
{
    printf("Deleting GAME PLAY State\n");

    for(auto &actor : _data->ld->return_game_objects())
	actor.first->GetComponent<RenderComponent>()->onDestroy();
    
    text->GetComponent<TextRenderComponent>()->onDestroy();

//Physics Code Deletion Starts Here
//#############################################################################################################################################
/*
	red_animation->getAnimation().clear();
	red_animation->getAnimation().resize(0);

	test_animation->getAnimation().clear();
	test_animation->getAnimation().resize(0);


	test2_animation->getAnimation().clear();
	test2_animation->getAnimation().resize(0);
*/	

//	red_animation->onDestroy();
//	test_animation->onDestroy();
//	test2_animation->onDestroy();


    if(player){
    	player->GetComponent<PhysicsComponent>()->onDestroy();
    	_data->world->DestroyBody(player->GetComponent<PhysicsComponent>()->get_body());
    }
    
	if(gun){
    	gun->GetComponent<PhysicsComponent>()->onDestroy();
    	_data->world->DestroyBody(gun->GetComponent<PhysicsComponent>()->get_body());
    }
    
    if(npc_){
    	npc_->GetComponent<PhysicsComponent>()->onDestroy();
    	_data->world->DestroyBody(npc_->GetComponent<PhysicsComponent>()->get_body());
    }
    
    if(platform){
    	platform->GetComponent<PhysicsComponent>()->onDestroy();
    	_data->world->DestroyBody(platform->GetComponent<PhysicsComponent>()->get_body());
    }
   
    for(auto &edges : _data->ld->return_edge_game_objects() )
    {
	edges.first->GetComponent<PhysicsComponent>()->onDestroy();
	_data->world->DestroyBody(edges.first->GetComponent<PhysicsComponent>()->get_body());
    }
    
    for(auto &npc : _data->ld->return_npc_game_objects() )
    {
	npc.first->GetComponent<PhysicsComponent>()->onDestroy();
	_data->world->DestroyBody(npc.first->GetComponent<PhysicsComponent>()->get_body());
    }
	
    for(auto &platform : _data->ld->return_platform_game_objects() )
    {
	platform.first->GetComponent<PhysicsComponent>()->onDestroy();
	_data->world->DestroyBody(platform.first->GetComponent<PhysicsComponent>()->get_body());
    }


    gun->onDestroy(*_data->world);


    for(auto box : boxes)
    {
	if(box){
	box->GetComponent<PhysicsComponent>()->onDestroy();	
	_data->world->DestroyBody(box->GetComponent<PhysicsComponent>()->get_body());
	}
    }

    _data->ld->return_edge_game_objects().clear();
    _data->ld->return_npc_game_objects().clear();
    _data->ld->return_platform_game_objects().clear();
    boxes.clear();
    delete _data->world;

//#############################################################################################################################################
	

    _data->ld->return_game_objects().clear();
    delete _data->ld;
}
void GamePlayState::Init()
{
    printf("Hello GAME PLAY Init************************************************************************\n");

//###########################################################################################################################
	  x_pos = 0.0f;
	  y_pos = 0.0f;

 
    for(auto &edge : _data->ld->return_edge_game_objects())
    {
        edge.first->onCreate(glm::vec2(edge.first->get_xo() + 1.0f, edge.first->get_yo() + 1.0f), 
                             glm::vec2(edge.first->get_xd() + 1.0f, edge.first->get_yd() + 1.0f));
    }

    for(auto &platform : _data->ld->return_platform_game_objects())
    {
        platform.first->onCreate();
    }


	if(_data->level == LEVEL_1)
	{
		_data->ld->Load_XML_ASSETS("assets/xml/game_settings.xml", "level_1"); 
	}
	else if(_data->level == LEVEL_2)
	{
		_data->ld->Load_XML_ASSETS("assets/xml/game_settings.xml", "level_2"); 
	}
    

	counter = 0.0f;	
}
void GamePlayState::SoundUpdate()
{
    //printf("Hello Game Play Sound UPdate\n");
}
void GamePlayState::Input(float delta)
{
    if (glfwGetKey(_data->window, GLFW_KEY_N) == GLFW_PRESS)
	{
		_data->level = LEVEL_2;
		_data->state_switch = LOADING_PLAY_STATE;
	}
    
	if (glfwGetKey(_data->window, GLFW_KEY_M) == GLFW_PRESS)
	{
		_data->level = LEVEL_1;
		_data->state_switch = LOADING_PLAY_STATE;
	}
//Player Input Starts Here
//#############################################################################################################################################

    if (glfwGetKey(_data->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ){
   	player->set_run_flag(true); 
    }
    else
	    player->set_run_flag(false);

    if (glfwGetKey(_data->window, GLFW_KEY_D) == GLFW_PRESS ){
		player->moveRight();
		
    
    }
    else if (glfwGetKey(_data->window, GLFW_KEY_A) == GLFW_PRESS){
		player->moveLeft();
		player->GetComponent<RenderComponent>()->get_sprite()->set_frames(vec2(2, 2));
    }
    else{
	    player->stop();
		player->GetComponent<RenderComponent>()->get_sprite()->set_frames(vec2(1, 2));
    }
   
    if (glfwGetKey(_data->window, GLFW_KEY_R) == GLFW_PRESS)
    {
	    player->set_gun_equipped_flag(true);
    }
    if (glfwGetKey(_data->window, GLFW_KEY_T) == GLFW_PRESS)
    {
	    player->set_gun_equipped_flag(false);
    }
//#############################################################################################################################################
   
    if (glfwGetKey(_data->window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
       if(npc_)
       {
         cout << "NPC Physics Removed" << endl;
         npc_->GetComponent<PhysicsComponent>()->get_body()->DestroyFixture(npc_->GetComponent<PhysicsComponent>()->get_body()->GetFixtureList());
         npc_ = nullptr;
         cout << "NPC DESTROYED!!!" << endl;
       }
    }

    //TODO Changee the counter variable to its own seperate counter 
    if (glfwGetKey(_data->window, GLFW_KEY_W) == GLFW_PRESS)
    {
		if(player->get_jump_flag())
      		jump_counter += 0.025f;
      if(jump_counter > 0.0f  && jump_counter < 0.4f)
      {
         std::cout << "Power Level 1 " << jump_counter << std::endl;
         jump_press = true;
      }
      else if(jump_counter > 0.4f)
      {
         std::cout << "Power Level: " << jump_counter << std::endl;
         //jump_counter = 0.0f;
         if(player->get_jump_flag()){
           player->pressure_sensitve_jump(jump_counter);
           jump_press = false;
         }
         player->set_jump_flag(false);
        jump_counter = 0.0f;
      }
    }
    else if (glfwGetKey(_data->window, GLFW_KEY_W) == GLFW_RELEASE)
    {
	   if(player->get_jump_flag()){
		   if(jump_press)
		   {
			   player->pressure_sensitve_jump(jump_counter);
			   jump_counter = -0.01f;
			   jump_press = false;
		}
		player->set_jump_flag(false);
	   }
    }
   

    if (glfwGetKey(_data->window, GLFW_KEY_I) == GLFW_PRESS)
    {	
	   gun_angle = 90.0f;
	   std::cout << "Angle : " << gun_angle << std::endl;
	   if(player->get_gun_equipped_flag())
		 {
				//TODO write better code for this
				for(auto &bullet : gun->get_projectile_list())
				{
					if(!bullet->GetComponent<PhysicsComponent>()->get_physics_enable())
					{
						counter += 0.5f;
						if(counter > 700.0f)
						{
							bullet->projectile_firing(0.0f, -120.0f, gun);
							counter = 0;
						}	
					}
				}
	    }
    }else
			gun_angle = 0.0f;

		if (glfwGetKey(_data->window, GLFW_KEY_L) == GLFW_PRESS)
   	{
	    if(player->get_gun_equipped_flag()){
			shooting_left = false;
			shooting_right = true;

			//TODO write better code for this
			for(auto &bullet : gun->get_projectile_list())
			{
				if(!bullet->GetComponent<PhysicsComponent>()->get_physics_enable())
				{
					counter += 0.5f;
					if(counter > 700.0f)
					{
						bullet->projectile_firing(120.0f, 0.0f, gun);
						counter = 0;
					}	
				}
			}
	    }
    }
   
   if (glfwGetKey(_data->window, GLFW_KEY_J) == GLFW_PRESS)
   {
	    if(player->get_gun_equipped_flag()){

			shooting_left = true;
			shooting_right = false;

			//TODO write better code for this
			for(auto &bullet : gun->get_projectile_list())
			{
				if(!bullet->GetComponent<PhysicsComponent>()->get_physics_enable())
				{
					counter += 0.5f;
					if(counter > 700.0f)
					{
						bullet->projectile_firing(-120.0f, 0.0f, gun);
						counter = 0;
					}	
				}
			}
	    }
    }
   
    if (glfwGetKey(_data->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
	    x_cam -=5.0f;
            std::cout << "X cam : " << x_cam  << std::endl;
    }
    if (glfwGetKey(_data->window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
	    x_cam +=5.0f;
            std::cout << "X cam : " << x_cam  << std::endl;
    }
    if (glfwGetKey(_data->window, GLFW_KEY_UP) == GLFW_PRESS)
    {
	    y_cam +=5.0f;
	    std::cout << "Y cam : " << y_cam  << std::endl;
    }
    if (glfwGetKey(_data->window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
	    y_cam -=5.0f;
            std::cout << "Y cam : " << y_cam  << std::endl;
    }
    if (glfwGetKey(_data->window, GLFW_KEY_E) == GLFW_PRESS)
    {
	    r_cam +=0.001;
            std::cout << "R cam : " << r_cam  << std::endl;
    }
    if (glfwGetKey(_data->window, GLFW_KEY_Q) == GLFW_PRESS)
    {
	    r_cam -=0.001;
            std::cout << "R cam : " << r_cam  << std::endl;
    }
    if (glfwGetKey(_data->window, GLFW_KEY_Z) == GLFW_PRESS)
    {
	    z_scale.x += 0.1;
	    z_scale.y += 0.1;
            std::cout << "Z-x cam : " << z_scale.x << std::endl;
            std::cout << "Z-y cam : " << z_scale.y << std::endl;
    }
    if (glfwGetKey(_data->window, GLFW_KEY_X) == GLFW_PRESS)
    {
	    z_scale.x -= 0.1;
	    z_scale.y -= 0.1;
            std::cout << "Z-x cam : " << z_scale.x << std::endl;
            std::cout << "Z-y cam : " << z_scale.y << std::endl;
    }


	//#####################################################################################################################################################################################33   
    int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
    int axesCount;
    const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
    int buttonsCount;
    const unsigned char *buttons= glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonsCount);

	
       if(present != 0)	       
       		std::cout << "Joystick/Gamepad Connected status: " << present << std::endl;

       if (present == 1) {
            
           //std::cout << "Number of axes available: " << axesCount << std::endl; 
           	std::cout << "Axis 1: " << axes[0] << std::endl;
           	std::cout << "Axis 2: " << axes[1] << std::endl; 
           	std::cout << "Axis 4: " << axes[3] << std::endl;
           	std::cout << "Axis 5: " << axes[4] << std::endl;
           
	   		std::cout << "D-PAD UP/DOWN : " << axes[7] << std::endl;
       	    std::cout << "D-PAD LEFT/RIGHT : " << axes[6] << std::endl;
	
       	    std::cout << std::endl; 
       	    std::cout << std::endl;
       	    std::cout << std::endl;

			if(buttons[0])
			{
				std::cout << "Button B was pressed " << std::endl;
				if(player->get_jump_flag())
       					player->jump();
			}
			else 
				std::cout << "Button B was released " << std::endl;

			if(buttons[1])
			{
				std::cout << "Button A was pressed " << std::endl;
			}
			else 
				std::cout << "Button A was released " << std::endl;

			if(buttons[2])
			{
				std::cout << "Button Y was pressed " << std::endl;
   				player->set_run_flag(true); 
			}
			else{ 
				std::cout << "Button Y was released " << std::endl;
   				player->set_run_flag(false); 
			}
			if(buttons[3])
			{
				std::cout << "Button X was pressed " << std::endl;
			}
			else 
				std::cout << "Button X was released " << std::endl;

			if(buttons[4])
			{
				std::cout << "Button L was pressed " << std::endl;
			}
			else 
				std::cout << "Button L was released " << std::endl;

			if(buttons[5])
			{
				std::cout << "Button R was pressed " << std::endl;
			}
			else 
				std::cout << "Button R was released " << std::endl;

			if(axes[2] == 1)
			{
				std::cout << "Button L-TRIGGER was pressed " << std::endl;
			}
			else 
				std::cout << "Button L-TRIGGER was released " << std::endl;

			if(axes[5] == 1)
			{
				std::cout << "Button R-TRIGGER was pressed " << std::endl;
			}
			else 
				std::cout << "Button R-TRIGGER was released " << std::endl;

			if(buttons[6])
			{
				std::cout << "Button SELECT was pressed " << std::endl;
			}
			else 
				std::cout << "Button SELECT was released " << std::endl;

			if(buttons[7])
			{
				std::cout << "Button START was pressed " << std::endl;
			}
			else 
				std::cout << "Button START was released " << std::endl;

			if(buttons[8])
			{
				std::cout << "Button HOME was pressed " << std::endl;
			}
			else 
				std::cout << "Button HOME was released " << std::endl;

			if(buttons[9])
			{
				std::cout << "Button L-CLICK was pressed " << std::endl;
			}
			else 
				std::cout << "Button L-CLICK was released " << std::endl;

			if(buttons[10])
			{
				std::cout << "Button R-CLICK was pressed " << std::endl;
			}
			else 
				std::cout << "Button R-CLICK was released " << std::endl;

			if(axes[7] == -1 || buttons[11])
			{
				std::cout << "D-PAD UP is pressed" << std::endl;
				player->jump();
			}
			else
				std::cout << "D-PAD UP is released" << std::endl;

			if(axes[7] == 1 || buttons[13])
			{	
				std::cout << "D-PAD DOWN is pressed" << std::endl;
			}
			else
				std::cout << "D-PAD DOWN is released" << std::endl;

			if(axes[6] == 1 || buttons[12])
			{	
				std::cout << "D-PAD RIGHT is pressed" << std::endl;
				player->moveRight();
			}
			else
				std::cout << "D-PAD RIGHT is released" << std::endl;

			if(axes[6] == -1 || buttons[14])
			{	
				std::cout << "D-PAD LEFT is pressed" << std::endl;
				player->moveLeft();
			}
			else
				std::cout << "D-PAD LEFT is released" << std::endl;
	   	}
}
void GamePlayState::Update(float delta)
{
	_data->world->Step(1.0f / 60.0f, 8, 2);    
	_data->o_cam->SetPosition(glm::vec3(x_cam, y_cam, z_cam));
	_data->o_cam->SetRotation(r_cam);
	_data->o_cam->SetScale(z_scale);



	/*
	if(_data->level == LEVEL_1)
	{
		std::cout << "Levels : " << _data->level << std::endl;
	}
	else if(_data->level == LEVEL_2)
	{
		std::cout << "Levels : " << _data->level << std::endl;
	}
	*/



//Update this code 
//################################################################################
	for(uint16_t i = 0; i < MAX_BOXES; ++i)
	{
		auto bullets = gun->get_projectile_list();

		if(bullets[i])
		{
			bullets[i]->update(glfwGetTime());
			bullets[i]->resetBulletPos(i);
		}
	}
//################################################################################
	
	for(uint16_t i =0; i < MAX_BOXES_TEST; ++i)
	{
		if(boxes[i])
		{
			auto square_physics = boxes[i]->GetComponent<PhysicsComponent>();
			if(square_physics->get_body()->GetPosition().y > 1800)
			{
				cout << "#############################################################Box Deleted########################################################### \n" << i << endl;
				boxes[i] = nullptr;	
			}
		}else{

		}
	}

//Physics Update Code Starts Here
//##########################################################################################################################################
    if(player)
	{
		player->update(glfwGetTime());
		/*
		if(player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x > SCR_WIDTH/2 && 
		   player->GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().x > 1.0f )
		{
			x_cam += 10.0f;
		//	if(player->GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().x > 80.0f)
		//		x_cam += 1.10f;
		}
		if(player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x > SCR_WIDTH/2 && 
		   player->GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().x < -1.0f )
		{
			x_cam -= 10.0f;
		//	if(player->GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().x < -80.0f)
		}
		
		if( player->GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().y > 1.0f )
		{
			y_cam += 0.1f;
		}
		if( player->GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().y < -1.0f )
		{
			y_cam -= 0.1f;
		}
		*/

		if(player->get_gun_equipped_flag())
			player->pick_up_gun(gun);

		_data->pd.x_pos = player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x;
		_data->pd.y_pos = player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y;
		_data->pd.x_pos_text = std::to_string(player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x) + "\n";
		_data->pd.y_pos_text = std::to_string(player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y) + "\n";
	
		_data->pd.player_data = std::to_string((int)player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x) + "," + 
							 	std::to_string((int)player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y) + "\n";

	}
        
//#############################################################################################################################################################
//#############################################################################################################################################################
//#############################################################################################################################################################
	if(npc_)
	{	
		
		//if(npc_->checkDistanceBetweenPlayer(player.get(), 10.002f))
			//std::cout << "TEST IS TRUE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    	

		//npc_->GetComponent<AIComponent>()->seek(player->GetComponent<PhysicsComponent>()->get_body(), 
		//		_data->world->GetGravity().y);
		b2Vec2 ai_vel = npc_->GetComponent<AIComponent>()->seek(player->GetComponent<PhysicsComponent>()->get_body(), 5.5f, 
						_data->world->GetGravity().y);
		npc_->GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(ai_vel);

		//npc_->update(glfwGetTime());
		npc_->set_colour(glm::vec3(1.0f, 0.0f, 0.4f));

		for(auto &bullet : gun->get_projectile_list())
		{
			npc_->collison_update(bullet);
		}

		if(npc_->get_health() <=  0)
		{
			 cout << "NPC Physics Removed" << endl;
			 npc_->GetComponent<PhysicsComponent>()->get_body()->DestroyFixture(npc_->GetComponent<PhysicsComponent>()->get_body()->GetFixtureList());
			 npc_ = nullptr;
			 cout << "NPC DESTROYED!!!" << endl;
		}


	}


	if(npc_2)
	{	
		
		b2Vec2 ai_vel = npc_2->GetComponent<AIComponent>()->seek(player->GetComponent<PhysicsComponent>()->get_body(), 5.5f, 
						_data->world->GetGravity().y);
		npc_2->GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(ai_vel);
		npc_2->update(player, glfwGetTime());

		npc_2->set_colour(glm::vec3(1.0f, 0.0f, 0.4f));

		for(auto &bullet : gun->get_projectile_list())
		{
			npc_2->collison_update(bullet);
		}

		if(npc_2->get_health() <=  0)
		{
			 cout << "NPC Physics Removed" << endl;
			 npc_2->GetComponent<PhysicsComponent>()->get_body()->DestroyFixture(npc_2->GetComponent<PhysicsComponent>()->get_body()->GetFixtureList());
			 npc_2 = nullptr;
			 cout << "NPC DESTROYED!!!" << endl;
		}
	}










	//Return steering algo update to phsycis body
	if(_npcFlee)
	{	
		_npcFlee->set_colour(glm::vec3(0.0f, 0.2f, 0.8f));
		auto ai = _npcFlee->GetComponent<AIComponent>();
		auto ai_positions = ai->getAIPositions();
		for(int i = 0; i < ai_positions.size(); i++)
		{
			if(!ai_positions[0]->destination)
			{
				//std::cout << "Pos " << ai_positions[0]->key << " : " << ai_positions[0]->position.x << ", " << ai_positions[0]->position.y << std::endl;
				if(ai->moveLeftPosition(ai_positions[0]->position))
				//if(ai->movePosition(ai_positions[0]->position))
				{
					//std::cout << "AI Reached Destination" << std::endl;
					ai_positions[0]->destination = true;
					if(ai_positions[1]->destination)
						ai_positions[1]->destination = false;
				}
			}
			else if(!ai_positions[1]->destination)
			{
				//std::cout << "Pos " << ai_positions[1]->key << " : " << ai_positions[1]->position.x << ", " << ai_positions[1]->position.y << std::endl;
				if(ai->moveRightPosition(ai_positions[1]->position))
				//if(ai->movePosition(ai_positions[0]->position))
				{
					//std::cout << "AI Reached Destination" << std::endl;
					ai_positions[1]->destination = true;
					if(ai_positions[2]->destination)
						ai_positions[2]->destination = false;
				}
			}
			else if(!ai_positions[2]->destination)
			{
				//std::cout << "Pos " << ai_positions[2]->key << " : " << ai_positions[2]->position.x << ", " << ai_positions[2]->position.y << std::endl;
				if(ai->moveLeftPosition(ai_positions[2]->position))
				//if(ai->movePosition(ai_positions[0]->position))
				{
					//std::cout << "AI Reached Destination" << std::endl;
					ai_positions[2]->destination = true;
					if(ai_positions[3]->destination)
						ai_positions[3]->destination = false;
				}
			}
			else if(!ai_positions[3]->destination)
			{
				//std::cout << "Pos " << ai_positions[3]->key << " : " << ai_positions[3]->position.x << ", " << ai_positions[3]->position.y << std::endl;
				if(ai->moveRightPosition(ai_positions[3]->position))
				//if(ai->movePosition(ai_positions[0]->position))
				{
					//std::cout << "AI Reached Destination" << std::endl;
					ai_positions[3]->destination = true;
				}
			}
			else
			{
				//Restart the loop
				printf("AI finished its path"); 
				ai_positions[0]->destination = false;
			}
		}

		for(auto &bullet : gun->get_projectile_list())
		{
			_npcFlee->collison_update(bullet);
		}
		if(_npcFlee->get_health() <= 0)
		{
			 cout << "NPC Physics Removed" << endl;
			 _npcFlee->GetComponent<PhysicsComponent>()->get_body()->DestroyFixture(_npcFlee->GetComponent<PhysicsComponent>()->get_body()->GetFixtureList());
			 _npcFlee = nullptr;
			 cout << "NPC DESTROYED!!!" << endl;
		}
	}

//#############################################################################################################################################################
//#############################################################################################################################################################
//#############################################################################################################################################################
	if(gun)
	{
		float r_wave = 5 * sin(2 * 3.14 * 0.01 * (int)(glfwGetTime() * 100));
		gun->GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(b2Vec2(0.0f, ((r_wave) * 1) ));
	}

	auto actors = _data->ld->return_game_objects();
	for(auto &actor : actors)
	{
		auto actor_render    = actor.first->GetComponent<RenderComponent>();
		if(actor_render->get_sprite()->get_position().y > 800)
		{
			actor.first->onDestroy();	
		}	
	}
	
	auto npc_list = _data->ld->return_npc_game_objects();
	for(auto &npc : npc_list)
	{
		npc.first->update(player, glfwGetTime());
	}
	
 	auto edge_list = _data->ld->return_edge_game_objects();
	for(auto &edge : edge_list)
	{
		edge.first->update(glfwGetTime());
    	player->check_collision_edge(edge.first);
	}
	
	if(platform->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y > 90.0f)
		platform->GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(b2Vec2(0.0f, -50.0f));
	else if(platform->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y < 50.0f)
		platform->GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(b2Vec2(0.0f, 50.0f));


	auto animation_map = _data->ld->return_animation_actors();
	for(auto &index : animation_map)
	{
		for(auto& texture : index.second)
		{
			texture->update(delta);
		}
	}
	if(test_animation)
		test_animation->update(delta);	
	
	if(red_animation)
		red_animation->update(delta);	
	
	if(test2_animation)
		test2_animation->update(delta);	



//##########################################################################################################################################
}
void GamePlayState::Render(float delta)
{
	std::string player_speed = std::to_string(player->GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().x);
	std::string player_speed_y = std::to_string(player->GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().y);
	std::string player_force = std::to_string(player->force_x);
	std::string player_jump_force = std::to_string(player->force);
	text->draw(_data->o_cam->return_matrix(), "new splash text actor", 200, 200);
	text->draw(projection1, "Vel X : " + player_speed, SCR_WIDTH/20 - 20.0f , SCR_HEIGHT/20);
	text->draw(projection1, "Vel Y : " + player_speed_y, SCR_WIDTH/20 - 20.0f , SCR_HEIGHT/20 + 20.0f);
	

	if(test_animation)
		test_animation->draw(texture_shader, _data->o_cam->return_matrix(), 52, 59, 32/2, 48/10, 0.0f);

	if(red_animation)
		red_animation->draw(texture_shader, _data->o_cam->return_matrix(), 58, 59, 32, 32, 0.0f);

	if(test2_animation)
		test2_animation->draw(texture_shader, _data->o_cam->return_matrix(), 55, 59, 32/2, 48/10, 0.0f);

//Physics Draw Code Starts Here
//##########################################################################################################################################
	// Get an iterator pointing to begining of map
	
	/*
	auto it = _data->ld->return_game_objects().begin();
	while(it != _data->ld->return_edge_game_objects().end())
	{
		std::cout<<it->first << " :: "<<it->second<<std::endl;
		it++;
	}
	*/

	auto animation_map = _data->ld->return_animation_actors();
	for(auto &index : animation_map)
	{
		//printf("Frame #: %d\n", i);
		//for(int i = 0; i < index.second.size(); i++)
		{
			//i = index.second[0]->GetComponent<RenderComponent>()->get_sprite()->get_frame().x;

			double current_time = glfwGetTime();
			if(current_time - game_play_last_time >= 0.1)
			{
				//cout << index.first << " Old animation: "  << i << endl;
				++i;
				index.second[0]->change_currGrame();
				//index.second[0]->set_currFrame(index.second[0]->get_currFrame()++);
				//slower
				//last_time += 0.5;
				game_play_last_time += 0.1;
				//Faster animation
				//last_time += 0.01;

				if(i > index.second[0]->GetComponent<RenderComponent>()->get_sprite()->get_num_x_frames() - 1)
					i = 0;
				//if(index.second[0]->get_currFrame() > index.second[0]->GetComponent<RenderComponent>()->get_sprite()->get_num_x_frames() - 1)
				//	index.second[0]->set_currFrame(0);
			}




			auto render = index.second[0]->GetComponent<RenderComponent>();
			index.second[i]->draw(texture_shader, _data->o_cam->return_matrix(),
			//index.second[index.second[0]->get_currFrame()]->draw(texture_shader, _data->o_cam->return_matrix(),
								  render->get_sprite()->get_position().x,
								  render->get_sprite()->get_position().y,
								  render->get_sprite()->get_size().x/10,
								  render->get_sprite()->get_size().y/10,
								  0.0f);
		}

	}

//#############################################################################################################################################################
//#############################################################################################################################################################
//#############################################################################################################################################################
//#############################################################################################################################################################

	auto actors = _data->ld->return_game_objects();
	for(auto &actor : actors)
	{
		//std::cout << "Actors From XML : " << actor.second << std::endl;
		if(actor.first)
		{
			auto actor_render    = actor.first->GetComponent<RenderComponent>();
			reinterpret_cast<Texture_Actor*>(actor.first.get())->draw(texture_shader, 
										  _data->o_cam->return_matrix(),
										  actor_render->get_sprite()->get_position().x,
										  actor_render->get_sprite()->get_position().y,
										  actor_render->get_sprite()->get_size().x/10,
										  actor_render->get_sprite()->get_size().y/10,
										  0.0f);

			if(actor.second == "map")
			{
				auto actor_render    = actor.first->GetComponent<RenderComponent>();
				reinterpret_cast<Texture_Actor*>(actor.first.get())->draw(texture_shader, 
											  _data->o_cam->return_matrix(),
											  actor_render->get_sprite()->get_position().x,
											  actor_render->get_sprite()->get_position().y,
											  actor_render->get_sprite()->get_size().x/10,
											  actor_render->get_sprite()->get_size().y/10,
											  0.0f);
			}

			else if(actor.second == "enemy")
			{
				if(npc_)
				{
				auto actor_render    = actor.first->GetComponent<RenderComponent>();
				reinterpret_cast<Texture_Actor*>(actor.first.get())->draw(texture_shader, 
											  _data->o_cam->return_matrix(),
			     npc_->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 0.65f, 
			     npc_->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 2.0f,
											  actor_render->get_sprite()->get_size().x/10,
											  actor_render->get_sprite()->get_size().y/10,
											  0.0f);
				}
				
				if(_npcFlee)
				{
				auto actor_render    = actor.first->GetComponent<RenderComponent>();
				reinterpret_cast<Texture_Actor*>(actor.first.get())->draw(texture_shader, 
											  _data->o_cam->return_matrix(),
			     _npcFlee->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 0.65f, 
			     _npcFlee->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 2.0f,
											  actor_render->get_sprite()->get_size().x/10,
											  actor_render->get_sprite()->get_size().y/10,
											  0.0f);
				}
			}
		}	
	}

	for(uint16_t i =0; i < MAX_BOXES_TEST; ++i)
	{
	       if(boxes[i])
	       {	
			   	boxes[i]->draw(shader, _data->o_cam->return_matrix(), 
			     	boxes[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x + 0.5f, 
			   	boxes[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y + 0.5f, 
			     	1.0f, 1.0f, 0.0f);
	       }
	       else{}
	}
	if(player)
		player->draw(texture_shader, _data->o_cam->return_matrix(), 
			     player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x, 
			     player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y , 
			     32.0f/4, 32.0f/4, 0.0f);
	
	if(gun){
		if(player->get_gun_equipped_flag()){
			if(shooting_right)
				gun->draw(texture_shader, shader ,_data->o_cam->return_matrix(), 
			     	player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x + 2.0f , 
			     	player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 1.2f, 
			     	2.0f, 1.0f, gun_angle);
		
			
			else if(shooting_left) 
			gun->draw(texture_shader, shader ,_data->o_cam->return_matrix(), 
			     player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 2.0f , 
			     player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 1.2f, 
			     2.0f, 1.0f, gun_angle);


		}
		else	
			gun->draw(texture_shader, shader, _data->o_cam->return_matrix(), 
			     gun->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x, 
			     gun->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y, 
			     2.0f, 1.0f, 0.0f);


	}


	if(npc_){
		npc_->draw(shader, _data->o_cam->return_matrix(), 
			     npc_->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 0.65f, 
			     npc_->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 1.0f ,
			     2.0f, 4.0f, 0.0f);

		std::string npc_health_text = std::to_string(npc_->get_health());	
		text->draw(projection1, "NPC Health : " + npc_health_text, SCR_WIDTH/4 * 3 , SCR_HEIGHT/20, 0.97647f, 0.50196f, 0.02353f);
	}
	
	if(npc_2){
		npc_2->draw(shader, _data->o_cam->return_matrix(), 
			     npc_2->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 0.65f, 
			     npc_2->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 1.0f ,
			     2.0f, 4.0f, 0.0f);
	}
	
	/*
	if(npc_1){
		npc_1->draw(shader, _data->o_cam->return_matrix(), 
			     npc_1->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 0.65f, 
			     npc_1->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 1.0f ,
			     2.0f, 4.0f, 0.0f);
	}
	*/


















	if(_npcFlee){
		//_npcFlee->draw(texture_shader, _data->o_cam->return_matrix(), 
		//	     _npcFlee->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 0.65f, 
		//	     _npcFlee->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 1.0f ,
		//	     32.0f/4, 32.0f/4, 0.0f);
		//	     //2.0f, 4.0f, 0.0f);

		std::string npc_health_text = std::to_string(_npcFlee->get_health());	
		text->draw(projection1, "NPC Health : " + npc_health_text, SCR_WIDTH/4 * 3 , SCR_HEIGHT/20 - 20.f, 0.97647f, 0.20196f, 0.02353f);
	}


//#############################################################################################################################################################
//#############################################################################################################################################################
//#############################################################################################################################################################
//#############################################################################################################################################################




	if(platform)
		platform->draw(shader, _data->o_cam->return_matrix(), 
			     platform->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 4.0f, 
			     platform->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y , 
			     10.0f, 2.0f, 0.0f);
//##########################################################################################################################################
	auto npc_list = _data->ld->return_npc_game_objects();
	for(auto &npc : npc_list)
	{
		if(npc.first)
		{
			auto npc_physcis = npc.first->GetComponent<PhysicsComponent>();
			npc.first->draw(shader, _data->o_cam->return_matrix(), 
							npc_physcis->get_body()->GetPosition().x ,
							npc_physcis->get_body()->GetPosition().y - 2.85f,
							2.0f, 4.0f, 0.0f);
		}
	}
	
	auto platform_list = _data->ld->return_platform_game_objects();
	for(auto &platform_ : platform_list)
	{
		if(platform_.first)
		{
			auto platform_physcis = platform_.first->GetComponent<PhysicsComponent>();
			platform_.first->draw(shader, _data->o_cam->return_matrix(), 
							platform_physcis->get_body()->GetPosition().x - 4.0f,
							platform_physcis->get_body()->GetPosition().y,
							10.0f, 2.0f, 0.0f);
		}
	}


	auto edge_actors = _data->ld->return_edge_game_objects();
	for(auto &edge : edge_actors)
		edge.first->draw(shader, _data->o_cam->return_matrix());

}
