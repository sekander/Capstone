#pragma once


#include <memory>
#include <vector>
#include <unordered_map>
#include <tinyxml.h>

#include <box2d/box2d.h>
//#include "../Graphics/texture.h"
//#include "sprite.h"

//#include "../../include/Components/Actor.h"
// ----------------------------------------------------------------------

// STDOUT dump and indenting utility functions
// ----------------------------------------------------------------------

class Actor;
class NPC_Actor;
class Platform_Actor;
class Edge_Actor;
class Texture_Actor;

using namespace std;
class LoadingGameObjects
{

public:
        LoadingGameObjects();
        ~LoadingGameObjects();
	   
        //void Load_XML_SPLASH_SCREEN(const char* fileName, b2World *world);
        void Load_XML_SPLASH_SCREEN(const char* fileName, const char* level, b2World *world);
				void Load_XML_ASSETS(const char* fileName, const char* level);
				//Seperate function to generate textures
				void generate_textures();

	unordered_map<shared_ptr<Actor>, string> return_game_objects(){return game_objects;}
	unordered_map<shared_ptr<NPC_Actor>, string> return_npc_game_objects(){return npc_game_objects;}
	unordered_map<shared_ptr<Edge_Actor>, string> return_edge_game_objects(){return edge_game_objects;}
	unordered_map<shared_ptr<Platform_Actor>, string> return_platform_game_objects(){return platform_game_objects;}
	vector<shared_ptr<Texture_Actor>> return_tile_objects(){return tile_objects;}
	
	unordered_map<std::string, std::vector<std::shared_ptr<Texture_Actor>>> return_animation_actors(){return animation_actors;}
private:
	unordered_map<shared_ptr<Actor>, string> game_objects;
	unordered_map<shared_ptr<NPC_Actor>, string> npc_game_objects;
	unordered_map<shared_ptr<Platform_Actor>, string> platform_game_objects;
	unordered_map<shared_ptr<Edge_Actor>, string> edge_game_objects;
	//unordered_map<shared_ptr<Texture_Actor>, string> tile_objects;
	vector<shared_ptr<Texture_Actor>> tile_objects;

	//vector<shared_ptr<Texture_Actor>> textures_package;

	unordered_map<std::string, std::vector<std::shared_ptr<Texture_Actor>>> animation_actors;

	uint16_t count;
	uint16_t npc_count;
	uint16_t tileX_count;
	uint16_t tileY_count;
	bool edgeTwoSided = true;


	



};

