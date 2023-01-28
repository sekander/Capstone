#pragma once
#include <GLFW/glfw3.h>
#include <box2d/box2d.h>
#include <iostream>
#include <memory>

#include "../../include/Camera/Orthographic_camera.h"
#include "../../include/States/state_machine.h"
#include "../../include/Loaders/LoadingGameObjects.h"


enum States
{
	SPLASH_STATE 					= 0,
	MAIN_MENU_STATE 				= 1,
	LOADING_PLAY_STATE 				= 2,
	PLAY_STATE 						= 3,
	GAME_OVER_STATE 				= 4,
	CURRENT 						= 5
};

enum Levels
{
    LEVEL_1 = 0,
    LEVEL_2, 
    LEVEL_3,
    LEVEL_4,
    LEVEL_5,
    LEVEL_6,
    LEVEL_7,
    LEVEL_8,
    LEVEL_9,
    LEVEL_0
};

struct Player_Data
{
	float x_pos;
	float y_pos;
	//int x_pos;
	//int y_pos;

	std::string player_data;
	std::string x_pos_text;
	std::string y_pos_text;
};

struct GameData 
{
	GLFWwindow* 			window;
	StateMachine* 			machine;
	Orthographic_camera* 	o_cam;
	b2World*				world;
	LoadingGameObjects*		ld;
	States					state_switch;
	Levels					level;
	Player_Data				pd;



	//Move Constructor
	GameData(){
		std::cout << "Default Constructor" << std::endl;
	}

	GameData(const GameData& gameData) : window(gameData.window), machine(gameData.machine), o_cam(gameData.o_cam), world(gameData.world)
	//GameData(const GameData& gameData) : window(gameData.window), o_cam(gameData.o_cam), world(gameData.world)
	{
		std::cout << "Copy Constructor" << std::endl;
	}

	GameData(GameData&& moveData) noexcept
	{
		std::cout << "Move Constructor" << std::endl;
		window = moveData.window;
		machine = moveData.machine;
		o_cam = moveData.o_cam;
		world = moveData.world;
		ld    = moveData.ld;
		//state_switch = moveData.state_switch;

		moveData.window = nullptr;
		moveData.machine = nullptr;
		moveData.o_cam = nullptr;
		moveData.world = nullptr;
		moveData.ld    = nullptr;
		//moveData.state_switch = nullptr;
	}

	~GameData()
	{
		std::cout << "GameData Destroyed" << std::endl;
	}

};

using GameDataRef = std::shared_ptr<GameData>;

