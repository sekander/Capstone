//////////////////////////////////////////////////////////////////////////////
///------------------------Component System---------------------------------
#include "../../include/Components/TransformComponent.h"
#include "../../include/Components/TextRenderComponent.h"



#include "../../include/Actors/Text_Actor.h"


#include "../../include/GameData/GameData.h"
#include "../../include/States/loading_play_state.h"


#include <cstdio>
#include <math.h>
#include <memory>

std::shared_ptr<Text_Actor> text_loading;
std::shared_ptr<Texture_Actor> texture;
///std::shared_ptr<Shader_Actor> shader;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;



glm::mat4 projection4 = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH),
            static_cast<float>(SCR_HEIGHT), 0.0f, -1.0f, 1.0f);


LoadingPlayState::LoadingPlayState( GameData& data)
{

	_data = std::move(&data);

    printf("LOADING State!\n");

    text_loading = std::make_shared<Text_Actor>(nullptr);
    text_loading->onCreate("shaders/text.vs", "shaders/text.fs", "assets/font/Antonio-Bold.ttf", 25);

    _data->world = new b2World(b2Vec2(0, 20));
    _data->ld = new LoadingGameObjects();
}


LoadingPlayState::~LoadingPlayState()
{
    printf("Deleting LOADING State\n");
//    DeleteData();
}

void LoadingPlayState::DeleteData()
{
//    delete _data.get()->ld;
    printf("Deleting LOADING DELETE DATA State\n");

    text_loading->GetComponent<TextRenderComponent>()->onDestroy();
}

void LoadingPlayState::Init()
{
    printf("Hello LOADING State\n");
    _data->o_cam->SetPosition(glm::vec3(-5.0f, 180.0f, 0.0f));
    finishedLoading = false;
}

void LoadingPlayState::SoundUpdate()
{
    //printf("Hello Game Over Sound UPdate\n");
}

void LoadingPlayState::Input(float delta)
{
    //printf("Main Menu Input \n");
}

void LoadingPlayState::Update(float delta)
{
    if(!finishedLoading){

        //_data->ld->Load_XML_SPLASH_SCREEN("assets/xml/game_settings.xml", "body", _data->world);
        if(_data->level == LEVEL_1)
            _data->ld->Load_XML_SPLASH_SCREEN("assets/xml/game_settings.xml", "level_1", _data->world);
        else if(_data->level == LEVEL_2)
            _data->ld->Load_XML_SPLASH_SCREEN("assets/xml/game_settings.xml", "level_2", _data->world);

        finishedLoading = true;
    }
    _data->state_switch = PLAY_STATE;
}

void LoadingPlayState::Render(float delta)
{
   // printf("Main Menu Render\n");
	  text_loading->draw(projection4, "Loading ...", SCR_WIDTH/2 , SCR_HEIGHT/2);
}
