// tutorial demo program
#include "../../include/Loaders/LoadingGameObjects.h"
#include "../../include/Components/TransformComponent.h"
#include "../../include/Components/PhysicsComponent.h"
#include "../../include/Components/RenderComponent.h"
#include "../../include/Components/AIComponent.h"
#include <box2d/b2_world.h>
#include <cstdio>
#include <memory>
#include <string>
#include <utility>


#include "../../include/Actors/Texture_Actor.h"
#include "../../include/Actors/Actor.h"
#include "../../include/Actors/NPC_Actor.h"
#include "../../include/Actors/Platform_Actor.h"
#include "../../include/Actors/Edge_Actor.h"
// ----------------------------------------------------------------------
// STDOUT dump and indenting utility functions
// ----------------------------------------------------------------------

#include "../../include/Graphics/texture.h"

    LoadingGameObjects::LoadingGameObjects()  
    {
			printf("Loading XML\n");
			count = 0;
			npc_count = 0;
			tileX_count = 0;
			tileY_count = 0;
    }


    //void LoadingGameObjects::Load_XML_SPLASH_SCREEN(const char* fileName, b2World* world)
    void LoadingGameObjects::Load_XML_SPLASH_SCREEN(const char* fileName, const char* level, b2World* world)
    {
        TiXmlDocument   doc(fileName);

				//std::shared_ptr<Actor> actor;
				std::shared_ptr<NPC_Actor> npc_actor;
				std::shared_ptr<Edge_Actor> edge_actor;
				std::shared_ptr<Platform_Actor> platform_actor;

				//Dont need to use pointer can just call from stack
				Texture_Actor temp(nullptr);

            if(doc.LoadFile())
            {
                TiXmlElement *pRoot, *pBody, *pParms, *pParm;
                pRoot = doc.FirstChildElement( "Splash_State" );
                if ( pRoot )
                {
                    //pBody= pRoot->FirstChildElement( "body" ); //body should be read
                    pBody= pRoot->FirstChildElement(level); //body should be read
                    if (pBody) 
					{

											if((pParms = pBody->FirstChildElement( "platform" )))
											{
												pParm=pParms->FirstChildElement("param");
												while (pParm) 
												{
													npc_count++;

													auto key = pParm->Attribute("key");
													auto xpos 	   = std::stof(pParm->Attribute("xpos"));
													auto ypos 	   = std::stof(pParm->Attribute("ypos"));
													auto boxWidth  = std::stof(pParm->Attribute("boxWidth"));
													auto boxHeight = std::stof(pParm->Attribute("boxHeight"));
													auto rot       = std::stof(pParm->Attribute("rotation"));
					
													platform_actor = std::make_shared<Platform_Actor>(nullptr);
													platform_actor->GetComponent<PhysicsComponent>()->create_kinematic_body(world, true, 
															vec2(xpos, ypos), rot, vec2(boxWidth, boxHeight), 1, 1
																	, 0x0032, 0x0002 | 0x0004 | 0x0064 | 0x0128); 
																	//, 0x0032, 0x0002 | 0x0004 | 0x0064); 
						
													std::string counter_string = std::to_string(npc_count);
													platform_game_objects.insert(make_pair(platform_actor, key + counter_string));
																			
													pParm=pParm->NextSiblingElement("param");
												}
											}
											
											if((pParms = pBody->FirstChildElement( "npc" )))
											{
												pParm=pParms->FirstChildElement("param");
												while (pParm) 
												{
										
													npc_count++;

													auto key = pParm->Attribute("key");
													auto xpos 	   = std::stof(pParm->Attribute("xpos"));
													auto ypos 	   = std::stof(pParm->Attribute("ypos"));
													auto boxWidth  = std::stof(pParm->Attribute("boxWidth"));
													auto boxHeight = std::stof(pParm->Attribute("boxHeight"));
													auto rot       = std::stof(pParm->Attribute("rotation"));
													auto xFrame    = std::stof(pParm->Attribute("xFrame"));
													auto yFrame    = std::stof(pParm->Attribute("yFrame"));


                                                    //MAKE EDITS HERE
													npc_actor = std::make_shared<NPC_Actor>(nullptr);
                                                    //npc_actor->onCreate(1, 1, 1,1);
	                                                npc_actor->GetComponent<RenderComponent>()->renderData(4, 1, 1, 1);

													npc_actor->GetComponent<PhysicsComponent>()->create_body(world, true, true, 
															glm::vec2 (xpos, ypos), rot, glm::vec2 (boxWidth, boxHeight)
														, 0x0004 , 0x0008 | 0x0001 ); 		//This works but no collision

                                                    npc_actor->GetComponent<AIComponent>()->Init(npc_actor->GetComponent<PhysicsComponent>()->get_body());
                                                    npc_actor->set_health(100);


													std::string counter_string = std::to_string(npc_count);
													npc_game_objects.insert(make_pair(npc_actor, key + counter_string));
																			
													pParm=pParm->NextSiblingElement("param");
												}
											}
					
											if((pParms = pBody->FirstChildElement( "edge" )))
											{
												pParm=pParms->FirstChildElement("param");
												while (pParm) 
												{			    
													count++;
								
													auto key = pParm->Attribute("key");
													auto xo = std::stof(pParm->Attribute("xo"));
													auto yo = std::stof(pParm->Attribute("yo"));
													auto xd = std::stof(pParm->Attribute("xd"));
													auto yd = std::stof(pParm->Attribute("yd"));

													edge_actor = std::make_shared<Edge_Actor>(nullptr);
													edge_actor->set_xo(xo);
													edge_actor->set_xd(xd);
													edge_actor->set_yo(yo);
													edge_actor->set_yd(yd);
													
													edge_actor->GetComponent<PhysicsComponent>()->createEdeg(world, xo, yo, xd, yd, 
																	//0x0008, 0x0001 | 0x0004 | 0x0002 | 0x0016);
																	0x0008, 0x0001 | 0x0004 | 0x0002 | 0x0016 | 0x0128);
								
													std::string counter_string = std::to_string(count);

													edge_game_objects.insert(make_pair(edge_actor, key + counter_string));
													pParm=pParm->NextSiblingElement("param");
												}
											}
					
											if((pParms = pBody->FirstChildElement( "edgeO" )))
											{
												pParm=pParms->FirstChildElement("param");
												while (pParm) 
												{			    

													count++;
													
													auto key = pParm->Attribute("key");
													auto xo = std::stof(pParm->Attribute("xo"));
													auto yo = std::stof(pParm->Attribute("yo"));
													auto xd = std::stof(pParm->Attribute("xd"));
													auto yd = std::stof(pParm->Attribute("yd"));

													edge_actor = std::make_shared<Edge_Actor>(nullptr);
													edge_actor->set_xo(xo);
													edge_actor->set_xd(xd);
													edge_actor->set_yo(yo);
													edge_actor->set_yd(yd);
                                                    //edge_actor->GetComponent<RenderComponent>()
													
													edge_actor->GetComponent<PhysicsComponent>()->createOneEdeg(world, xo, yo, xd, yd, 
																	0x0008, 0x0001 | 0x0002 | 0x0004 | 0x0128);
					
													std::string counter_string = std::to_string(count);

													edge_game_objects.insert(make_pair(edge_actor, key + counter_string));
													pParm=pParm->NextSiblingElement("param");
												}
											}
					    }
				}
		}
	}


void LoadingGameObjects::Load_XML_ASSETS(const char* fileName, const char* level)
    {
        TiXmlDocument   doc(fileName);
        //game_text*      text;

		//std::shared_ptr<Actor> actor;
		std::shared_ptr<Texture_Actor> texture;
		std::shared_ptr<Texture_Actor> tile;
		//Dont need to use pointer can just call from stac
		Texture_Actor temp(nullptr);

            if(doc.LoadFile())
            {

                TiXmlElement *pRoot, *pBody, *pParms, *pParm;
                pRoot = doc.FirstChildElement( "Splash_State" );
                if ( pRoot )
                {
                    //pBody= pRoot->FirstChildElement( "body" ); //body should be read
                    pBody= pRoot->FirstChildElement(level); //body should be read
                    if (pBody) {

                        if((pParms = pBody->FirstChildElement( "gw" )))
                        {

                            bool isAlpha;
                            
                            pParm=pParms->FirstChildElement("param");
                            while (pParm) 
							{
                                
								texture = std::make_shared<Texture_Actor>(nullptr);

								auto actor_transform = texture->GetComponent<TransformComponent>();
								auto actor_render = texture->GetComponent<RenderComponent>();


                                if ((std::string(pParm->Attribute("alpha")) == "true")
                                || (std::string(pParm->Attribute("alpha")) == "True"))
                                    isAlpha = true;
                                else
                                    isAlpha = false;
                                   
																//This should be seperated         
																actor_render->LoadSprite(
																	pParm->Attribute("filename"),
				                	       	vec2(
																		std::stof(pParm->Attribute("position_x")),
																		std::stof(pParm->Attribute("position_y"))
																	),
																	vec2(
																		std::stof(pParm->Attribute("size_x")),
																		std::stof(pParm->Attribute("size_y"))
																	),
																	std::stoi(pParm->Attribute("num_x_frame")),
																	std::stoi(pParm->Attribute("num_y_frame")),
																	std::stof(pParm->Attribute("rotate")),
																	vec3(
																		std::stof(pParm->Attribute("color_r")),
																		std::stof(pParm->Attribute("color_g")),
																		std::stof(pParm->Attribute("color_b"))
																	),
																	vec2(
																		std::stoi(pParm->Attribute("current_x_frame")),
																		std::stoi(pParm->Attribute("current_y_frame"))
																	),
																	isAlpha);

																	actor_render->renderData(
																		std::stoi(pParm->Attribute("num_x_frame")),
																		std::stoi(pParm->Attribute("num_y_frame")),
																		std::stoi(pParm->Attribute("current_x_frame")),
																		std::stoi(pParm->Attribute("current_y_frame"))
																	);

																	game_objects.insert(make_pair(texture, pParm->Attribute("key")));
																	pParm=pParm->NextSiblingElement("param");
                            }
                        }

                        if((pParms = pBody->FirstChildElement( "an" )))
                        {
                            pParm=pParms->FirstChildElement("param");
                            while (pParm) 
														{

                                std::vector<std::shared_ptr<Texture_Actor>> animation_textures;
                                bool isAlpha;
                                auto numX = std::stoi(pParm->Attribute("num_x_frame"));
								auto numy = std::stoi(pParm->Attribute("num_y_frame"));
								auto curX = std::stoi(pParm->Attribute("current_x_frame"));
								auto curY = std::stoi(pParm->Attribute("current_y_frame"));

                                //Create a texture for each frame and add to vector
                                while(curX <= numX)
                                {

                                    texture = std::make_shared<Texture_Actor>(nullptr);

									auto actor_transform = texture->GetComponent<TransformComponent>();
									auto actor_render = texture->GetComponent<RenderComponent>();


                                    if ((std::string(pParm->Attribute("alpha")) == "true")
                                    || (std::string(pParm->Attribute("alpha")) == "True"))
                                        isAlpha = true;
                                    else
                                        isAlpha = false;

                                    //Load the sprite  
                                    actor_render->LoadSprite(
																			pParm->Attribute("filename"),
																			vec2(
																				std::stof(pParm->Attribute("position_x")),
																				std::stof(pParm->Attribute("position_y"))
																			),
																			vec2(
																				std::stof(pParm->Attribute("size_x")),
																				std::stof(pParm->Attribute("size_y"))
																			),
																			std::stoi(pParm->Attribute("num_x_frame")),
																			std::stoi(pParm->Attribute("num_y_frame")),
																			std::stof(pParm->Attribute("rotate")),
																			vec3(
																				std::stof(pParm->Attribute("color_r")),
																				std::stof(pParm->Attribute("color_g")),
																				std::stof(pParm->Attribute("color_b"))
																			),
																			vec2(curX, curY),isAlpha);

																		actor_render->renderData(
																			std::stoi(pParm->Attribute("num_x_frame")),
																			std::stoi(pParm->Attribute("num_y_frame")),
																			curX, curY);


                                    animation_textures.push_back(texture);
                                    curX++;
                                }

                            //push complete vector of frames into map
                            animation_actors.insert(std::make_pair(pParm->Attribute("key"), animation_textures));
														pParm=pParm->NextSiblingElement("param");
                            }
                        }






                        if((pParms = pBody->FirstChildElement( "map" )))
                        {
                            const char* key;
                            const char* fileName;
                            float posx;
                            float posy;
                            int xFrames;
                            int yFrames;
                            float size_x;
                            float size_y;
                            int mapWidth;
                            int mapHeight;
														float offsetX;
														float offsetY;
														int counter_x;
														int counter_y;
														float paddingX;
														float paddingY;

                            pParm=pParms->FirstChildElement("mapData");
                            if (pParm) 
                            //while (pParm) 
                            {
                                fileName = pParm->Attribute("filename");
																key = pParm->Attribute("key");
																posx = std::stof(pParm->Attribute("position_x"));
																posy = std::stof(pParm->Attribute("position_y"));
																xFrames = std::stoi(pParm->Attribute("num_x_frame"));
																yFrames = std::stoi(pParm->Attribute("num_y_frame"));
                                size_x = std::stof(pParm->Attribute("size_x"));
                                size_y = std::stof(pParm->Attribute("size_y"));
                                mapWidth = std::stoi(pParm->Attribute("map_width"));
                              	mapHeight = std::stoi(pParm->Attribute("map_height"));
																
																offsetX = 0.0f;
																offsetY = 0.0f;
																counter_x = 0;
																counter_y = 0;
																
																paddingX = 0.0f;
																paddingY = 0.0f;
	



																//Load the image in here 
                                uint16_t element = 0;

                                uint16_t multi_tile[xFrames][yFrames];
                                for(int i = 0; i < xFrames; i++)
                                    for(int j = 0; j < yFrames; j++)
                                        multi_tile[i][j] = element++;



																temp.GetComponent<RenderComponent>()->LoadTexture(fileName);
																//auto texture_render = temp.GetComponent<RenderComponent>();
																//Create Texture from render component such that each new sprite that is created 
																//will re-use the texture			

                                pParm=pParms->FirstChildElement("t");
                                while (pParm) 
                                {
                                    tile  = std::make_shared<Texture_Actor>(nullptr);
																		auto tile_render = tile->GetComponent<RenderComponent>();
																		auto current_x_Frame = std::stoi(pParm->Attribute("x"));
																		auto current_y_Frame = std::stoi(pParm->Attribute("y"));
                                    //auto tileID = std::stoi(pParm->Attribute("ID"));
                                    //int current_x_Frame;
                                    //int current_y_Frame;
				
				 /*
                                    for(int i = 0; i < xFrames; i++)
                                        for(int j = 0; j < yFrames; j++)
                                            if(multi_tile[i][j] == tileID){
                                                std::cout << "ID x:" << i << " y:" << j << std::endl;
                                                current_x_Frame = i;
                                                current_y_Frame = j;
                                            }
				*/	
                                    
                                    if(tileX_count > mapWidth)
                                    {
                                        tileX_count = 0;
																				counter_x = 0;
																				offsetX = 0.0f;
																				paddingX = 0.0f;
																				tileY_count++;
																				counter_y++;
																				if(tileY_count > 0)
																					paddingY = 0.15f;
																				if(counter_y > 4)
																				{
																					offsetY -= 2.0f;
																					counter_y = 0;
																					paddingY = 0.0f;
																				}
                                    }
                                

																		tile_render->LoadTiles(temp.GetComponent<RenderComponent>()->get_texture(), 
                                                        glm::vec2((posx + offsetX)+ paddingX*tileX_count + (tileX_count*32/10),
																																	(posy + offsetY)+ paddingY*tileY_count  + (tileY_count*32/10)),
                                                        glm::vec2(size_x, size_y), xFrames, yFrames, 0.0f,
                                                        glm::vec3(1.0f),
                                                        glm::vec2(current_x_Frame - 1, current_y_Frame ));
                                                        //glm::vec2(current_x_Frame , current_y_Frame ));
				
                                    //To fix the tile gap that occurs every 4th tile add two more variables that count to 4 and shift the tile position

                                    std::string tile_counterX = std::to_string(tileX_count); 
                                    std::string tile_counterY = std::to_string(tileY_count); 

																		tile_render->renderData(
																			xFrames, yFrames, current_x_Frame, current_y_Frame 
																		);





                                    game_objects.insert(std::make_pair(tile, key + tile_counterX + tile_counterY)); 
                                    tileX_count++;
																		counter_x++;
																		if(tileX_count > 0)
																			paddingX = 0.15f;
																			//paddingX = 0.225f;
																		if(counter_x > 4)
																		{
																			offsetX -= 1.0f;
																			//offsetX -= 2.0f;
																			counter_x = 0;
																		}
																		pParm=pParm->NextSiblingElement("t");
                           	    }	
                            }
                        }
										}
								}
						}
		}

/*

void LoadingGameObjects::Load_XML_MENU_SCREEN(const char* fileName)
{
  TiXmlDocument   doc(fileName);

            if(doc.LoadFile())
            {

                TiXmlElement *pRoot, *pBody, *pParms, *pProcess, *pApp, *pLineFormat, *pParm;
                pRoot = doc.FirstChildElement( "Main_Menu_State" );
                if ( pRoot )
                {
                    pBody= pRoot->FirstChildElement( "body" ); //body should be read
                    //while(pBody){
                    if (pBody) {
                        //pParms= pBody->FirstChildElement( "gw" ); //now params
                        //pParms= pBody->FirstChildElement( "gw" ); //now param
                       
                        if(pParms == pBody->FirstChildElement( "tx" ))
                        {

                            
                            pParm=pParms->FirstChildElement("param");
                            while (pParm) {

                                std::cout <<"MENU STATE GW::key = "<<pParm->Attribute("key")<<std::endl;
                                sfe = new sf::Sprite();
                

                                this->_data->assets.LoadTexture( pParm->Attribute("key"), pParm->Attribute("file_name"));
                                sfe->setTexture(this->_data->assets.GetTexture(pParm->Attribute("key")));
                                sfe->setTextureRect(sf::IntRect(
                                            std::stoi(pParm->Attribute("source_x")),
                                            std::stoi(pParm->Attribute("source_y")),
                                            std::stoi(pParm->Attribute("sprite_WIDTH")),
                                            std::stoi(pParm->Attribute("sprite_HEIGHT"))

                                ));
                                sfe->setPosition( std::stof(pParm->Attribute("sprite_X_POS")), std::stof(pParm->Attribute("sprite_Y_POS")));

                                //this->_sprite_Objects.insert(std::make_pair(pParm->Attribute("key"), sfe));
                                this->mm_sprite_Objects.insert(std::make_pair(pParm->Attribute("key"), sfe));

                                pParm=pParm->NextSiblingElement("param");

                            }
                        }


                        if((pParms = pBody->FirstChildElement( "gw" )))
                        {

                            
                            pParm=pParms->FirstChildElement("param");
                            while (pParm) {
                                

				                //#######################################################################				
				                //#######################################################################				
                                auto s = std::string(pParm->Attribute("dynamic"));
                                
                                if ((std::string(pParm->Attribute("dynamic")) == "true")
                                || (std::string(pParm->Attribute("dynamic")) == "True"))
                                    dynamic = true;
                                else
                                    dynamic = false;
                                
                                if ((std::string(pParm->Attribute("i_am_a_sprite_sheet")) == "true")
                                || (std::string(pParm->Attribute("i_am_a_sprite_sheet")) == "True"))
                                    i_am_sprite_sheet = true;
                                else
                                    i_am_sprite_sheet = false;
                                
                                if ((std::string(pParm->Attribute("change_frame")) == "true")
                                || (std::string(pParm->Attribute("change_frame")) == "True"))
                                    change_frames   = true;
                                else
                                   change_frames = false;
                                
                                if ((std::string(pParm->Attribute("set_physics")) == "true")
                                || (std::string(pParm->Attribute("set_physics")) == "True"))
                                    set_physics = true;
                                else
                                   set_physics = false;

                                // now loop al param elements and get their attributes
                                std::cout <<"GW::key = "
                                  << "\n" << pParm->Attribute("key")
		                          << "\n"  << pParm->Attribute("filename") 
		                          << "\n"  << dynamic
		                          << "\n"  << i_am_sprite_sheet
		                          << "\n"  << change_frames 
		                          << "\n"  << set_physics 
		                          << "\n"  << std::stoi(pParm->Attribute("x_frame"))
		                          << "\n"  << std::stoi(pParm->Attribute("y_frame"))
		                          << "\n"  << std::stof(pParm->Attribute("position_x"))
		                          << "\n"  << std::stof(pParm->Attribute("position_y"))
		                          << "\n"  << std::stof(pParm->Attribute("animation_speed"))
		                          << "\n"  << std::stof(pParm->Attribute("size_x"))
		                          << "\n"  << std::stof(pParm->Attribute("size_y"))
		                          << "\n"  << std::stof(pParm->Attribute("rotate"))
		                          << "\n"  << std::stof(pParm->Attribute("color_r"))
		                          << "\n"  << std::stof(pParm->Attribute("color_g"))
		                          << "\n"  << std::stof(pParm->Attribute("color_b"))
                                <<std::endl;

                                //manager = new EntityManager();
                                 
                                //manager.get()->Add(
                                manager->Add(
                                        pParm->Attribute("key"), 
                                        pParm->Attribute("filename"), 
                                        dynamic, 
                                        i_am_sprite_sheet, 
                                        change_frames, 
                                        set_physics,
                                        std::stoi(pParm->Attribute("x_frame")), 
                                        std::stoi(pParm->Attribute("y_frame")), 
		                                std::stof(pParm->Attribute("animation_speed")),
                                        glm::vec2(std::stof(pParm->Attribute("position_x")), std::stof(pParm->Attribute("position_y"))), 
                                        glm::vec2(std::stof(pParm->Attribute("size_x")), std::stof(pParm->Attribute("size_y"))), 
		                                std::stof(pParm->Attribute("rotate")),
                                        glm::vec3(std::stof(pParm->Attribute("color_r")), std::stof(pParm->Attribute("color_g")), std::stof(pParm->Attribute("color_b"))));
                                pParm=pParm->NextSiblingElement("param");
                            }
                        }

                    }
                }

            }

}
*/

/*
void LoadingGameObjects::Load_XML_PLAY_SCREEN(const char* fileName) 
{

        TiXmlDocument   doc(fileName);
        game_text*      text;

            if(doc.LoadFile())
            {

                TiXmlElement *pRoot, *pBody, *pParms, *pProcess, *pApp, *pLineFormat, *pParm;
                pRoot = doc.FirstChildElement( "GameWorld" );
                if ( pRoot )
                {
                    pBody= pRoot->FirstChildElement( "body" ); //body should be read
                    //while(pBody){
                    if (pBody) {
                        //pParms= pBody->FirstChildElement( "gw" ); //now params
                        //pParms= pBody->FirstChildElement( "gw" ); //now param
                       
                        if((pParms = pBody->FirstChildElement( "gw" )))
                        {

                            
                            pParm=pParms->FirstChildElement("param");
                            while (pParm) {
                                

				                //#######################################################################				
				                //#######################################################################				
                                auto s = std::string(pParm->Attribute("dynamic"));
                                
                                if ((std::string(pParm->Attribute("dynamic")) == "true")
                                || (std::string(pParm->Attribute("dynamic")) == "True"))
                                    dynamic = true;
                                else
                                    dynamic = false;
                                
                                if ((std::string(pParm->Attribute("i_am_a_sprite_sheet")) == "true")
                                || (std::string(pParm->Attribute("i_am_a_sprite_sheet")) == "True"))
                                    i_am_sprite_sheet = true;
                                else
                                    i_am_sprite_sheet = false;
                                
                                if ((std::string(pParm->Attribute("change_frame")) == "true")
                                || (std::string(pParm->Attribute("change_frame")) == "True"))
                                    change_frames   = true;
                                else
                                   change_frames = false;
                                
                                if ((std::string(pParm->Attribute("set_physics")) == "true")
                                || (std::string(pParm->Attribute("set_physics")) == "True"))
                                    set_physics = true;
                                else
                                   set_physics = false;

                                // now loop al param elements and get their attributes
                                std::cout <<"GW::key = "
                                  << "\n" << pParm->Attribute("key")
		                          << "\n"  << pParm->Attribute("filename") 
		                          << "\n"  << dynamic
		                          << "\n"  << i_am_sprite_sheet
		                          << "\n"  << change_frames 
		                          << "\n"  << set_physics 
		                          << "\n"  << std::stoi(pParm->Attribute("x_frame"))
		                          << "\n"  << std::stoi(pParm->Attribute("y_frame"))
		                          << "\n"  << std::stof(pParm->Attribute("position_x"))
		                          << "\n"  << std::stof(pParm->Attribute("position_y"))
		                          << "\n"  << std::stof(pParm->Attribute("animation_speed"))
		                          << "\n"  << std::stof(pParm->Attribute("size_x"))
		                          << "\n"  << std::stof(pParm->Attribute("size_y"))
		                          << "\n"  << std::stof(pParm->Attribute("rotate"))
		                          << "\n"  << std::stof(pParm->Attribute("color_r"))
		                          << "\n"  << std::stof(pParm->Attribute("color_g"))
		                          << "\n"  << std::stof(pParm->Attribute("color_b"))
                                <<std::endl;

                                //manager = new EntityManager();
                                 
                                //manager.get()->Add(
                                manager->Add(
                                        pParm->Attribute("key"), 
                                        pParm->Attribute("filename"), 
                                        dynamic, 
                                        i_am_sprite_sheet, 
                                        change_frames, 
                                        set_physics,
                                        std::stoi(pParm->Attribute("x_frame")), 
                                        std::stoi(pParm->Attribute("y_frame")), 
		                                std::stof(pParm->Attribute("animation_speed")),
                                        glm::vec2(std::stof(pParm->Attribute("position_x")), std::stof(pParm->Attribute("position_y"))), 
                                        glm::vec2(std::stof(pParm->Attribute("size_x")), std::stof(pParm->Attribute("size_y"))), 
		                                std::stof(pParm->Attribute("rotate")),
                                        glm::vec3(std::stof(pParm->Attribute(
                                        "color_r")), std::stof(pParm->Attribute("color_g")), std::stof(pParm->Attribute("color_b"))));
                                pParm=pParm->NextSiblingElement("param");
                            }
                        }
                        
                        if(pParms = pBody->FirstChildElement("tl"))
                        {

                            pParm=pParms->FirstChildElement("param");
                            while (pParm) {
                                
                                if ((std::string(pParm->Attribute("i_am_a_sprite_sheet")) == "true")
                                || (std::string(pParm->Attribute("i_am_a_sprite_sheet")) == "True"))
                                    i_am_sprite_sheet = true;
                                else
                                    i_am_sprite_sheet = false;
                                
                                if ((std::string(pParm->Attribute("change_frame")) == "true")
                                || (std::string(pParm->Attribute("change_frame")) == "True"))
                                    change_frames   = true;
                                else
                                   change_frames = false;
                                smart_sprites = std::make_shared<sprite>(i_am_sprite_sheet, 
                                                                             change_frames,
                                                                             48, 23, 0,
                                                                             glm::vec2(100, 100),
                                                                             glm::vec2(1536, 736),
                                                                             0,
                                                                             glm::vec3(1.0f, 1.0f, 1.0f),
                                                                             glm::vec2(0, 1)
                                                                             );
                                smart_sprites = std::make_shared<sprite>
                                            (
                                             
                                             //pParm->Attribute("filename"), 
                                             //pParm->Attribute("key"), 
                                             i_am_sprite_sheet,
						  					 change_frames,
                                             std::stoi(pParm->Attribute("x_frame")), 
                                             std::stoi(pParm->Attribute("y_frame")), 
		                                     std::stof(pParm->Attribute("animation_speed")),
                                             glm::vec2(std::stof(pParm->Attribute("position_x")  ), std::stof(pParm->Attribute("position_y") )), 
                                             glm::vec2(std::stof(pParm->Attribute("size_x")), std::stof(pParm->Attribute("size_y"))), 
		                                     std::stof(pParm->Attribute("rotate")),
                                             glm::vec3(std::stof(pParm->Attribute("color_r")), 
                                                       std::stof(pParm->Attribute("color_g")), 
                                                       std::stof(pParm->Attribute("color_b"))),
                                             glm::vec2(std::stoi(pParm->Attribute("m_frame_x")), 
                                                       std::stoi(pParm->Attribute("m_frame_y"))));

                                

                                xml_sprite_package.push_back(smart_sprites);
                                pParm=pParm->NextSiblingElement("param");
                            }
                        }
                        if(pParms = pBody->FirstChildElement("tx"))
                        {

                            pParm=pParms->FirstChildElement("param");
                            while (pParm) {
                                

                                std::cout <<
                                                pParm->Attribute("text") <<
                                    "\n" <<    std::stof(pParm->Attribute("pos_x")) << 
                                    "\n" <<    std::stof(pParm->Attribute("pos_y")) << 
                                    "\n" <<    std::stof(pParm->Attribute("scale")) << 
                                    "\n" <<    std::stof(pParm->Attribute("color_r")) << 
                                    "\n" <<    std::stof(pParm->Attribute("color_g")) << 
                                    "\n" <<    std::stof(pParm->Attribute("color_b")) << 
                                std::endl;


                                text = new game_text(
                                        
                                 std::string(pParm->Attribute("text")), 
                                 std::stof(pParm->Attribute("pos_x")), 
                                 std::stof(pParm->Attribute("pos_y")),
                                 std::stof(pParm->Attribute("scale")),
                                 std::stof(pParm->Attribute("color_r")),
                                 std::stof(pParm->Attribute("color_g")),
                                 std::stof(pParm->Attribute("color_b"))



                                );

                                //game_text text;

                                //text->text = pParm->Attribute("text"); 
                                //text->pos_x = std::stof(pParm->Attribute("pos_x")); 
                                //text->pos_y = std::stof(pParm->Attribute("pos_y"));
                                //text->scale = std::stof(pParm->Attribute("scale"));
                                //text->color_r = std::stof(pParm->Attribute("color_r"));
                                //text->color_g = std::stof(pParm->Attribute("color_g"));
                                //text->color_b = std::stof(pParm->Attribute("color_b"));

                                //xml_text_package.push_back(text);
                                //xml_text_package.push_back(text);
                                xml_text_package.push_back(text);


                                pParm=pParm->NextSiblingElement("param");

                            }
                        }
                        if((pParms = pBody->FirstChildElement( "edge" )))
                        {
                            pParm=pParms->FirstChildElement("param");
                            while (pParm) {



                                std::cout <<
                                                pParm->Attribute("key") <<
                                    "\n" <<    std::stof(pParm->Attribute("xo")) << 
                                    "\n" <<    std::stof(pParm->Attribute("yo")) << 
                                    "\n" <<    std::stof(pParm->Attribute("xd")) << 
                                    "\n" <<    std::stof(pParm->Attribute("yd")) << 
                                    "\n" <<    std::stof(pParm->Attribute("color_r")) << 
                                    "\n" <<    std::stof(pParm->Attribute("color_g")) << 
                                    "\n" <<    std::stof(pParm->Attribute("color_b")) << 
                                std::endl;


                            manager->newEdge(pParm->Attribute("key"),
                            std::stof(pParm->Attribute("xo")),
                            std::stof(pParm->Attribute("yo")),
                            std::stof(pParm->Attribute("xd")),
                            std::stof(pParm->Attribute("yd")),
                            std::stof(pParm->Attribute("color_r")),
                            std::stof(pParm->Attribute("color_g")),
                            std::stof(pParm->Attribute("color_b")));


                            
                            
                            
                            pParm=pParm->NextSiblingElement("param");

                            }
                                
                        }

                    }
                }

            }
}
*/

/*
void LoadingGameObjects::Load_XML_GAME_OVER_SCREEN(const char* fileName)
{

 TiXmlDocument   doc(fileName);
            //GameWorld*      gw;

            if(doc.LoadFile())
            {

                TiXmlElement *pRoot, *pBody, *pParms, *pProcess, *pApp, *pLineFormat, *pParm;
                pRoot = doc.FirstChildElement( "Game_Over_State" );
                if ( pRoot )
                {
                    pBody= pRoot->FirstChildElement( "body" ); //body should be read
                    //while(pBody){
                    if (pBody) {
                        //pParms= pBody->FirstChildElement( "gw" ); //now params
                        //pParms= pBody->FirstChildElement( "gw" ); //now param
                       
                        if((pParms = pBody->FirstChildElement( "gw" )))
                        {

                            
                            pParm=pParms->FirstChildElement("param");
                            while (pParm) {
                                

				                //#######################################################################				
				                //#######################################################################				
                                auto s = std::string(pParm->Attribute("dynamic"));
                                
                                if ((std::string(pParm->Attribute("dynamic")) == "true")
                                || (std::string(pParm->Attribute("dynamic")) == "True"))
                                    dynamic = true;
                                else
                                    dynamic = false;
                                
                                if ((std::string(pParm->Attribute("i_am_a_sprite_sheet")) == "true")
                                || (std::string(pParm->Attribute("i_am_a_sprite_sheet")) == "True"))
                                    i_am_sprite_sheet = true;
                                else
                                    i_am_sprite_sheet = false;
                                
                                if ((std::string(pParm->Attribute("change_frame")) == "true")
                                || (std::string(pParm->Attribute("change_frame")) == "True"))
                                    change_frames   = true;
                                else
                                   change_frames = false;
                                
                                if ((std::string(pParm->Attribute("set_physics")) == "true")
                                || (std::string(pParm->Attribute("set_physics")) == "True"))
                                    set_physics = true;
                                else
                                   set_physics = false;

                                // now loop al param elements and get their attributes
                                std::cout <<"GW::key = "
                                  << "\n" << pParm->Attribute("key")
		                          << "\n"  << pParm->Attribute("filename") 
		                          << "\n"  << dynamic
		                          << "\n"  << i_am_sprite_sheet
		                          << "\n"  << change_frames 
		                          << "\n"  << set_physics 
		                          << "\n"  << std::stoi(pParm->Attribute("x_frame"))
		                          << "\n"  << std::stoi(pParm->Attribute("y_frame"))
		                          << "\n"  << std::stof(pParm->Attribute("position_x"))
		                          << "\n"  << std::stof(pParm->Attribute("position_y"))
		                          << "\n"  << std::stof(pParm->Attribute("animation_speed"))
		                          << "\n"  << std::stof(pParm->Attribute("size_x"))
		                          << "\n"  << std::stof(pParm->Attribute("size_y"))
		                          << "\n"  << std::stof(pParm->Attribute("rotate"))
		                          << "\n"  << std::stof(pParm->Attribute("color_r"))
		                          << "\n"  << std::stof(pParm->Attribute("color_g"))
		                          << "\n"  << std::stof(pParm->Attribute("color_b"))
                                <<std::endl;

                                //manager = new EntityManager();
                                 
                                //manager.get()->Add(
                                manager->Add(
                                        pParm->Attribute("key"), 
                                        pParm->Attribute("filename"), 
                                        dynamic, 
                                        i_am_sprite_sheet, 
                                        change_frames, 
                                        set_physics,
                                        std::stoi(pParm->Attribute("x_frame")), 
                                        std::stoi(pParm->Attribute("y_frame")), 
		                                std::stof(pParm->Attribute("animation_speed")),
                                        glm::vec2(std::stof(pParm->Attribute("position_x")), std::stof(pParm->Attribute("position_y"))), 
                                        glm::vec2(std::stof(pParm->Attribute("size_x")), std::stof(pParm->Attribute("size_y"))), 
		                                std::stof(pParm->Attribute("rotate")),
                                        glm::vec3(std::stof(pParm->Attribute("color_r")), std::stof(pParm->Attribute("color_g")), std::stof(pParm->Attribute("color_b"))));
                                pParm=pParm->NextSiblingElement("param");
                            }
                        }
                        if(pParms == pBody->FirstChildElement( "tx" ))
                        {

                            
                            pParm=pParms->FirstChildElement("param");
                            while (pParm) {

                                std::cout <<"GAME OVER STATE GW::key = "<<pParm->Attribute("key")<<std::endl;

                                sfe = new sf::Sprite();

                                this->_data->assets.LoadTexture( pParm->Attribute("key"), pParm->Attribute("file_name"));
                                sfe->setTexture(this->_data->assets.GetTexture(pParm->Attribute("key")));
                                sfe->setTextureRect(sf::IntRect(
                                            std::stoi(pParm->Attribute("source_x")),
                                            std::stoi(pParm->Attribute("source_y")),
                                            std::stoi(pParm->Attribute("sprite_WIDTH")),
                                            std::stoi(pParm->Attribute("sprite_HEIGHT"))

                                ));
                                
                                sfe->setPosition( std::stof(pParm->Attribute("sprite_X_POS")), std::stof(pParm->Attribute("sprite_Y_POS")));

                                this->_sprite_Objects.insert(std::make_pair(pParm->Attribute("key"), sfe));
                                
                                
                                
                                //this->_gameObjects.insert(std::make_pair(pParm->Attribute("key"), gw));

                               // ListAllGameObjects();

                                //this->_data->manager.Add(pParm->Attribute("key"), gw(Entity));



                                pParm=pParm->NextSiblingElement("param");

                            }
                        }
                    }
                }

            }

}
*/

LoadingGameObjects::~LoadingGameObjects()
{
    printf("Deleting XML Parser!!\n");
    //delete manager;
    //xml_text_package.clear();
    //xml_sprite_package.clear();

}












