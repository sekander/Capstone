#include "../../include/Actors/Shader_Actor.h"
#include "../../include/Actors/Player_Actor.h"
#include "../../include/Actors/Gun_Actor.h"
#include "../../include/Actors/Tent_Actor.h"
#include "../../include/Actors/Projectile_Acotr.h"
#include "../../include/Actors/Edge_Actor.h"
#include "../../include/Components/TransformComponent.h"
#include "../../include/Components/ShaderComponent.h"
#include "../../include/Components/RenderComponent.h"
#include "../../include/Components/PhysicsComponent.h"
#include <box2d/b2_math.h>
#include <cstddef>
#include <memory>

#include "../../include/GameData/GameData.h"
#include <GLFW/glfw3.h>



float jumP_pos;

Player_Actor::Player_Actor(Component* parent_) : Actor(parent_)
{
	AddComponent<TransformComponent>(nullptr);
	AddComponent<RenderComponent>(nullptr);
	AddComponent<PhysicsComponent>(nullptr);
	std::cout << "######################Player Actor Created#######################" << std::endl;
	jump_flag = false;
	floor_flag = false;
	player_collision = false;

	ListComponents();
}  

Player_Actor::~Player_Actor()
{

}

void Player_Actor::InitalizeActor(const char* fileName, 
										  b2World *world, 
											glm::vec2 position, 
											glm::vec2 size, 
											glm::vec2 boxSize, 
											int totalXFrames,
											int totalYFrames,
											int currentXFrame,
											int currentYFrame)
{
	GetComponent<RenderComponent>()->LoadSprite(fileName, position, size, currentXFrame, currentYFrame, 0.0f);
	onCreate(totalXFrames, totalYFrames, currentXFrame, currentYFrame);
	//GetComponent<PhysicsComponent>()->create_body(world, true, true, position, 0.0f, boxSize, currentXFrame, currentYFrame, 0x0004,0x0016 | 0x0008 | 0x0032 | 0x0004 );
	GetComponent<PhysicsComponent>()->create_body(world, true, true, position, 0.0f, 
	boxSize, currentXFrame, currentYFrame, 0x0004, 0x0008 | 0x0032 );
	GetComponent<PhysicsComponent>()->get_body()->SetFixedRotation(true);
	GetComponent<PhysicsComponent>()->get_body()->SetGravityScale(5.25f);

	set_player_health(1000);

	player_right_direction = true;
	player_left_direction = false;

	playItemAnimation = false;
	playerHealedAnimation = false;
	playerReviedAnimation = false;
	playerIsPoisoned = false;

}


//bool Player_Actor::onCreate()
bool Player_Actor::onCreate(int num_x_frame, int num_y_frame, int curr_x_frame, int curr_y_frame)
{
	GetComponent<RenderComponent>()->renderData(num_x_frame, num_y_frame, curr_x_frame, curr_y_frame);
	//GetComponent<RenderComponent>()->initRenderData();
	//GetComponent<RenderComponent>()->renderData();

}

void Player_Actor::onDestroy()
{

}

void Player_Actor::input(GameData* _data )
{
    if (glfwGetKey(_data->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS 
		|| _data->pd.X == 1)
	{
   		set_run_flag(true); 
		set_MoveRight_flag(false);
		set_MoveLeft_flag(false);
		set_notMoving_flag(false);
		//std::cout << "RUNNGIN !!!!!!!" << std::endl;
    }
    else
	    set_run_flag(false);


    if (glfwGetKey(_data->window, GLFW_KEY_D) == GLFW_PRESS
		|| _data->pd.dpadR == 1){
			//set_move_left_flag(false);
			//set_move_flag(true);
			moveRight();    
			set_MoveRight_flag(true);
			set_MoveLeft_flag(false);
			set_notMoving_flag(false);
			//set_shooting_flag(false);
    }
    else if (glfwGetKey(_data->window, GLFW_KEY_A) == GLFW_PRESS
		|| _data->pd.dpadL == 1){
			//set_move_flag(false);
			//set_move_left_flag(true);
			moveLeft();
			set_MoveLeft_flag(true);
			set_MoveRight_flag(false);
			set_notMoving_flag(false);
			//set_shooting_flag(false);
		//player->GetComponent<RenderComponent>()->get_sprite()->set_frames(vec2(2, 2));
    }
    else{
	    stop();
		set_notMoving_flag(true);
		set_MoveRight_flag(false);
		set_MoveLeft_flag(false);
			//set_move_flag(false);
			//set_move_left_flag(false);
		//player->GetComponent<RenderComponent>()->get_sprite()->set_frames(vec2(1, 2));
    }
   


    if (glfwGetKey(_data->window, GLFW_KEY_R) == GLFW_PRESS
		|| _data->pd.Y == 1)
    {
	    set_gun_equipped_flag(true);
    }

    if (glfwGetKey(_data->window, GLFW_KEY_T) == GLFW_PRESS
		|| _data->pd.B == 1)
    {
	    //set_gun_equipped_flag(false);
    }


	if(glfwGetKey(_data->window, GLFW_KEY_M) == GLFW_PRESS || _data->pd.touchPad_5 == 1)
	{
		useMeditKit = true;
	}
	else {
		useMeditKit = false;
	}
	
	if(glfwGetKey(_data->window, GLFW_KEY_P) == GLFW_PRESS || _data->pd.touchPad_6 == 1)
	{
		useAntidote = true;
	}
	else {
		useAntidote = false;
	}












	if(glfwGetKey(_data->window, GLFW_KEY_Y) == GLFW_PRESS || _data->pd.touchPad_8 == 1)
	{
		useAdrenaline = true;
	}
	else {
		useAdrenaline = false;
	}
	
	if(glfwGetKey(_data->window, GLFW_KEY_U) == GLFW_PRESS || _data->pd.touchPad_11 == 1)
	{
		useTrap = true;
	}
	else {
		useTrap = false;
	}

	if(glfwGetKey(_data->window, GLFW_KEY_I) == GLFW_PRESS || _data->pd.touchPad_9 == 1)
	{
		useRepairKit = true;
	}
	else {
		useRepairKit = false;
	}
	
	if(glfwGetKey(_data->window, GLFW_KEY_O) == GLFW_PRESS || _data->pd.touchPad_10 == 1)
	{
		useFortify = true;
	}
	else {
		useFortify = false;
	}







//#############################################################################################################################################
    //TODO Changee the counter variable to its own seperate counter 
    if (glfwGetKey(_data->window, GLFW_KEY_W) == GLFW_PRESS 
		|| _data->pd.dpadU == 1 || _data->pd.A == 1)
    {
		if(get_jump_flag())
      		jump_counter += 0.025f;
      	if(jump_counter > 0.0f  && jump_counter < 0.4f)
      	{
       		//std::cout << "Power Level 1 " << jump_counter << std::endl;
        	jump_press = true;
      	}
      	else if(jump_counter > 0.4f)
      	{
        	//std::cout << "Power Level: " << jump_counter << std::endl;
         	//jump_counter = 0.0f;
         	if(get_jump_flag())
		 	{
           		pressure_sensitve_jump(jump_counter);
           		jump_press = false;
         	}
        	set_jump_flag(false);
        	jump_counter = 0.0f;
      }
    }
    else if (glfwGetKey(_data->window, GLFW_KEY_W) == GLFW_RELEASE
		|| _data->pd.dpadU == 0 || _data->pd.A == 0)
    {
	   if(get_jump_flag())
	   {
		   if(jump_press)
		   {
			   pressure_sensitve_jump(jump_counter);
			   jump_counter = -0.01f;
			   jump_press = false;
		}
		set_jump_flag(false);
	   }
    }
   




  /*
    if (glfwGetKey(_data->window, GLFW_KEY_I) == GLFW_PRESS)
    {	
	   gun_angle = 90.0f;
	   std::cout << "Angle : " << gun_angle << std::endl;
	   if(get_gun_equipped_flag())
		 {
				//TODO write better code for this
				for(auto &bullet : gun->get_projectile_list())
				{
					if(!bullet->GetComponent<PhysicsComponen
t>()->get_physics_enable())
					{
						counter += 0.5f;
						if(counter > 700.0f)
						{
							set_shooting_flag(true);
							bullet->projectile_firin
g(0.0f, -120.0f, gun);
							counter = 0;
							//Add player is shooting
 flag
						}
						set_shooting_flag(false);	
					}
				}

	    }
    }else
			gun_angle = 0.0f;

		if (glfwGetKey(_data->window, GLFW_KEY_L) == GLFW_PRESS
			|| _data->pd.R == 1)
   	{
	    if(get_gun_equipped_flag()){
			shooting_left = false;
			shooting_right = true;

			//TODO write better code for this
			for(auto &bullet : gun->get_projectile_list())
			{
				if(!bullet->GetComponent<PhysicsComponent>()->ge
t_physics_enable())
				{
					counter += 0.5f;
					if(counter > 700.0f)
					{
						set_shooting_flag(true);
						bullet->projectile_firing(120.0f
, 0.0f, gun);
						counter = 0;
					}	
						set_shooting_flag(false);	
				}
			}
	    }
    }
   
   if (glfwGetKey(_data->window, GLFW_KEY_J) == GLFW_PRESS)
   {
	    if(get_gun_equipped_flag()){

			shooting_left = true;
			shooting_right = false;

			//TODO write better code for this
			for(auto &bullet : gun->get_projectile_list())
			{
				if(!bullet->GetComponent<PhysicsComponent>()->ge
t_physics_enable())
				{
					counter += 0.5f;
					if(counter > 700.0f)
					{
						set_shooting_flag(true);
						bullet->projectile_firing(-120.0
f, 0.0f, gun);
						counter = 0;
					}	
						set_shooting_flag(false);	
				}
			}
	    }
    }
		*/
	//Joystick
	//#####################################################################################################################################################################################33   




	/*





		int present = glfwJoystickPresent(GLFW_JOYSTICK_1);
    int axesCount;
    const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
    int buttonsCount;
    const unsigned char *buttons= glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonsCount);

	
       if(present != 0)	       
       		std::cout << "Joystick/Gamepad Connected status: " << present << std::endl;

       if (present == 1) {
            
           //std::cout << "Number of axes available: " << axesCount << std::endl
; 
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
				if(get_jump_flag())
       					jump();
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
   				set_run_flag(true); 
			}
			else{ 
				std::cout << "Button Y was released " << std::endl;
   				set_run_flag(false); 
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

			if(axes[7] == -1 || buttons[11]
				|| _data->pd.dpadU == 1)
			{
				std::cout << "D-PAD UP is pressed" << std::endl;
				jump();
			}
			else
				std::cout << "D-PAD UP is released" << std::endl
;

			if(axes[7] == 1 || buttons[13])
			{	
				std::cout << "D-PAD DOWN is pressed" << std::endl;
			}
			else
				std::cout << "D-PAD DOWN is released" << std::endl;

			if(axes[6] == 1 || buttons[12] 
			|| _data->pd.dpadR == 1)
			{	
				std::cout << "D-PAD RIGHT is pressed" << std::endl;
				moveRight();
			}
			else
				std::cout << "D-PAD RIGHT is released" << std::endl;

			if(axes[6] == -1 || buttons[14]
			|| _data->pd.dpadL == 1)
			{	
				std::cout << "D-PAD LEFT is pressed" << std::endl;
				moveLeft();
			}
			else
				std::cout << "D-PAD LEFT is released" << std::endl;
	   	}


	   	*/

}

bool Player_Actor::pick_up_gun(std::shared_ptr<Gun_Actor> gun)
{

		gun->GetComponent<PhysicsComponent>()->get_body()->SetTransform(b2Vec2(
				GetComponent<PhysicsComponent>()->get_body()->GetPosition().x + 2.0f,
				GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 1.2f ), 0.0f);	

	return true;
}

void Player_Actor::pressure_sensitve_jump(float pressure)
{

	//std::cout << "Pressure test : " << pressure << std::endl;	
	auto physics = GetComponent<PhysicsComponent>()->get_body();
	
	//auto force_y = physics->GetMass() * ((0.25f + pressure) / (1/60.0f));
	auto force_y = physics->GetMass() * ((0.25f + pressure) / (1/60.0f));
	auto force_x = physics->GetMass() * (physics->GetLinearVelocity().x/50 / (1/60.0f));
	physics->ApplyLinearImpulse(b2Vec2(force_x, -force_y), physics->GetWorldCenter(), true);
}

//Update jump so that it checks the edge contatact, player contact, and player y velocity == 0 

void Player_Actor::jump()
{
	auto physics = GetComponent<PhysicsComponent>()->get_body();
	jumP_pos = physics->GetPosition().y;

}

void Player_Actor::moveLeft()
{
	auto vel = GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity();
	if(run_flag)
	{
		vel.x = b2Max( vel.x - 0.1f, -15.0f );
	}
	else {
		if(vel.x < -5.0f)
			vel.x += 0.05f;	
		else if(vel.x >= -5.0f)
			vel.x = b2Max( vel.x - 1.0f, -5.0f );
	}
	GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(vel);

	player_right_direction = false;
	player_left_direction = true;

}

void Player_Actor::moveRight()
{
	auto vel = GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity();
	if(run_flag)
	{
		vel.x = b2Min( vel.x + 0.1f, 15.0f );
	}
	else {
		if(vel.x > 5.0f)
			vel.x -= 0.05f;	
		else if(vel.x <= 5.0f)
			vel.x = b2Min( vel.x + 1.0f, 5.0f );
	}
	GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(vel);

	player_right_direction = true;
	player_left_direction = false;
}

void Player_Actor::stop()
{
	auto vel = GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity();

	if(vel.x > 0)
		vel.x -= 0.5f;	
	if(vel.x < 0)
		vel.x += 0.5f;	

	if(jump_flag)	
	{
		
		if(vel.x > 0)
			vel.x -= 1.0f;	
		if(vel.x < 0)
			vel.x += 1.0f;	
	}
	
	GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(vel);
}


void Player_Actor::update(const float deltaTime_, GameData *_data, Tent_Actor* tent)
{

	if(playerIsPoisoned)
	{
		player_health = player_health - 0.001f;
	}

	if(shooting_flag)
		GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(b2Vec2(0, 
		GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().y));



	//Limit Player speed
	if(GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().x > 15.0f)
	{
		GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(b2Vec2(15.0f, 
			GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().y));
	}
	
	if(GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().x < -15.0f)
	{
		GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(b2Vec2(-15.0f, 
			GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().y));
	}



	//Check if item is used
	//std::cout << "Item Cooldown : " << deltaTime_ - itemUsedTimeStamp << std::endl;
	//ITEM COOLDOWN
		if(playerAdrenalineOn)
		{
			if(deltaTime_ - itemAdrenalineUsedTimeStamp > 30)
				playerAdrenalineOn = false;
		}


		if(deltaTime_ - itemUsedTimeStamp > 15)
			itemMedkitUsed = false;

		if(deltaTime_ - itemAntidoteUsedTimeStamp > 15)
			itemAntidoteUsed = false;
		
		if(deltaTime_ - itemUsedTimeStamp > 1.5f)
			playItemAnimation = false;
		
		if(deltaTime_ - itemAdrenalineUsedTimeStamp > 15)
			itemAdrenalineUsed = false;
		
		if(deltaTime_ - itemRepairKitUsedTimeStamp > 15)
			itemRepairKitUsed = false;
		
		if(deltaTime_ - itemTrapUsedTimeStamp > 15)
			itemTrapUsed = false;
		
		if(deltaTime_ - itemFortifyUsedTimeStamp > 15)
			itemFortifyUsed = false;

		if(useFortify)
		{
			if(!itemFortifyUsed){
				if(get_totalFortify() > 0){
					//play = true;
					set_totalFortify(get_totalFortify()- 1);
					//set_player_health(get_player_health() + 250.0f);

					tent->set_fortify(tent->get_fortify() + 500);
					itemFortifyUsed = true;
					itemFortifyUsedTimeStamp = deltaTime_;
				}
				useFortify = false;
			}
		}

		if(useTrap)
		{
			if(!itemTrapUsed){
				if(get_totalTraps() > 0){
					//play = true;
					set_totalTraps(get_totalTraps()- 1);
					//set_player_health(get_player_health() + 250.0f);
					itemTrapUsed = true;
					itemTrapUsedTimeStamp = deltaTime_;
				}
				useTrap = false;
			}
		}

		if(useRepairKit)
		{
			if(!itemRepairKitUsed){
				if(get_totalRepairKit() > 0){
					playItemRepairKitAnimation = true;
					set_totalRepairKit(get_totalRepairKit()- 1);
					//set_player_health(get_player_health() + 250.0f);
					
					tent->set_health(1000);	
					
					itemRepairKitUsed = true;
					itemRepairKitUsedTimeStamp = deltaTime_;
				}
				useRepairKit = false;
			}
		}
		

		if(useAdrenaline)
		{
			if(!itemAdrenalineUsed){
				if(get_totalAdrenaline() > 0){
					playAdrenalineAnimation = true;
					set_totalAdrenaline(get_totalAdrenaline()- 1);
					playerAdrenalineOn = true;
					//set_player_health(get_player_health() + 250.0f);
					itemAdrenalineUsed = true;
					itemAntidoteUsedTimeStamp = deltaTime_;
				}
				useAdrenaline = false;
			}
		}
		
		if(useMeditKit)
		{
			if(!itemMedkitUsed){
				if(get_totalMedkits() > 0){
					playItemAnimation = true;
					set_totalMedkits(get_totalMedkits()- 1);
					set_player_health(get_player_health() + 250.0f);
					itemMedkitUsed = true;
					itemUsedTimeStamp = deltaTime_;
				}
				useMeditKit = false;
			}
		}
		
		if(useAntidote)
		{
			if(!itemAntidoteUsed){
				if(get_totalAntidotes() > 0){
					//playItemAnimation = true;
					set_totalAntidotes(get_totalAntidotes() - 1);
					//set_player_health(get_player_health() + 250.0f);
					playerIsPoisoned = false;
					itemAntidoteUsed = true;
					itemAntidoteUsedTimeStamp = deltaTime_;
				}
				useAntidote = false;
			}
		}

//	set_jump_flag(true);

		auto physics = GetComponent<PhysicsComponent>()->get_body();
		for(auto ce = physics->GetContactList(); ce; ce->next)
		{
			auto c = ce->contact;
			if(c->IsTouching())
			{
				player_collision = true;
				
				break;
			}
			else 
			{
				player_collision = false;
				break;
			}
		}

	//if(get_gun_equipped_flag())
	//	pick_up_gun(std::shared_ptr<Gun_Actor> gun)
										//_data->pd.y_pos) + 

		_data->pd.x_pos = floor( GetComponent<PhysicsComponent>()->get_body()->GetPosition().x * 100.0) / 100.0;
		_data->pd.y_pos = floor( GetComponent<PhysicsComponent>()->get_body()->GetPosition().y * 100.0) / 100.0;
		_data->pd.playerHealth = get_player_health() / 10;
		_data->pd.totalMedkit = get_totalMedkits();		
		_data->pd.totalEmergencykit = get_totalEmergencykits();
		_data->pd.totalAntidotes = get_totalAntidotes();
		_data->pd.playerArmor = get_player_armor();
		_data->pd.totalAddrenaline = get_totalAdrenaline();
		_data->pd.totalTraps = get_totalTraps();
		_data->pd.totalRepairKit = get_totalRepairKit();
		_data->pd.totalFortify = get_totalFortify();

		//std::cout << &"Inventory Size : " [ get_inventory().size()] << std::endl;	
		
		

		/*		
		
		_data->pd.x_pos_text = std::to_string(GetComponent<PhysicsComponent>()->get_body()->GetPosition().x) + "\n";
		_data->pd.y_pos_text = std::to_string(GetComponent<PhysicsComponent>()->get_body()->GetPosition().y) + "\n";
	
		_data->pd.player_data = std::to_string((int)GetComponent<PhysicsComponent>()->get_body()->GetPosition().x) + "," + 
			std::to_string((int)GetComponent<PhysicsComponent>()->get_body()->GetPosition().y) + "\n";

		_data->pd.player_data =
		
		 std::to_string((int)GetComponent<PhysicsComponent>()->get_body()->GetPosition().x) + "," + 
							 	std::to_string((int)GetComponent<PhysicsComponent>()->get_body()->GetPosition().y) + "\n";

		*/
}


//bool Player_Actor::checkDistanceBetween(std::shared_ptr<PickUps_Actor> pickups, float distance )
bool Player_Actor::checkDistanceBetween(std::shared_ptr<Actor> pickups, float distance )
{
    	auto s = sqrt(pow(this->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x -
						  pickups->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x , 2) +
					  pow(this->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y -
					  	  pickups->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y, 2) * 1.0);


		//std::cout << "Distance: " << s << std::endl;

		

		if(s < distance){
			return true;
		}
		else if(s > distance)
		{
			return false;
		}
		return false;
}


//NEEDS UPDATING
void Player_Actor::check_collision_edge(std::shared_ptr<Edge_Actor> edge)
{
		if(player_collision && edge->get_edge_collision())
		{
		
			set_jump_flag(true);
		
		//		//if(GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().y <  0.001f && 
		//		//GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().y >  -0.001f )
		//		{
		//				jump_flag = true;
		//		}
		}
		//else
		//	jump_flag = false;
}

void Player_Actor::draw(std::shared_ptr<Shader_Actor> shader, glm::mat4 projection, float xpos, float ypos, float boxWidth, float boxHeight, float rot) const
{
	shader->GetComponent<ShaderComponent>()->Use();
         	shader->GetComponent<ShaderComponent>()->SetMatrix4("projection", projection);
          	shader->GetComponent<ShaderComponent>()->SetMatrix4("model", GetComponent<TransformComponent>()->transform(
					vec2(xpos, ypos), 
					vec2(boxWidth, boxHeight), rot));
            shader->GetComponent<ShaderComponent>()->SetVector3f("color", vec3(1.0f, 1.0f, 1.0f));
            //shader->GetComponent<ShaderComponent>()->SetVector3f("color", GetComponent<RenderComponent>()->get_sprite()->get_color());
    //GetComponent<RenderComponent>()->drawSquare();
    GetComponent<RenderComponent>()->drawSprites();
}
