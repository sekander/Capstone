///-------------------------------ALUT--------------------------------------
#include <AL/al.h>
#include <AL/alut.h>
//////////////////////////////////////////////////////////////////////////////
///------------------------Component System---------------------------------
#include "../../include/Components/TransformComponent.h"
#include "../../include/Components/ShaderComponent.h"
#include "../../include/Components/RenderComponent.h"
#include "../../include/Components/TextRenderComponent.h"
#include "../../include/Components/PhysicsComponent.h"
#include "../../include/Components/AIComponent.h"

/////////////////////////////////////////////////////////////////////////////
///------------------------------IMGUI--------------------------------------
#include "../../include/IMGUI/imgui.h"
#include "../../include/IMGUI/imgui_impl_glfw.h"
#include "../../include/IMGUI/imgui_impl_opengl3.h" 

//////////////////////////////////////////////////////////////////////////////
///------------------------Actors---------------------------------
#include "../../include/Actors/Shader_Actor.h"
#include "../../include/Actors/Texture_Actor.h"

#include "../../include/Actors/Actor.h"
#include "../../include/Actors/Player_Actor.h"
#include "../../include/Actors/Tent_Actor.h"
#include "../../include/Actors/NPC_Actor.h"
#include "../../include/Actors/Text_Actor.h"
#include "../../include/Actors/Edge_Actor.h"
#include "../../include/Actors/Projectile_Acotr.h"
#include "../../include/Actors/Platform_Actor.h"
#include "../../include/Actors/Gun_Actor.h"
#include "../../include/Actors/PickUps_Actor.h"



#include "../../include/Actors/Animate_Actor.h"




#include "../../include/GameData/GameData.h"
#include "../../include/States/game_play_state.h"
#include "../../include/Loaders/LoadingGameObjects.h"
#include <GLFW/glfw3.h>
#include <box2d/b2_math.h>
#include <complex>
#include <cstddef>
#include <glm/fwd.hpp>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include <iostream>
#include <cstdlib>

#include "../../include/GameData/ObjectCounter.h"

//#define MAX_BOXES 1
#define MAX_BOXES 250
//#define MAX_BOXES_TEST 1
#define MAX_BOXES_TEST 200 

#define MAX_ENEMIES 1000

// settings
const uint16_t SCR_WIDTH = 800;
const uint16_t SCR_HEIGHT = 600;


glm::mat4 projection1 = glm::ortho(
	0.0f, 
	static_cast<float>(SCR_WIDTH),
    static_cast<float>(SCR_HEIGHT), 
	0.0f, 
	-1.0f, 
	1.0f);

//####################################################################################
//Organize all this 

//MY SHADERS
std::shared_ptr<Shader_Actor> shader;
std::shared_ptr<Shader_Actor> texture_shader;
std::shared_ptr<Text_Actor>   text;
std::shared_ptr<Text_Actor>   tentText;
std::shared_ptr<Text_Actor>   enemyText;
std::shared_ptr<Text_Actor>   roundText;




//std::vector<std::shared_ptr<Projectile_Actor>> boxes;

std::shared_ptr<Player_Actor>  player;
std::shared_ptr<Animate_Actor> player_idle_animation;
std::shared_ptr<Animate_Actor> player_idleLeft_animation;
std::shared_ptr<Animate_Actor> player_shooting_animation;
std::shared_ptr<Animate_Actor> player_shootingLeft_animation;
std::shared_ptr<Animate_Actor> player_walk_animation;
std::shared_ptr<Animate_Actor> player_walkLeft_animation;
std::shared_ptr<Animate_Actor> player_run_animation;
std::shared_ptr<Animate_Actor> player_runLeft_animation;
std::shared_ptr<Animate_Actor> player_death_animation;

std::shared_ptr<Tent_Actor> tent;


std::shared_ptr<Gun_Actor> 	   gun;

//ADD Grenades


std::shared_ptr<PickUps_Actor> antidote;
std::shared_ptr<PickUps_Actor> instantHeal;
std::shared_ptr<PickUps_Actor> medKit;
std::shared_ptr<PickUps_Actor> emergencyKit;

std::shared_ptr<PickUps_Actor> armour;
std::shared_ptr<PickUps_Actor> addrenaline;
std::shared_ptr<PickUps_Actor> repair_kit;
std::shared_ptr<PickUps_Actor> fortify;
std::shared_ptr<PickUps_Actor> trap;

std::shared_ptr<Animate_Actor> 	medkit_animation;
std::shared_ptr<Animate_Actor> 	instantHeal_animation;
std::shared_ptr<Animate_Actor> 	emergencyKit_animation;
std::shared_ptr<Animate_Actor> 	poison_animation;

std::shared_ptr<Animate_Actor> 	armor_animation;
std::shared_ptr<Animate_Actor> 	addrenaline_animation;



std::vector<std::shared_ptr<PickUps_Actor>> antidote_pkg;
std::vector<std::shared_ptr<PickUps_Actor>> instantHeal_pkg;
std::vector<std::shared_ptr<PickUps_Actor>> emergencyKit_pkg;
std::vector<std::shared_ptr<PickUps_Actor>> medKit_pkg;

std::vector<std::shared_ptr<PickUps_Actor>> armour_pkg;
std::vector<std::shared_ptr<PickUps_Actor>> addrenaline_pkg;
std::vector<std::shared_ptr<PickUps_Actor>> trap_pkg;
std::vector<std::shared_ptr<PickUps_Actor>> repair_kit_pkg;
std::vector<std::shared_ptr<PickUps_Actor>> fortify_kit_pkg;

//ALL OF THESES ACTORS WILL BE PLACED IN XML
std::shared_ptr<NPC_Actor> 	    enemy;
std::shared_ptr<Animate_Actor> 	enemy_idle_animation;
std::shared_ptr<Animate_Actor> 	enemy_walk_animation;
std::shared_ptr<Animate_Actor> 	enemy_walkLeft_animation;
std::shared_ptr<Animate_Actor> 	enemy_run_animation;
std::shared_ptr<Animate_Actor> 	enemy_runLeft_animation;
std::shared_ptr<Animate_Actor> 	enemy_attackOne_animation;
std::shared_ptr<Animate_Actor> 	enemy_dead_animation;




std::vector<std::shared_ptr<NPC_Actor>> 	    enemies;
std::vector<std::shared_ptr<Animate_Actor>> 	enemy_idle;
std::vector<std::shared_ptr<Animate_Actor>> 	enemy_walk;
std::vector<std::shared_ptr<Animate_Actor>> 	enemy_walkLeft;
std::vector<std::shared_ptr<Animate_Actor>> 	enemy_run;
std::vector<std::shared_ptr<Animate_Actor>> 	enemy_runLeft;
std::vector<std::shared_ptr<Animate_Actor>> 	enemy_attackOne;
std::vector<std::shared_ptr<Animate_Actor>> 	enemy_dead;



std::shared_ptr<Actor> gp_fade_in_out_actor;                

/*
	IN PROGRESS
	- Add music and sound fx
	- Add fade in and out 
	- Add game play menu screen 
	
	TODO LIST
	- Fix game pause to be more accurate
	- Fix player run animation
	- Complete Game Over screen
	
	Polish
	- Add splash image
	- Add sound fx to menu 

*/


double game_state_last_time = glfwGetTime();
int i = 0;

double game_play_last_time = glfwGetTime();


bool enemyflag[MAX_ENEMIES];

int startingPoint = 0;
int enemiesKilled = 0;

int score;

float player_R, player_G, player_B;


bool meditUpdate[50];
bool healUpdate[50];
bool emergency_kitUpdate[50];
bool antidoteUpdate[50];

bool addrenalineUpdate[50];
bool trapUpdate[50];
bool repairKitUpdate[50];
bool fortifyUpdate[50];
bool armourUpdate[50];



ALuint gp_Buffer, 
	   gp_backgroundSource, 
	   gp_shootBuffer, 
	   gp_shootSource, 
	   gp_jumpSource;

ALint gp_state;

bool gp_stop_audio;
bool gp_stop_update;

bool draw_playerHud;

GamePlayState::GamePlayState(GameData &data) : _data(std::move(&data)) 
{
		shader = std::make_shared<Shader_Actor>(nullptr);		
		texture_shader = std::make_shared<Shader_Actor>(nullptr);
		
		text = std::make_shared<Text_Actor>(nullptr);
		tentText = std::make_shared<Text_Actor>(nullptr);
		enemyText = std::make_shared<Text_Actor>(nullptr);
		roundText = std::make_shared<Text_Actor>(nullptr);
		
		player = std::make_shared<Player_Actor>(nullptr);
		player_walk_animation= std::make_shared<Animate_Actor>(nullptr);
		player_walkLeft_animation = std::make_shared<Animate_Actor>(nullptr);
		player_idle_animation = std::make_shared<Animate_Actor>(nullptr);
		player_idleLeft_animation = std::make_shared<Animate_Actor>(nullptr);
		player_run_animation = std::make_shared<Animate_Actor>(nullptr);
		player_runLeft_animation = std::make_shared<Animate_Actor>(nullptr);
		player_shooting_animation = std::make_shared<Animate_Actor>(nullptr);
		player_shootingLeft_animation = std::make_shared<Animate_Actor>(nullptr);
		player_death_animation = std::make_shared<Animate_Actor>(nullptr);

		gun = std::make_shared<Gun_Actor>(nullptr);
		medKit = std::make_shared<PickUps_Actor>(nullptr);
		instantHeal = std::make_shared<PickUps_Actor>(nullptr);
		emergencyKit = std::make_shared<PickUps_Actor>(nullptr);
		antidote = std::make_shared<PickUps_Actor>(nullptr);

		armour = std::make_shared<PickUps_Actor>(nullptr);
		addrenaline = std::make_shared<PickUps_Actor>(nullptr);
		repair_kit = std::make_shared<PickUps_Actor>(nullptr);
		trap = std::make_shared<PickUps_Actor>(nullptr);
		fortify = std::make_shared<PickUps_Actor>(nullptr);

		medkit_animation = std::make_shared<Animate_Actor>(nullptr);
		poison_animation = std::make_shared<Animate_Actor>(nullptr);
		//instantHeal_animation = std::make_shared<Animate_Actor>(nullptr);
		//emergencyKit_animation = std::make_shared<Animate_Actor>(nullptr);





		tent = std::make_shared<Tent_Actor>(nullptr);



    	gp_fade_in_out_actor= std::make_shared<Actor>(nullptr);




	  	_data->gs.start_game = true;
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

    if(player){
    	player->GetComponent<PhysicsComponent>()->onDestroy();
    	_data->world->DestroyBody(player->GetComponent<PhysicsComponent>()->get_body());
    }
    
	if(gun){
    	gun->GetComponent<PhysicsComponent>()->onDestroy();
    	_data->world->DestroyBody(gun->GetComponent<PhysicsComponent>()->get_body());
    }
    
    for(auto &edges : _data->ld->return_edge_game_objects() )
    {
			edges.first->GetComponent<PhysicsComponent>()->onDestroy();
			_data->world->DestroyBody(edges.first->GetComponent<PhysicsComponent>()->get_body());
    }
    	
    for(auto &platform : _data->ld->return_platform_game_objects() )
    {
			platform.first->GetComponent<PhysicsComponent>()->onDestroy();
			_data->world->DestroyBody(platform.first->GetComponent<PhysicsComponent>()->get_body());
    }

    gun->onDestroy(*_data->world);

	enemies.clear();
	enemy_walk.clear();
	enemy_walkLeft.clear();
	enemy_run.clear();
	enemy_runLeft.clear();
	enemy_attackOne.clear();
	enemy_attackOne.clear();

	medKit_pkg.clear();
	instantHeal_pkg.clear();
	emergencyKit_pkg.clear();
	antidote_pkg.clear();
	addrenaline_pkg.clear();
	armour_pkg.clear();
	repair_kit_pkg.clear();
	fortify_kit_pkg.clear();
	trap_pkg.clear();

    gp_state = AL_STOPPED;
    alSourceStop(gp_backgroundSource);

    // Clean up sources and buffers
    alDeleteSources(1, &gp_backgroundSource);
    alDeleteSources(1, &gp_shootSource);
    alDeleteSources(1, &gp_jumpSource);
    alDeleteBuffers(1, &gp_Buffer);

    // Exit everything
    alutExit();
		

    _data->ld->return_edge_game_objects().clear();
    _data->ld->return_npc_game_objects().clear();
    _data->ld->return_platform_game_objects().clear();
    delete _data->world;

    _data->ld->return_game_objects().clear();
    delete _data->ld;
}

float gameplay_BackgroundMusic = 0.5f;
float gameplay_SoundFX = 0.5f;

void GamePlayState::Init()
{
    printf("Hello GAME PLAY Init************************************************************************\n");
	shader->onCreate(
	"shaders/sprite.vs", 
	"shaders/simpleTriangle.fs");
	//"shaders/simple.fs");

	texture_shader->onCreate(
	"shaders/sprite.vs", 
	"shaders/sprite.fs");

	text->onCreate(
	"shaders/text.vs", 
	"shaders/text.fs", 
	"assets/font/Antonio-Bold.ttf", 
	25);
	
	tentText->onCreate(
	"shaders/text.vs", 
	"shaders/text.fs", 
	"assets/font/Antonio-Bold.ttf", 
	25);

	//tentText->GetComponent<TransformComponent>()->setTranform(vec2(0, 0), float rot)

	enemyText->onCreate(
	"shaders/text.vs", 
	"shaders/text.fs", 
	"assets/font/Minecraft.ttf", 
	5);
	
	roundText->onCreate(
	"shaders/text.vs", 
	"shaders/text.fs", 
	"assets/font/Minecraft.ttf", 
	50);

	enemyText->GetComponent<TransformComponent>()->setTranform(
	vec2(1, 1), 
	0.0, 
	vec2(0.1f, 0.1f));

	tent->onCreate(_data->world);

	player->InitalizeActor(
	"assets/images/red.png",
	_data->world, 
	vec2(20, 19), 
	vec2(95, 128), 
	vec2(2, 2), 
	3, 
	4, 
	1, 
	1);

	player_walk_animation->onCreate(
	"assets/images/Soldier_1/Walk.png", 
	vec2(52, 59), 
	vec2(224, 32), 
	7, 
	1, 
	0.0f, 
	vec3(1.0f), 
	vec2(1, 1), 
	true);

	player_walkLeft_animation->onCreate(
	"assets/images/Soldier_1/WalkLeft.png", 
	vec2(52, 59), 
	vec2(224, 32), 
	7, 
	1, 
	0.0f, 
	vec3(1.0f), 
	vec2(7, 1), 
	true);

	player_idle_animation->onCreate(
	"assets/images/Soldier_1/Idle.png", 
	vec2(50, 59), 
	vec2(224, 32), 
	7, 
	1, 
	0.0f, 
	vec3(1.0f), 
	vec2(1, 1), 
	true);
	
	player_idleLeft_animation->onCreate(
	"assets/images/Soldier_1/IdleLeft.png", 
	vec2(50, 59), 
	vec2(224, 32), 
	7, 
	1, 
	0.0f, 
	vec3(1.0f), 
	vec2(1, 1), 
	true);

	player_run_animation->onCreate(
	"assets/images/Soldier_1/Run.png", 
	vec2(50, 59), 
	vec2(1024, 128), 
	8, 
	1, 
	0.0f, 
	vec3(1.0f), 
	vec2(1, 1), 
	true);
	
	player_runLeft_animation->onCreate(
	"assets/images/Soldier_1/RunLeft.png", 
	vec2(50, 59), 
	vec2(1024, 128), 
	8, 
	1, 
	0.0f, 
	vec3(1.0f), 
	vec2(8, 1), 
	true);

	player_shooting_animation->onCreate(
	"assets/images/Soldier_1/Shot_1.png", 
	vec2(50, 59), 
	vec2(512, 128), 
	4, 
	1, 
	0.0f, 
	vec3(1.0f), 
	vec2(1, 1), 
	true);

	player_shootingLeft_animation->onCreate(
	"assets/images/Soldier_1/Shot_1Left.png", 
	vec2(50, 59), 
	vec2(512, 128), 
	4, 
	1, 
	0.0f, 
	vec3(1.0f), 
	vec2(1, 1), 
	true);
	
	player_death_animation->onCreate(
	"assets/images/Soldier_1/Dead.png", 
	vec2(50, 59), 
	vec2(512, 128), 
	4, 
	1, 
	0.0f, 
	vec3(1.0f), 
	vec2(1, 1), 
	true);


	gun->InitalizeActor(
	"assets/images/2_1.png", 
	_data->world,
	vec2(15, 19),
	vec2(22, 8),
	vec2(2, 1),
	1, 
	1, 
	1, 
	1);



	//std::shared_ptr<NPC_Actor> enemy;
	enemy = std::make_shared<NPC_Actor>(nullptr);

	//enemy->readStateMachine(
	//"");
	enemy->InitalizeActor(
	"assets/images/Idle.png",
	_data->world,
	vec2(50 + i, 19),
	vec2(192, 48),
	vec2(2.3f, 4),
	1, 
	1, 
	4, 
	1);
	enemy->GetComponent<PhysicsComponent>()->get_body()->SetEnabled(false);
	enemy->set_health(25);

	//std::shared_ptr<Animate_Actor> enemy_idle_animation;
	enemy_idle_animation = std::make_shared<Animate_Actor>(nullptr);
			
	enemy_idle_animation->onCreate(
	"assets/images/Zombie_Man/Idle.png", 
	vec2(50, 59), 
	vec2(768, 96 - 6),
	8, 
	1, 
	0.0f,
	vec3(1.0f), 
	vec2(1, 1), 
	true);

	//std::shared_ptr<Animate_Actor> enemy_walk_animation;
	enemy_walk_animation = std::make_shared<Animate_Actor>(nullptr);
		
	enemy_walk_animation->onCreate(
	"assets/images/Zombie_Man/Walk.png", 
	vec2(50, 59), 
	vec2(768, 96 - 6), 
	8, 
	1, 
	0.0f, 
	vec3(1.0f),
	vec2(1, 1), 
	true);
			
	//std::shared_ptr<Animate_Actor> enemy_walkLeft_animation;
	enemy_walkLeft_animation = std::make_shared<Animate_Actor>(nullptr);
			
	enemy_walkLeft_animation->onCreate(
	"assets/images/Zombie_Man/WalkLeft.png", 
	vec2(50, 59),
	vec2(768, 96 - 6),
	8, 
	1,
	0.0f, 
	vec3(1.0f),
	vec2(8, 1), 
	true);

	//std::shared_ptr<Animate_Actor> enemy_run_animation;
	enemy_run_animation = std::make_shared<Animate_Actor>(nullptr);
			
	enemy_run_animation->onCreate(
	"assets/images/Zombie_Man/Run.png", 
	vec2(50, 59), 
	vec2(672, 96 - 6),
	7, 
	1, 
	0.0f, 
	vec3(1.0f), 
	vec2(1, 1), 
	true);
			
	//std::shared_ptr<Animate_Actor> enemy_runLeft_animation;
	enemy_runLeft_animation = std::make_shared<Animate_Actor>(nullptr);
			
	enemy_runLeft_animation->onCreate(
	"assets/images/Zombie_Man/RunLeft.png", 
	vec2(50, 59), 
	vec2(672, 96 - 6), 
	7, 
	1, 
	0.0f, 
	vec3(1.0f), 
	vec2(7, 1), 
	true);
			
	//std::shared_ptr<Animate_Actor> enemy_attackOne_animation;
	enemy_attackOne_animation = std::make_shared<Animate_Actor>(nullptr);
		
	enemy_attackOne_animation->onCreate(
	//"assets/images/Zombie_Man/Bite.png", 
	"assets/images/Zombie_Man/Attack_1.png", 
	vec2(50, 59), 
	vec2(480, 96 - 6), 
	//vec2(1056, 96), 
	//11, 
	5, 
	1, 
	0.0f, 
	vec3(1.0f), 
	vec2(1, 1), 
	true);
			
	//std::shared_ptr<Animate_Actor> enemy_dead_animation;
	enemy_dead_animation = std::make_shared<Animate_Actor>(nullptr);
			
	enemy_dead_animation->onCreate(
	"assets/images/Zombie_Man/Dead.png", 
	vec2(50, 59), 
	vec2(480, 96 - 6), 
	5, 
	1, 
	0.0f, 
	vec3(1.0f), 
	vec2(1, 1), 
	true);


	for(int i = 0; i < MAX_ENEMIES; i++)
	{
			enemyflag[i] = false;

			int random = 1 + (rand() % 6);
			int attackRandom = 1 + (rand() % 2);

			if(random == 1)
			{
				std::shared_ptr<NPC_Actor> enemy;
				enemy = std::make_shared<NPC_Actor>(nullptr);
				enemy->InitalizeActor(
				_data->world,
				vec2(200 , 19),
				//vec2(random + i, 19),
				vec2(192, 48),
				vec2(2.0f, 4.5f),
				1, 
				1, 
				4, 
				1);
				enemy->GetComponent<PhysicsComponent>()->get_body()->SetEnabled(false);

				//enemy->set_health(100);
				//enemy->set_health(50);
				enemy->set_health(10);
				enemy->set_attackPosition(attackRandom);
				enemies.push_back(enemy);
			}
			else if(random == 2)
			{
				std::shared_ptr<NPC_Actor> enemy;
				enemy = std::make_shared<NPC_Actor>(nullptr);
				enemy->InitalizeActor(
				_data->world,
				vec2(-140 , 18),
				//vec2(random + i, 19),
				vec2(192, 48),
				vec2(2.0f, 4.5f),
				1, 
				1, 
				4, 
				1);
				enemy->GetComponent<PhysicsComponent>()->get_body()->SetEnabled(false);

				//enemy->set_health(100);
				//enemy->set_health(50);
				enemy->set_health(10);
				enemy->set_attackPosition(attackRandom);
				enemies.push_back(enemy);

			}
			else if(random == 3)
			{
				std::shared_ptr<NPC_Actor> enemy;
				enemy = std::make_shared<NPC_Actor>(nullptr);
				enemy->InitalizeActor(
				_data->world,
				vec2(-200 , 35),
				//vec2(random + i, 19),
				vec2(192, 48),
				vec2(2.0f, 4.5f),
				1, 
				1, 
				4, 
				1);
				enemy->GetComponent<PhysicsComponent>()->get_body()->SetEnabled(false);

				//enemy->set_health(100);
				//enemy->set_health(50);
				enemy->set_health(10);
				enemy->set_attackPosition(attackRandom);
				enemies.push_back(enemy);

			}
			else if(random == 4)
			{
				std::shared_ptr<NPC_Actor> enemy;
				enemy = std::make_shared<NPC_Actor>(nullptr);
				enemy->InitalizeActor(
				_data->world,
				vec2(260 , 35),
				//vec2(random + i, 19),
				vec2(192, 48),
				vec2(2.0f, 4.5f),
				1, 
				1, 
				4, 
				1);
				enemy->GetComponent<PhysicsComponent>()->get_body()->SetEnabled(false);

				//enemy->set_health(100);
				//enemy->set_health(50);
				enemy->set_health(10);
				enemy->set_attackPosition(attackRandom);
				enemies.push_back(enemy);

			}
			else if(random == 5)
			{
				std::shared_ptr<NPC_Actor> enemy;
				enemy = std::make_shared<NPC_Actor>(nullptr);
				enemy->InitalizeActor(
				_data->world,
				vec2(200, -24),
				//vec2(random + i, 19),
				vec2(192, 48),
				vec2(2.0f, 4.5f),
				1, 
				1, 
				4, 
				1);
				enemy->GetComponent<PhysicsComponent>()->get_body()->SetEnabled(false);

				//enemy->set_health(100);
				//enemy->set_health(50);
				enemy->set_health(5);
				enemy->set_attackPosition(attackRandom);
				enemies.push_back(enemy);

			}
			else if(random == 6)
			{
				std::shared_ptr<NPC_Actor> enemy;
				enemy = std::make_shared<NPC_Actor>(nullptr);
				enemy->InitalizeActor(
				_data->world,
				vec2(-140 ,-20),
				//vec2(random + i, 19),
				vec2(192, 48),
				vec2(2.0f, 4.5f),
				1, 
				1, 
				4, 
				1);
				enemy->GetComponent<PhysicsComponent>()->get_body()->SetEnabled(false);

				//enemy->set_health(100);
				//enemy->set_health(50);
				enemy->set_health(5);
				enemy->set_attackPosition(attackRandom);
				enemies.push_back(enemy);

			}
	
			std::shared_ptr<Animate_Actor> enemy_idle_animationOBJ;
			enemy_idle_animationOBJ = std::make_shared<Animate_Actor>(*enemy_idle_animation);

			std::shared_ptr<Animate_Actor> enemy_walk_animationOBJ;
			enemy_walk_animationOBJ = std::make_shared<Animate_Actor>(*enemy_walk_animation); 
			
			std::shared_ptr<Animate_Actor> enemy_walkLeft_animationOBJ;
			enemy_walkLeft_animationOBJ = std::make_shared<Animate_Actor>(*enemy_walkLeft_animation); 
			
			std::shared_ptr<Animate_Actor> enemy_run_animationOBJ;
			enemy_run_animationOBJ = std::make_shared<Animate_Actor>(*enemy_run_animation); 
			
			std::shared_ptr<Animate_Actor> enemy_runLeft_animationOBJ;
			enemy_runLeft_animationOBJ = std::make_shared<Animate_Actor>(*enemy_runLeft_animation); 
			
			std::shared_ptr<Animate_Actor> enemy_attackOne_animationOBJ;
			enemy_attackOne_animationOBJ = std::make_shared<Animate_Actor>(*enemy_attackOne_animation); 
			
			std::shared_ptr<Animate_Actor> enemy_dead_animationOBJ;
			enemy_dead_animationOBJ = std::make_shared<Animate_Actor>(*enemy_dead_animation); 

			enemy_idle.push_back(enemy_idle_animationOBJ);
			enemy_walk.push_back(enemy_walk_animationOBJ);
			enemy_walkLeft.push_back(enemy_walkLeft_animationOBJ);
			enemy_run.push_back(enemy_run_animationOBJ);
			enemy_runLeft.push_back(enemy_runLeft_animationOBJ);
			enemy_attackOne.push_back(enemy_attackOne_animationOBJ);
			enemy_dead.push_back(enemy_dead_animationOBJ);

	}
	
	medKit->InitalizeActor(
	"assets/images/medkit.png",
	_data->world,
	vec2(15, 19),
	vec2(24, 24),
	vec2(2, 1),
	1, 
	1, 
	1, 
	1);

	instantHeal->InitalizeActor(
	"assets/images/heal.png",
	_data->world,
	vec2(18, 19),
	vec2(24, 34),
	vec2(2, 1),
	1, 
	1, 
	1, 
	1);

	emergencyKit->InitalizeActor(
	"assets/images/emergency_kit.png",
	_data->world,
	vec2(21, 19),
	vec2(24, 24),
	vec2(2, 1),
	1, 
	1, 
	1, 
	1);
	
	antidote->InitalizeActor(
	"assets/images/antidote.png",
	_data->world,
	vec2(21, 19),
	vec2(24, 24),
	vec2(2, 1),
	1, 
	1, 
	1, 
	1);

	addrenaline->InitalizeActor(
	"assets/images/adrenaline.png",
	_data->world,
	vec2(21, 19),
	vec2(24, 24),
	vec2(2, 1),
	1, 
	1, 
	1, 
	1);

	trap->InitalizeActor(
	"assets/images/trap.png",
	_data->world,
	vec2(21, 19),
	vec2(24, 24),
	vec2(2, 1),
	1, 
	1, 
	1, 
	1);

	repair_kit->InitalizeActor(
	"assets/images/repair.png",
	_data->world,
	vec2(21, 19),
	vec2(24, 24),
	vec2(2, 1),
	1, 
	1, 
	1, 
	1);

	fortify->InitalizeActor(
	"assets/images/gear.png",
	_data->world,
	vec2(21, 19),
	vec2(24, 24),
	vec2(2, 1),
	1, 
	1, 
	1, 
	1);

	armour->InitalizeActor(
	"assets/images/3.png",
	_data->world,
	vec2(21, 19),
	vec2(24, 24),
	vec2(2, 1),
	1, 
	1, 
	1, 
	1);

	medkit_animation->onCreate(
	"assets/images/Particles/blue.png", 
	vec2(50, 59), 
	vec2(960*2, 192*2), 
	5, 
	1, 
	0.0f, 
	vec3(1.0f), 
	vec2(1, 1), 
	true);

	poison_animation->onCreate(
	"assets/images/Particles/blue.png", 
	vec2(50, 59), 
	vec2(960, 192), 
	5, 
	1, 
	0.0f, 
	vec3(1.0f), 
	vec2(1, 1), 
	true);




	instantHeal_animation = std::make_shared<Animate_Actor>(*medkit_animation);
	emergencyKit_animation = std::make_shared<Animate_Actor>(*medkit_animation);
	addrenaline_animation = std::make_shared<Animate_Actor>(*medkit_animation);

	for(int i = 0; i < 50; i++)
	{
		std::shared_ptr<PickUps_Actor> armor_;
		armor_ = std::make_shared<PickUps_Actor>(*armour);
		armour_pkg.push_back(armor_);
		armourUpdate[i] = false;
		
		std::shared_ptr<PickUps_Actor> medkit;
		medkit = std::make_shared<PickUps_Actor>(*medKit);
		medKit_pkg.push_back(medkit);
		meditUpdate[i] = false;

		std::shared_ptr<PickUps_Actor> heal;
		heal = std::make_shared<PickUps_Actor>(*instantHeal);
		instantHeal_pkg.push_back(heal);
		healUpdate[i] = false;

		std::shared_ptr<PickUps_Actor> emergency;
		emergency = std::make_shared<PickUps_Actor>(*emergencyKit);
		emergencyKit_pkg.push_back(emergency);
		emergency_kitUpdate[i] = false;

		std::shared_ptr<PickUps_Actor> antidote_;
		antidote_ = std::make_shared<PickUps_Actor>(*antidote);
		antidote_pkg.push_back(antidote_);
		antidoteUpdate[i] = false;

		std::shared_ptr<PickUps_Actor> addrenaline_;
		addrenaline_ = std::make_shared<PickUps_Actor>(*addrenaline);
		addrenaline_pkg.push_back(addrenaline_);
		addrenalineUpdate[i] = false;
		
		std::shared_ptr<PickUps_Actor> trap_;
		trap_ = std::make_shared<PickUps_Actor>(*trap);
		trap_pkg.push_back(trap_);
		trapUpdate[i] = false;
		
		std::shared_ptr<PickUps_Actor> repairKit_;
		repairKit_ = std::make_shared<PickUps_Actor>(*repair_kit);
		repair_kit_pkg.push_back(repairKit_);
		repairKitUpdate[i] = false;
		
		std::shared_ptr<PickUps_Actor> fortify_;
		fortify_ = std::make_shared<PickUps_Actor>(*fortify);
		fortify_kit_pkg.push_back(fortify_);
		fortifyUpdate[i] = false;
	}



   	gp_fade_in_out_actor->AddComponent<TransformComponent>(nullptr, glm::vec2(100, 100), 0.0f);
    gp_fade_in_out_actor->AddComponent<RenderComponent>(nullptr);
    gp_fade_in_out_actor->AddComponent<ShaderComponent>(nullptr);

    auto square_transform = gp_fade_in_out_actor->GetComponent<TransformComponent>();
    auto square_render = gp_fade_in_out_actor->GetComponent<RenderComponent>();
    auto square_shader = gp_fade_in_out_actor->GetComponent<ShaderComponent>();

    square_shader->loadShader("shaders/sprite.vs", "shaders/simple.fs");
    square_render->initRenderData();



//###########################################################################################################################
    //x_cam = -5.0f;
    x_cam = 135.0f;
    y_cam = 230.0f;
	z_cam = 0.0f;
	r_cam = 0.0f;

	z_scale.x = 12.54f;
	z_scale.y = 12.54f;
	pause_counter = 0;
	
	cam_x_speed = 0.0f;
	cam_y_speed = 0.0f;

    _data->o_cam->SetPosition(glm::vec3(x_cam, y_cam, z_cam));
	//glfwSetTime(0.0);
	game_play_clock = 0;
	record_game_play_clock = 0;
	round = 0;
	score = 0;
	
	x_pos = 0.0f;
	y_pos = 0.0f;
	game_paused = false;
	counter = 0.0f;	

	player_R = 1.0f;
	player_G = 1.0f;
	player_B = 1.0f;

	draw_playerHud = true;


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
		_data->ld->Load_XML_ASSETS("assets/xml/map.xml", "level_1"); 

	}


      	alutInit(0, NULL);

      	gp_Buffer = alutCreateBufferFromFile("assets/sound/main_menu.wav");
      	alGenSources(1, &gp_backgroundSource);
      	alSourcei(gp_backgroundSource, AL_BUFFER, gp_Buffer); 
		//alSourcef(gp_backgroundSource, AL_GAIN, 0.15f);
		alSourcef(gp_backgroundSource, AL_GAIN, gameplay_BackgroundMusic);

      	gp_Buffer = alutCreateBufferFromFile("assets/sound/fire4.wav");
      	alGenSources(1, &gp_shootSource);
      	alSourcei(gp_shootSource, AL_BUFFER, gp_Buffer); 
		//alSourcef(gp_shootSource, AL_GAIN, 0.5f);
		alSourcef(gp_shootSource, AL_GAIN, gameplay_SoundFX);
      	
		gp_Buffer = alutCreateBufferFromFile("assets/sound/jump.wav");
      	alGenSources(1, &gp_jumpSource);
      	alSourcei(gp_jumpSource, AL_BUFFER, gp_Buffer); 
		//alSourcef(gp_jumpSource, AL_GAIN, 0.5f);
		alSourcef(gp_jumpSource, AL_GAIN, gameplay_SoundFX);



		std::cout << "Total Number of Textures " << ObjectCounter::texture_actor_counter << std::endl;
		std::cout << "Total Number of NPC " << ObjectCounter::npc_actor_counter << std::endl;
		std::cout << "Total Number of Animator " << ObjectCounter::animation_actor_counter << std::endl;
		std::cout << "Total Number of Projectile " << ObjectCounter::projectile_actor_counter << std::endl;
		
		std::cout << "Total Number of RenderComponents " << ObjectCounter::render_component_counter << std::endl;
		std::cout << "Total Number of TransformComponents " << ObjectCounter::transform_component_counter << std::endl;
		std::cout << "Total Number of PhysicsComponents " << ObjectCounter::physic_component_counter << std::endl;
		std::cout << "Total Number of AI Componets " << ObjectCounter::ai_component_counter << std::endl;

}

bool gun_shooting = false;

void GamePlayState::SoundUpdate()
{
    //printf("Hello Game Play Sound UPdate\n");

	// Play

 
//play

	//Background Music
	//play
    alSourcePlay(gp_backgroundSource);
    // Wait for the song to complete
    do {
        alGetSourcei(gp_backgroundSource, AL_SOURCE_STATE, &gp_state);
				alSourcef(gp_backgroundSource, AL_GAIN, gameplay_BackgroundMusic);
				alSourcef(gp_shootSource, AL_GAIN, gameplay_SoundFX);
				alSourcef(gp_jumpSource, AL_GAIN, gameplay_SoundFX);
		if(gun_shooting)
			alSourcePlay(gp_shootSource);
		if(player->get_jump_flag())
			alSourcePlay(gp_jumpSource);


    } while (gp_state == AL_PLAYING);

        




}

void GamePlayState::Input(float delta)
{
	/*
		//Move camera Left
    	if (glfwGetKey(_data->window, GLFW_KEY_RIGHT) == GLFW_PRESS
		//	|| _data->pd.RJOYX > 0.0f
		)
    	{
		    //x_cam -=5.0f;
			//std::cout << "X cam : " << x_cam  << std::endl;
    	}

		//Move camera Right
    	if (glfwGetKey(_data->window, GLFW_KEY_LEFT) == GLFW_PRESS
		//	|| _data->pd.RJOYX < 0.0f
		)
    	{
		    //x_cam +=5.0f;
			//std::cout << "X cam : " << x_cam  << std::endl;
    	}

		//Move camera UP
    	if (glfwGetKey(_data->window, GLFW_KEY_UP) == GLFW_PRESS
		//	|| _data->pd.RJOYY < 0.0f
		)
    	{
		    y_cam +=5.0f;
		    //std::cout << "Y cam : " << y_cam  << std::endl;
    	}

		//Move camera Down
    	if (glfwGetKey(_data->window, GLFW_KEY_DOWN) == GLFW_PRESS
		//	|| _data->pd.RJOYY > 0.0f
		)
    	{
		    y_cam -=5.0f;
			//std::cout << "Y cam : " << y_cam  << std::endl;
    	}

		//Rotate camera right
    	if (glfwGetKey(_data->window, GLFW_KEY_E) == GLFW_PRESS)
    	{
		    //r_cam +=0.001;
			//std::cout << "R cam : " << r_cam  << std::endl;
    	}

		//Rotate camera left
    	if (glfwGetKey(_data->window, GLFW_KEY_Q) == GLFW_PRESS)
    	{
		    //r_cam -=0.001;
			//std::cout << "R cam : " << r_cam  << std::endl;
    	}

		//Camera Zoom in
    	if (glfwGetKey(_data->window, GLFW_KEY_Z) == GLFW_PRESS
			|| _data->pd.LJOYY > 0.0f) 
    	{
		   //z_scale.x += 0.1;
		   //z_scale.y += 0.1;
    	   //std::cout << "Z-x cam : " << z_scale.x << std::endl;
    	   //std::cout << "Z-y cam : " << z_scale.y << std::endl;
    	}

		//Camera Zoom out
    	if (glfwGetKey(_data->window, GLFW_KEY_X) == GLFW_PRESS)
			//|| _data->pd.LJOYY < 0.0f) 
    	{
		   z_scale.x -= 0.1;
		    z_scale.y -= 0.1;
    	    //std::cout << "Z-x cam : " << z_scale.x << std::endl;
    	    //std::cout << "Z-y cam : " << z_scale.y << std::endl;
    	}
	*/
		//std::cout << "X cam : " << x_cam  << std::endl;
		//std::cout << "Y cam : " << y_cam  << std::endl;
		//Move camera Left
    	if (glfwGetKey(_data->window, GLFW_KEY_RIGHT) == GLFW_PRESS
		//	|| _data->pd.RJOYX > 0.0f
		)
    	{
		    x_cam -=5.0f;
			std::cout << "X cam : " << x_cam  << std::endl;
    	}

		//Move camera Right
    	if (glfwGetKey(_data->window, GLFW_KEY_LEFT) == GLFW_PRESS
		//	|| _data->pd.RJOYX < 0.0f
		)
    	{
		    x_cam +=5.0f;
			std::cout << "X cam : " << x_cam  << std::endl;
    	}

		//Move camera UP
    	if (glfwGetKey(_data->window, GLFW_KEY_UP) == GLFW_PRESS
		//	|| _data->pd.RJOYY < 0.0f
		)
    	{
		    y_cam +=5.0f;
		    //std::cout << "Y cam : " << y_cam  << std::endl;
    	}

		//Move camera Down
    	if (glfwGetKey(_data->window, GLFW_KEY_DOWN) == GLFW_PRESS
		//	|| _data->pd.RJOYY > 0.0f
		)
    	{
		    y_cam -=5.0f;
			//std::cout << "Y cam : " << y_cam  << std::endl;
    	}

		player->input(_data );
		//Camera Zoom in
    	if (glfwGetKey(_data->window, GLFW_KEY_Z) == GLFW_PRESS)
//			|| _data->pd.LJOYY > 0.0f) 
    	{
		   z_scale.x += 0.1;
		   z_scale.y += 0.1;
    	   //std::cout << "Z-x cam : " << z_scale.x << std::endl;
    	   //std::cout << "Z-y cam : " << z_scale.y << std::endl;
    	}

		//Camera Zoom out
    	if (glfwGetKey(_data->window, GLFW_KEY_X) == GLFW_PRESS)
//			//|| _data->pd.LJOYY < 0.0f) 
    	{
		    z_scale.x -= 0.1;
		    z_scale.y -= 0.1;
    	    //std::cout << "Z-x cam : " << z_scale.x << std::endl;
    	    //std::cout << "Z-y cam : " << z_scale.y << std::endl;
    	}

		if (glfwGetKey(_data->window, GLFW_KEY_L) == GLFW_PRESS || _data->pd.R == 1)
		{
			player->set_shooting_flag(true);

			//TODO write better code for this
			for(auto &bullet : gun->get_projectile_list())
			{
				if(!bullet->GetComponent<PhysicsComponent>()->get_physics_enable())
				{
					if(player->get_player_right_direction())
					{
						gun_shooting = true;
						counter += 0.5f;
						if(counter > 1000.0f)
						{
							player->set_player_right_direction(true);
							player->set_player_left_direction(false);

							bullet->projectile_firing(120.0f/2, 0.0f, gun);
							counter = 0;
						}
					}
					else if(player->get_player_left_direction())
					{
						gun_shooting = true;
						counter += 0.5f;
						if(counter > 1000.0f)
						{
							player->set_player_right_direction(false);
							player->set_player_left_direction(true);

							bullet->projectile_firing(-120.0f/2, -5.0f, gun);
							counter = 0;
						}
					}
				}
			}
		}
		else
		{
			player->set_shooting_flag(false);
			gun_shooting = false;

		}

	if(_data->pd.touchPad_3 == 1)
		_data->state_switch = MAIN_MENU_STATE;

	if (glfwGetKey(_data->window, GLFW_KEY_P) == GLFW_PRESS || _data->pd.touchPad_1 == 1)
	{
		pause_counter++;
	}
/*	
	if (glfwGetKey(_data->window, GLFW_KEY_U) == GLFW_PRESS || _data->pd.touchPad_5 == 1)
	{
		pause_counter++;
		if(pause_counter > 0)
			game_paused = true;
		else if(pause_counter > 1)
		{
			game_paused = false;
			pause_counter = 0;
		}

		game_paused = false;
	
	}
	*/




}


double captureHealTime;
double captureEmergencyHealTime;
double captureAdrenalineTime;
double roundIncrement = 10;

double pauseCaputureTime;

void GamePlayState::Update(float delta)
{
	game_play_clock = glfwGetTime();
	
	
	if(pause_counter == 1)
	{
		game_paused = true;
		pauseCaputureTime = game_play_clock;
	}
	else if(pause_counter == 2 && game_play_clock - pauseCaputureTime > 2)
	{
		game_paused = false;
		pause_counter = 0;
	}

	if(player->get_itemAmimation())
		medkit_animation->update(delta);

	if(player->get_playerHealedAnimation())
		instantHeal_animation->update(delta);

	if(player->get_playerReviedAnimation())
		emergencyKit_animation->update(delta);

	if(player->get_playerIsPoisoned())
		poison_animation->update(delta);

	if(player->get_playerAdrenalineOn())
		captureAdrenalineTime = game_play_clock;

	if(game_play_clock - captureAdrenalineTime > 30)
	{
	//	captureAdrenalineTime = game_play_clock;
		addrenaline_animation->update(delta);
	}	
	else {
		//player->set
	}







	//CLOCKS 
	if(game_play_clock - captureHealTime > 0.5)
		player->set_playerHealedAnimation(false);

	if(game_play_clock - captureEmergencyHealTime > 2.5)
		player->set_playerReviedAnimation(false);




	//boxes.shrink_to_fit();
	//std::cout << "Box Count : " << boxes.size() << std::endl;
	//std::cout << "Enemy Count : " << enemies.size() << std::endl;
	//std::cout << "Enemy Killed : " << enemiesKilled << std::endl;
	/*
		std::cout << "Player pos : " 
		<< "x=" << player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x << ", " 
		<< "y=" << player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y 
		<< "\nPlayer vel: "
		<< "x=" << player->GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().x << ", " 
		<< "y=" << player->GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().y 



		std::cout << "\nCam pos : " 
		<< "x=" << _data->o_cam->GetPosition().x 
		<< "y=" << _data->o_cam->GetPosition().y

		<< std::endl;
	*/



	//std::cout << "GAMEPLAY CLOCK : " << game_play_clock << std::endl;
	//#########################################################################################################################
	//#########################################################################################################################
	//#########################################################################################################################
	//#########################################################################################################################
	//#########################################################################################################################
	//#########################################################################################################################
	//#########################################################################################################################

	//if(game_play_clock - record_game_play_clock > 10.0)
	
		_data->o_cam->SetPosition(glm::vec3(
		x_cam, 
		y_cam,
		z_cam));
		_data->o_cam->SetScale(z_scale);
	if(!game_paused)
	{
		_data->world->Step(1.0f / 60.0f, 8, 2);    
		//_data->o_cam->SetPosition(glm::vec3(
		//x_cam, 
		//y_cam,
		//z_cam));

		x_cam += player->GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().x * 0.207  * -1;
		//y_cam += player->GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().y * -1;
		y_cam += player->GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().y * 0.187 * -1;
		//y_cam = -player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y;

		_data->o_cam->SetRotation(r_cam);
		//_data->o_cam->SetScale(z_scale);


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
		//if(game_play_clock - record_game_play_clock > 1.0)
		if(game_play_clock - record_game_play_clock > roundIncrement)
		{
			round++;
			std::cout << "###########################################################################################################" << std::endl;
			std::cout << "ROUND  : " << round << std::endl;

			/*
			if(round > 10)
				roundIncrement = 5.0;
			else if(round > 30)
				roundIncrement = 2.5;
			*/

			//for(int i = startingPoint; i <= round*2; i++)
			//for(int i = 0; i <= round*5; i++)
			for(int i = 0; i <= round*10; i++)
				enemyflag[i] = true;

			if(round < 50)
			{
				int random = 1 + (rand() % 30);
				std::cout << "RANDOM GENERATOR : " << random << std::endl;
				if(random == 1 | random == 11 | random == 10 | random == 21)
					meditUpdate[round] = true;
				else if(random == 2 | random == 12 | random == 22 | random == 23)
					antidoteUpdate[round] = true;
				else if(random == 3 | random == 13 | random == 17 | random == 24)
					healUpdate[round] = true;
				else if(random == 4 | random == 14 | random == 20 | random == 26)
					emergency_kitUpdate[round] = true;
				else if(random == 5 | random == 15 | random == 27)
					armourUpdate[round] = true;
				else if(random == 6 | random == 16 | random == 28)
					addrenalineUpdate[round] = true;
				else if(random == 7 | random == 18 | random == 25)
					repairKitUpdate[round] = true;
				else if(random == 8 | random == 29 | random == 30)
					trapUpdate[round] = true;
				else if(random == 9 | random == 19)
					fortifyUpdate[round] = true;
			}
			//Debug
			//if( round == 10)
			//	_data->pd.touchPad_4 = 1;


			record_game_play_clock = game_play_clock;
		}

		//std::cout << "Enemy Count : " <<  enemiesKilled << std::endl;

		for(int i = 0; i <= enemies.size() - 1; i++)
		//for(int i = startingPoint; i <= enemies.size() - 1; i++)
		{
			if(enemies.size() < 1)
				break;

			if(enemies[i])
			{	
				if(enemyflag[i])
				{
					if(enemies[i]->get_health() <= 0)
					{
						auto enemyDeath = game_play_clock;

						if(enemy_dead[i]->updateOnce(delta))
						{
							std::cout << "Playing death animation" << std::endl;
							enemies[i]->set_isWalking(false);
							enemies[i]->set_isRunning(false);
							enemies[i]->set_isAttacking(false);
							enemyflag[i] = false;
							enemies[i]->GetComponent<PhysicsComponent>()->get_body()->SetEnabled(false);
							enemies[i]->GetComponent<PhysicsComponent>()->get_body()->DestroyFixture(
				    		enemies[i]->GetComponent<PhysicsComponent>()->get_body()->GetFixtureList());
							if(!enemyflag[i])
							{
								score += 100;
								enemiesKilled++;
							}
							startingPoint++;
						}
					}

					enemies[i]->GetComponent<PhysicsComponent>()->get_body()->SetEnabled(true);
					//std::cout << "Enemy " << i << " Health : " << enemies[i]->get_health() << std::endl;

					enemies[i]->basic_update(tent, player, glfwGetTime(), _data->world, round);
					//This line causes segmentation faults
					//enemies[i]->update(player, glfwGetTime(), _data->world, true);
					enemy_idle[i]->update(delta);
					enemy_walk[i]->update(delta);
					enemy_walkLeft[i]->update(delta);
					enemy_run[i]->update(delta);
					enemy_runLeft[i]->update(delta);
					enemy_attackOne[i]->update(delta);

					//enemies[i]->set_health(enemies[i]->get_health() + round * 0.1);
					for(auto &bullet : gun->get_projectile_list())
					{
						//This line causes segmentation faults 
						if(bullet)
							enemies[i]->collison_update(bullet);
					}
				}
			}
		}




















		//Physics Update Code Starts Here
		//##########################################################################################################################################
		if(player)
		{
			player->update(game_play_clock, _data, tent.get());
			
			if(player->get_gun_equipped_flag())
				player->pick_up_gun(gun);

			if(player->get_player_health() < 10)
			{
				auto capture_deathTime = game_play_clock;
				//player_death_animation->update(delta);
				if(player_death_animation->updateOnce(delta))
				{
					std::cout << "Player is DEAD!!!" << std::endl;
  					if(gp_fade <= 1.0f)
  					{
  					  gp_fade += 0.01f;
  					}
					else if( gp_fade >= 0.95)
						_data->state_switch = GAME_OVER_STATE;

					//if(game_play_clock - capture_deathTime > 2.5)
				}
			}


			/*
			if(player->get_usedTrap())
			{
				if(player->get_totalTraps() > 0)
				{
					//tent->set_fortify(500);
					trapUpdate[]
				}
			}*/
			


			if(player->get_player_health() < 250)
			{
				float r_wave = 1 * sin(2 * 3.14 * 0.01 * (int)(glfwGetTime() * 100));
				player_G = r_wave;
				player_B = r_wave;
				
			
				if(player->get_player_health() < 100)
				{
					float r_wave = 1 * sin(2 * 3.14 * 0.05 * (int)(glfwGetTime() * 100));
					player_G = r_wave;
					player_B = r_wave;
				
					if(player->get_totalEmergencykits() > 0)
					{

						player->set_playerReviedAnimation(true);

						captureEmergencyHealTime = game_play_clock;						



						player->set_totalEmergencykits(player->get_totalEmergencykits() - 1);
						player->set_player_health(1000);					
					}
				}
			}
			else {
				player_G = 1.0f;
				player_B = 1.0f;
			}
			
			player_idle_animation->update(delta);
			//player_idleLeft_animation->update(delta, true);
			player_idleLeft_animation->update(delta);
			player_walk_animation->update(delta);
			player_walkLeft_animation->update(delta, true);
			player_run_animation->update(delta);
			player_runLeft_animation->update(delta, true);
			player_shooting_animation->update(delta);
			player_shootingLeft_animation->update(delta);


		}



















		if(gun)
		{
			float r_wave = 5 * sin(2 * 3.14 * 0.01 * (int)(glfwGetTime() * 100));
			gun->GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(b2Vec2(0.0f, ((r_wave) * 1) ));
		}

		/*
		if(medKit)
		{
			float r_wave = 5 * sin(2 * 3.14 * 0.01 * (int)(glfwGetTime() * 100));
			medKit->GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(b2Vec2(0.0f, ((r_wave) * 1) ));

			if(player->checkDistanceBetween(medKit, 1.0f) )
			{
				//place medkit in inventory
				//player->get_inventory().push_back(medKit);
			
				player->set_totalMedkits(player->get_totalMedkits() + 1);

				medKit->GetComponent<PhysicsComponent>()->get_body()->DestroyFixture(
	    medKit->GetComponent<PhysicsComponent>()->get_body()->GetFixtureList());
				medKit = nullptr;
			}
		}
		*/



		for(int i = 0; i < 50; i++)
		{
			if(antidoteUpdate[i])
			{
				if(antidote_pkg[i])
				{
					antidote_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->SetTransform(b2Vec2(35, 17.5), 0.0f);

					float r_wave = 5 * sin(2 * 3.14 * 0.01 * (int)(glfwGetTime() * 100));
					antidote_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(b2Vec2(0.0f, ((r_wave) * 1) ));

					if(player->checkDistanceBetween(antidote_pkg[i], 2.5f) )
					{
						//PLAY PICKUP SOUND EFFECT HERE
						//place medkit in inventory
						//player->get_inventory().push_back(medKit);

						player->set_totalAntidotes(player->get_totalAntidotes() + 1);
						//player->set_playerIsPoisoned(false);

						antidote_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->DestroyFixture(
	    				antidote_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->GetFixtureList());
						antidote_pkg[i] = nullptr;
					}
				}
			}
		}

		for(int i = 0; i < 50; i++)
		{
			if(armourUpdate[i])
			{
				if(armour_pkg[i])
				{
					armour_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->SetTransform(b2Vec2(40, 17.5), 0.0f);

					float r_wave = 5 * sin(2 * 3.14 * 0.01 * (int)(glfwGetTime() * 100));
					armour_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(b2Vec2(0.0f, ((r_wave) * 1) ));

					if(player->checkDistanceBetween(armour_pkg[i], 2.5f) )
					{
						//PLAY PICKUP SOUND EFFECT HERE
						//place medkit in inventory
						//player->get_inventory().push_back(medKit);

						//player->set_tot(player->get_totalAntidotes() + 1);
						//player->set_playerIsPoisoned(false);
						player->set_player_armor(player->get_player_armor() + 200);

						armour_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->DestroyFixture(
	    				armour_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->GetFixtureList());
						armour_pkg[i] = nullptr;
					}
				}
			}
		}

		for(int i = 0; i < 50; i++)
		{
			if(addrenalineUpdate[i])
			{
				if(addrenaline_pkg[i])
				{
					addrenaline_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->SetTransform(b2Vec2(37.5, 17.5), 0.0f);

					float r_wave = 5 * sin(2 * 3.14 * 0.01 * (int)(glfwGetTime() * 100));
					addrenaline_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(b2Vec2(0.0f, ((r_wave) * 1) ));

					if(player->checkDistanceBetween(addrenaline_pkg[i], 2.5f) )
					{
						//PLAY PICKUP SOUND EFFECT HERE
						//place medkit in inventory
						//player->get_inventory().push_back(medKit);

						player->set_totalAdrenaline(player->get_totalAdrenaline() + 1);
						//player->set_playerIsPoisoned(false);

						addrenaline_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->DestroyFixture(
	    				addrenaline_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->GetFixtureList());
						addrenaline_pkg[i] = nullptr;
					}
				}
			}
		}


		for(int i = 0; i < 50; i++)
		{
			if(repairKitUpdate[i])
			{
				if(repair_kit_pkg[i])
				{
					repair_kit_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->SetTransform(b2Vec2(32.5, 17.5), 0.0f);

					float r_wave = 5 * sin(2 * 3.14 * 0.01 * (int)(glfwGetTime() * 100));
					repair_kit_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(b2Vec2(0.0f, ((r_wave) * 1) ));

					if(player->checkDistanceBetween(repair_kit_pkg[i], 2.5f) )
					{
						//PLAY PICKUP SOUND EFFECT HERE
						//place medkit in inventory
						//player->get_inventory().push_back(medKit);

						player->set_totalRepairKit(player->get_totalRepairKit() + 1);
						//player->set_playerIsPoisoned(false);

						repair_kit_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->DestroyFixture(
	    				repair_kit_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->GetFixtureList());
						repair_kit_pkg[i] = nullptr;
					}
				}
			}
		}


		for(int i = 0; i < 50; i++)
		{
			if(fortifyUpdate[i])
			{
				if(fortify_kit_pkg[i])
				{
					fortify_kit_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->SetTransform(b2Vec2(27.5, 17.5), 0.0f);

					float r_wave = 5 * sin(2 * 3.14 * 0.01 * (int)(glfwGetTime() * 100));
					fortify_kit_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(b2Vec2(0.0f, ((r_wave) * 1) ));

					if(player->checkDistanceBetween(fortify_kit_pkg[i], 2.5f) )
					{
						//PLAY PICKUP SOUND EFFECT HERE
						//place medkit in inventory
						//player->get_inventory().push_back(medKit);

						player->set_totalFortify(player->get_totalFortify() + 1);
						//player->set_playerIsPoisoned(false);

						fortify_kit_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->DestroyFixture(
	    				fortify_kit_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->GetFixtureList());
						fortify_kit_pkg[i] = nullptr;
					}
				}
			}
		}


		for(int i = 0; i < 50; i++)
		{
			if(trapUpdate[i])
			{
				if(trap_pkg[i])
				{
					trap_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->SetTransform(b2Vec2(22.5, 17.5), 0.0f);

					float r_wave = 5 * sin(2 * 3.14 * 0.01 * (int)(glfwGetTime() * 100));
					trap_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(b2Vec2(0.0f, ((r_wave) * 1) ));

					if(player->checkDistanceBetween(trap_pkg[i], 2.5f) )
					{
						//PLAY PICKUP SOUND EFFECT HERE
						//place medkit in inventory
						//player->get_inventory().push_back(medKit);

						player->set_totalTraps(player->get_totalTraps() + 1);
						trapUpdate[i] = false;
						//player->set_playerIsPoisoned(false);

						//trap_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->DestroyFixture(
	    				//trap_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->GetFixtureList());
						//trap_pkg[i] = nullptr;
					}
				}
			}
		}









		for(int i = 0; i < 50; i++)
		{
			if(meditUpdate[i])
			{
				if(medKit_pkg[i])
				{
					medKit_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->SetTransform(b2Vec2(25, 17.5), 0.0f);

					float r_wave = 5 * sin(2 * 3.14 * 0.01 * (int)(glfwGetTime() * 100));
					medKit_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(b2Vec2(0.0f, ((r_wave) * 1) ));

					if(player->checkDistanceBetween(medKit_pkg[i], 2.5f) )
					{
						//PLAY PICKUP SOUND EFFECT HERE
						//place medkit in inventory
						//player->get_inventory().push_back(medKit);

						player->set_totalMedkits(player->get_totalMedkits() + 1);

						medKit_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->DestroyFixture(
	    				medKit_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->GetFixtureList());
						medKit_pkg[i] = nullptr;
					}
				}
			}
				
		}

		for(int i = 0; i < 50; i++)
		{
			if(healUpdate[i])
			{
				if(instantHeal_pkg[i])
				{
					instantHeal_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->SetTransform(b2Vec2(20, 17.5), 0.0f);

					float r_wave = 5 * sin(2 * 3.14 * 0.01 * (int)(glfwGetTime() * 100));
					instantHeal_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(b2Vec2(0.0f, ((r_wave) * 1) ));

					if(player->checkDistanceBetween(instantHeal_pkg[i], 2.5f) )
					{
						//PLAY PICKUP SOUND EFFECT HERE

						player->set_playerHealedAnimation(true);

						captureHealTime = game_play_clock;

						//play animation here 

						player->set_player_health(player->get_player_health() + 100);

						instantHeal_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->DestroyFixture(
	    				instantHeal_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->GetFixtureList());
						instantHeal_pkg[i] = nullptr;
					}
				}
			}
		}
		for(int i = 0; i < 50; i++)
		{
			if(emergency_kitUpdate[i])
			{
				if(emergencyKit_pkg[i])
				{
					emergencyKit_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->SetTransform(b2Vec2(15,17.5), 0.0f);

					float r_wave = 5 * sin(2 * 3.14 * 0.01 * (int)(glfwGetTime() * 100));
					emergencyKit_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->SetLinearVelocity(b2Vec2(0.0f, ((r_wave) * 1) ));

					if(player->checkDistanceBetween(emergencyKit_pkg[i], 2.5f) )
					{
						//player->set_player_health(player->get_player_health() + 100);
						//PLAY PICKUP SOUND EFFECT HERE



						player->set_totalEmergencykits(player->get_totalEmergencykits() + 1);



						emergencyKit_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->DestroyFixture(
	    				emergencyKit_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->GetFixtureList());
						emergencyKit_pkg[i] = nullptr;
					}
				}
			}
		}
	
	//#########################################################################################################################
	//#########################################################################################################################
	//#########################################################################################################################
	//#########################################################################################################################
	//#########################################################################################################################
	//#########################################################################################################################
	//#########################################################################################################################

		auto actors = _data->ld->return_game_objects();
		for(auto &actor : actors)
		{
			auto actor_render    = actor.first->GetComponent<RenderComponent>();
			if(actor_render->get_sprite()->get_position().y > 800)
			{
				actor.first->onDestroy();	
			}	
		}
		
 		auto edge_list = _data->ld->return_edge_game_objects();
		for(auto &edge : edge_list)
		{
			edge.first->update(glfwGetTime());
    		player->check_collision_edge(edge.first);
		}
	
		auto animation_map = _data->ld->return_animation_actors();
		for(auto &index : animation_map)
		{
			for(auto& texture : index.second)
			{
				texture->update(delta);
			}
		}
	}
}

void GamePlayState::Render(float delta)
{
	std::string player_speed = std::to_string(player->GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().x);
	std::string player_speed_y = std::to_string(player->GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().y);
	std::string player_force = std::to_string(player->force_x);
	std::string player_jump_force = std::to_string(player->force);
	std::string player_health_text = std::to_string(player->get_player_health() / 10);
	
	
	//BACKGROUNDS

//XML IMAGES
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################



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
		}	
	}
	//#############################################################################################################################################################
	//Physics Draw Code Starts Here
		auto animation_map = _data->ld->return_animation_actors();
		for(auto &index : animation_map)
		{
			{

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
									  render->get_sprite()->get_position().x,
									  render->get_sprite()->get_position().y,
									  render->get_sprite()->get_size().x/10,
									  render->get_sprite()->get_size().y/10,
									  0.0f);
			}

		}

	//#############################################################################################################################################################
	
	if(draw_playerHud)
	{
		text->draw(
			_data->o_cam->return_matrix(), 
			"new splash text actor", 
			200, 
			200);

		text->draw(
			projection1, 
			"Vel X : " + player_speed, 
			SCR_WIDTH/20 - 20.0f , 
			SCR_HEIGHT/20);

		text->draw(
			projection1, 
			"Vel Y : " + player_speed_y, 
			SCR_WIDTH/20 - 20.0f , 
			SCR_HEIGHT/20 + 20.0f);

		tentText->draw(
				_data->o_cam->return_matrix(), 
				"Tent Health : " + std::to_string(tent->get_health() / 10), 
				tent->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 2.5, 
				tent->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 13,  
				0.05f, 
				0.90196f, 
				0.02353f,
				0.5f);

		tentText->draw(
				_data->o_cam->return_matrix(), 
				"Tent Fortified : " + std::to_string(tent->get_fortify()), 
				tent->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 2.5, 
				tent->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 10,  
				0.05f, 
				0.90196f, 
				0.02353f,
				0.5f);

		roundText->draw(
			projection1, 
			"ROUND: " + std::to_string(round), 
			SCR_WIDTH/2 - 5.0f, 
			SCR_HEIGHT/20 + 20.0f);
		
		text->draw(
			projection1, 
			"Player Health : " + player_health_text, 
			SCR_WIDTH/4 * 3 , 
			SCR_HEIGHT/20, 
			0.5f, 
			0.17647f, 
			0.90196f, 
			0.02353f);
		
		text->draw(
			projection1, 
			"Score : " + std::to_string(score), 
			SCR_WIDTH/4 * 3 , 
			SCR_HEIGHT/20 + 20, 
			0.5f, 
			0.17647f, 
			0.90196f, 
			0.02353f);

	}




//PLAYER ANIMATION
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
	if(player)
	{
		if(player->get_player_health() <= 10)
		{
			std::cout << "Drawing Death animation" << std::endl;
			player_death_animation->draw(
			texture_shader, 
			_data->o_cam->return_matrix(),
			player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 1.5 ,
			player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 10,
			64/2, 
			24/2, 
			0.0f,
			glm::vec3(player_R, player_G, player_B));
		}
		else
		{
			if(!player->get_shooting_flag())
			{
				if(player->get_notMoving_flag())
				//	if(player->get_player_right_direction())
						//player_idleLeft_animation->draw(
						player_idle_animation->draw(
							texture_shader, 
							_data->o_cam->return_matrix(),
							player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 2.5 ,
							player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 10,
							124/2, 
							24/2, 
							0.0f,
							glm::vec3(player_R, player_G, player_B));

				if(player->get_run_flag())
				{
					//if(player->GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().x > 5.0f)
						if(player->get_player_right_direction())
							player_run_animation->draw(
							texture_shader, 
							_data->o_cam->return_matrix(),
							player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 1.0 ,
							player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 10,
							128/2, 
							24/2, 
							0.0f);

					//if(player->GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().x < -5.0f)
						if(player->get_player_left_direction())
							player_runLeft_animation->draw(
							texture_shader, 
							_data->o_cam->return_matrix(),
							player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 3.0 ,
							player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 10,
							128/2, 
							24/2, 
							0.0f);

				}

				//else if(player->get_MoveRight_flag())
				if(player->get_MoveRight_flag())
				player_walk_animation->draw(
					texture_shader, 
					_data->o_cam->return_matrix(),
					player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 2.5 ,
					player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 10,
					128/2, 
					24/2, 
					0.0f,
					glm::vec3(player_R, player_G, player_B));

				else if(player->get_MoveLeft_flag())
				player_walkLeft_animation->draw(
					texture_shader, 
					_data->o_cam->return_matrix(),
					player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 2.5 ,
					player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 10,
					128/2, 
					24/2, 
					0.0f,
					glm::vec3(player_R, player_G, player_B));

			}

			else if(player->get_shooting_flag())
			{
				if(player->get_player_right_direction()){
					player_shooting_animation->draw(
					texture_shader, 
					_data->o_cam->return_matrix(),
					player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 1.5 ,
					player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 10,
					64/2, 
					24/2, 
					0.0f,
					glm::vec3(player_R, player_G, player_B));
				}

				if(player->get_player_left_direction()){
					//player_shooting_animation->draw(
					player_shootingLeft_animation->draw(
					texture_shader, 
					_data->o_cam->return_matrix(),
					player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 2.5f ,
					player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 10,
					64/2, 
					24/2, 
					0.0f,
					glm::vec3(player_R, player_G, player_B));
				}
			}
		}
	}

//ENEMY ANIMATION
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------


	for(int i = 0; i <= enemies.size() - 1; i++)
	{
		if(enemies.size() < 1)
			break;

		//if(enemies[i])
		if(enemyflag[i])
		{

			//if(enemyflag[i])
			if(enemies[i])
			{
			std::string npc_health_text = std::to_string(enemies[i]->get_health());

				if(enemies[i]->get_health() <= 0)
				{
					std::cout << "Drawing Death Animation " << std::endl;
					enemy_dead[i]->draw(texture_shader, _data->o_cam->return_matrix(),
                        enemies[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 1.5 ,
                        enemies[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 6,
                                132/2.4, 22/2.4, 0.0f);
	
				}
				else 
				{
					if(enemies[i]->get_isWalking())
					//else if(enemies[i]->get_isWalking())
					{
						if(enemies[i]->GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().x < 0)
						enemy_walkLeft[i]->draw(
							texture_shader, 
							_data->o_cam->return_matrix(),
							enemies[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 1.5 ,
							enemies[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 6,
							132/2.4, 
							22/2.4, 
							0.0f);


						else if(enemies[i]->GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().x > 0)
						enemy_walk[i]->draw(
							texture_shader, 
							_data->o_cam->return_matrix(),
							enemies[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 1.5 ,
							enemies[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 6,
							132/2.4, 
							22/2.4, 
							0.0f);
					}
					else if(enemies[i]->get_isRunning())
					{
						if(enemies[i]->GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().x < 0)
						enemy_runLeft[i]->draw(
							texture_shader, 
							_data->o_cam->return_matrix(),
							enemies[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 1.5 ,
							enemies[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 6,
							132/2.4, 
							22/2.4, 
							0.0f);

						//During object removal animation may change which can cause segmentation fault
						//Causes bugs
						else if(enemies[i]->GetComponent<PhysicsComponent>()->get_body()->GetLinearVelocity().x > 0)
						enemy_run[i]->draw(
							texture_shader, 
							_data->o_cam->return_matrix(),
							enemies[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 1.5 ,
							enemies[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 6,
							132/2.4, 
							22/2.4, 
							0.0f);

					}
					else if(enemies[i]->get_isAttacking())
					{
						//std::cout << "ATTACKING !!! " << std::endl;

						enemy_attackOne[i]->draw(
						texture_shader, 
						_data->o_cam->return_matrix(),
						enemies[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 1.5 ,
						enemies[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 6,
						132/2.5, 
						22/2.4, 
						0.0f);

					}
				}
			}
		}	
	}	

	/*
	if(medKit)
	{
		medKit->draw(
			texture_shader, 
			_data->o_cam->return_matrix(),
			medKit->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x,
			medKit->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y,
			2.0f, 
			1.0f, 
			0.0f);
	}
	*/


//PICKUP ANIMATION
//##########################################################################################################################
//##########################################################################################################################
//##########################################################################################################################
//##########################################################################################################################
//##########################################################################################################################
//##########################################################################################################################
//##########################################################################################################################
//##########################################################################################################################
//##########################################################################################################################
//##########################################################################################################################
//##########################################################################################################################
//##########################################################################################################################
//##########################################################################################################################
//##########################################################################################################################
//##########################################################################################################################
//##########################################################################################################################

		for(int i = 0; i < 50; i++)
		{
			if(fortifyUpdate[i])
			{
				if(fortify_kit_pkg[i])
				{
					fortify_kit_pkg[i]->draw(
					texture_shader, 
					_data->o_cam->return_matrix(),
					fortify_kit_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x,
					fortify_kit_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y,
					2.0f, 
					1.0f, 
					0.0f);
				}
			}
		}


		for(int i = 0; i < 50; i++)
		{
			if(repairKitUpdate[i])
			{
				if(repair_kit_pkg[i])
				{
					repair_kit_pkg[i]->draw(
					texture_shader, 
					_data->o_cam->return_matrix(),
					repair_kit_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x,
					repair_kit_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y,
					2.0f, 
					1.0f, 
					0.0f);
				}
			}
		}

		for(int i = 0; i < 50; i++)
		{
			if(trapUpdate[i])
			{
				if(trap_pkg[i])
				{
					trap_pkg[i]->draw(
					texture_shader, 
					_data->o_cam->return_matrix(),
					trap_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x,
					trap_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y,
					2.0f, 
					1.0f, 
					0.0f);
				}
			}
		}


		for(int i = 0; i < 50; i++)
		{
			if(addrenalineUpdate[i])
			{
				if(addrenaline_pkg[i])
				{
					addrenaline_pkg[i]->draw(
					texture_shader, 
					_data->o_cam->return_matrix(),
					addrenaline_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x,
					addrenaline_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y,
					2.0f, 
					1.0f, 
					0.0f);
				}
			}
		}



		for(int i = 0; i < 50; i++)
		{
			if(armourUpdate[i])
			{
				if(armour_pkg[i])
				{
					armour_pkg[i]->draw(
					texture_shader, 
					_data->o_cam->return_matrix(),
					armour_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x,
					armour_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y,
					2.0f, 
					1.0f, 
					0.0f);
				}
			}
		}


		for(int i = 0; i < 50; i++)
		{
			if(antidoteUpdate[i])
			{
				if(antidote_pkg[i])
				{
					antidote_pkg[i]->draw(
					texture_shader, 
					_data->o_cam->return_matrix(),
					antidote_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x,
					antidote_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y,
					2.0f, 
					1.0f, 
					0.0f);
				}
			}
		}



		for(int i = 0; i < 50; i++)
		{
			if(meditUpdate[i])
			{
				if(medKit_pkg[i])
				{
					medKit_pkg[i]->draw(
					texture_shader, 
					_data->o_cam->return_matrix(),
					medKit_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x,
					medKit_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y,
					2.0f, 
					1.0f, 
					0.0f);
				}
			}
		}

		for(int i = 0; i < 50; i++)
		{
			if(healUpdate[i])
			{
				if(instantHeal_pkg[i])
				{
					instantHeal_pkg[i]->draw(
					texture_shader, 
					_data->o_cam->return_matrix(),
					instantHeal_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x,
					instantHeal_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y,
					2.0f, 
					1.0f, 
					0.0f);
				}
			}
		}
		
		for(int i = 0; i < 50; i++)
		{
			if(emergency_kitUpdate[i])
			{
				if(emergencyKit_pkg[i])
				{
					emergencyKit_pkg[i]->draw(
					texture_shader, 
					_data->o_cam->return_matrix(),
					emergencyKit_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x,
					emergencyKit_pkg[i]->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y,
					2.0f, 
					1.0f, 
					0.0f);
				}
			}
		}

		if(player->get_playerAdrenalineOn())
			addrenaline_animation->draw(
			texture_shader, 
			_data->o_cam->return_matrix(),
			player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 1.8f ,
			player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 6.6f,
			40, 
			10, 
			0.0f,
			glm::vec3(1.0f, 0.6f, 0.4f));



		if(player->get_itemAmimation())
			medkit_animation->draw(
			texture_shader, 
			_data->o_cam->return_matrix(),
			player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 1.8f ,
			player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 6.6f,
			40, 
			10, 
			0.0f,
			glm::vec3(1.0f, 1.0f, 1.0f));

		if(player->get_playerHealedAnimation())
			instantHeal_animation->draw(
			texture_shader, 
			_data->o_cam->return_matrix(),
			player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 1.8f,
			player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 6.6f,
			40, 
			10, 
			0.0f,
			glm::vec3(0.0f, 1.0f, 0.0f));
		
		if(player->get_playerReviedAnimation())
			emergencyKit_animation->draw(
			texture_shader, 
			_data->o_cam->return_matrix(),
			player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 1.8f ,
			player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 6.6f,
			40, 
			10, 
			0.0f,
			glm::vec3(1.0f, 0.0f, 0.0f));
		
		if(player->get_playerIsPoisoned())
			poison_animation->draw(
			texture_shader, 
			_data->o_cam->return_matrix(),
			player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x + 0.8f ,
			player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 6.6f,
			10, 
			2, 
			0.0f,
			glm::vec3(0.0f, 1.0f, 0.0f));
		





	if(gun){
		if(player->get_gun_equipped_flag()){
			if(shooting_right)
				gun->draw(
					texture_shader, 
					shader ,
					_data->o_cam->return_matrix(), 
			     	player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x + 2.0f , 
			     	player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 1.2f, 
			     	2.0f, 
					1.0f, 
					gun_angle);
		
			
			else if(shooting_left) 
				gun->draw(
					texture_shader, 
					shader ,
					_data->o_cam->return_matrix(), 
			     	player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x - 2.0f , 
			     	player->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y - 1.2f, 
			     	2.0f, 
					1.0f, 
					gun_angle);
		}
		else	
			gun->draw(
				texture_shader, 
				shader, 
				_data->o_cam->return_matrix(), 
			    gun->GetComponent<PhysicsComponent>()->get_body()->GetPosition().x, 
			    gun->GetComponent<PhysicsComponent>()->get_body()->GetPosition().y, 
			    2.0f, 
				1.0f, 
				0.0f);
	}

//XML IMAGES
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################
//##########################################################################################################################################

	
	auto platform_list = _data->ld->return_platform_game_objects();
	for(auto &platform_ : platform_list)
	{
		if(platform_.first)
		{
			auto platform_physcis = platform_.first->GetComponent<PhysicsComponent>();
			platform_.first->draw(
				shader, 
				_data->o_cam->return_matrix(), 
				platform_physcis->get_body()->GetPosition().x - 4.0f,
				platform_physcis->get_body()->GetPosition().y,
				10.0f, 
				2.0f, 
				0.0f);
		}
	}

	auto edge_actors = _data->ld->return_edge_game_objects();
	for(auto &edge : edge_actors)
		edge.first->draw(
			shader, 
			_data->o_cam->return_matrix());
//PAUSE SCREEN
//##########################################################################################################################################
	
		// feed inputs to dear imgui, start new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    if(game_paused)
    {
        ImGui::Begin("MENU", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
        ImGui::SetWindowPos("MENU", ImVec2(SCR_WIDTH/2 - 200, SCR_HEIGHT/2 - 150));
        ImGui::SetWindowSize("MENU", ImVec2(400 , 300));
        ImGui::CaptureMouseFromApp(true);
        ImGui::SetWindowFontScale(1.0f);
        
          ImGui::SetCursorPos(ImVec2(150, 10));
          ImGui::Text("GAME PAUSED", ImVec2(100, 50));
        
          //ImGui::SetCursorPos(ImVec2(50, 50));
          //ImGui::Text("Background Music", ImVec2(100, 50));

          ImGui::SliderFloat("Background Music", &gameplay_BackgroundMusic, 0.0f, 1.0f); 
          ImGui::SliderFloat("Sound FX", &gameplay_SoundFX, 0.0f, 1.0f); 
          ImGui::Checkbox("Fullscreen", &_data->gs.fullScreen);
          ImGui::Checkbox("Window Mode", &_data->gs.windowMode);
          ImGui::Checkbox("Draw Player HUD", &draw_playerHud);
          
          //ImGui::SetCursorPos(ImVec2(50, 150));
          //ImGui::Text("Sound FX", ImVec2(100, 50));


        static bool exit_menu;
        ImGui::SetCursorPos(ImVec2(150, 230));
        exit_menu = ImGui::Button("EXIT MENU", ImVec2(100, 50));
        if(exit_menu)
		{
            game_paused = false;
			pause_counter = 0;
		}
        ImGui::End();
    }
	  ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGui::EndFrame();

    auto square_transform = gp_fade_in_out_actor ->GetComponent<TransformComponent>();
    auto square_render = gp_fade_in_out_actor->GetComponent<RenderComponent>();
    auto square_shader = gp_fade_in_out_actor->GetComponent<ShaderComponent>();

	  square_shader->Use();
		//square_shader->SetMatrix4("projection", projection3);
		  square_shader->SetMatrix4("projection", _data->o_cam->return_matrix());
      square_shader->SetMatrix4("model", square_transform->transform(
						vec2(-100, -100), 
						vec2(SCR_WIDTH + 1000, SCR_HEIGHT + 1000), 0.0f));
      square_shader->SetVector3f("color", vec3(0.0f, 0.0f, 0.0f));
      square_shader->SetFloat("alpha", gp_fade);
	  square_render->drawSquare();

}
