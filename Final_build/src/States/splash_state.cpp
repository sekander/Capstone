//////////////////////////////////////////////////////////////////////////////
///------------------------Component System---------------------------------
#include "../../include/Components/TransformComponent.h"
#include "../../include/Components/ShaderComponent.h"
#include "../../include/Components/RenderComponent.h"


#include "../../include/Actors/Actor.h"
#include "../../include/Actors/Text_Actor.h"

#include "../../include/GameData/GameData.h"
#include "../../include/States/splash_state.h"


#include <algorithm>
#include <cstdio>

std::shared_ptr<Text_Actor>   splash_text;

std::shared_ptr<Actor> splash_fade_in_out_actor;                


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;



glm::mat4 projection2 = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH),
            static_cast<float>(SCR_HEIGHT), 0.0f, -1.0f, 1.0f);

double last_time = glfwGetTime();

unsigned int frame_x;

using namespace std;

float splash_fadein_wave;
bool  splash_pause_fade;

SplashState::SplashState(GameData& data)
{


	_data = std::move(&data);

    printf("Game Play State!\n");
    splash_fade_in_out_actor= std::make_shared<Actor>(nullptr);
   	splash_fade_in_out_actor->AddComponent<TransformComponent>(nullptr, glm::vec2(100, 100), 0.0f);
    splash_fade_in_out_actor->AddComponent<RenderComponent>(nullptr);
    splash_fade_in_out_actor->AddComponent<ShaderComponent>(nullptr);

    auto square_transform = splash_fade_in_out_actor->GetComponent<TransformComponent>();
    auto square_render =    splash_fade_in_out_actor->GetComponent<RenderComponent>();
    auto square_shader =    splash_fade_in_out_actor->GetComponent<ShaderComponent>();

    square_shader->loadShader("shaders/sprite.vs", "shaders/simple.fs");
    square_render->initRenderData();


	splash_text = std::make_shared<Text_Actor>(nullptr);
	


	x_cam = 0.0f;
	y_cam = 0.0f;
	z_cam = 0.0f;
	r_cam = 0.0f;

	z_scale.x = 1.0f;
	z_scale.y = 1.0f;

	splash_pause_fade = false;
}


SplashState::~SplashState()
{
    printf("Deleting Game Play State\n");
//    DeleteData();
}

void SplashState::DeleteData()
{
//    delete _data.get()->ld;
    printf("Deleting Game Play State\n");
}

void SplashState::Init()
{

    printf("Hello Game Play\n");
	
	splash_text->onCreate(
	"shaders/text.vs", 
	"shaders/text.fs", 
	"assets/font/Antonio-Bold.ttf", 
	25);

}

void SplashState::SoundUpdate()
{
    //printf("Hello Splah State Sound UPdate\n");
}


void SplashState::Input(float delta)
{
    //printf("Main Menu Input \n");
    if (glfwGetKey(_data->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
	    x_cam -=5;
	    _data->o_cam->SetPosition(glm::vec3(x_cam, y_cam, z_cam));
            std::cout << "X cam : " << x_cam  << std::endl;
    }
    if (glfwGetKey(_data->window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
	    x_cam +=5;
	    _data->o_cam->SetPosition(glm::vec3(x_cam, y_cam, z_cam));
            std::cout << "X cam : " << x_cam  << std::endl;
    }
    if (glfwGetKey(_data->window, GLFW_KEY_UP) == GLFW_PRESS)
    {
	    y_cam +=5;
	    _data->o_cam->SetPosition(glm::vec3(x_cam, y_cam, z_cam));
            std::cout << "Y cam : " << y_cam  << std::endl;
    }
    if (glfwGetKey(_data->window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
	    y_cam -=5;
	    _data->o_cam->SetPosition(glm::vec3(x_cam, y_cam, z_cam));
            std::cout << "Y cam : " << y_cam  << std::endl;
    }
    if (glfwGetKey(_data->window, GLFW_KEY_E) == GLFW_PRESS)
    {
	    r_cam +=0.01;
	    _data->o_cam->SetRotation(r_cam);
            std::cout << "R cam : " << r_cam  << std::endl;
    }

    if (glfwGetKey(_data->window, GLFW_KEY_Q) == GLFW_PRESS)
    {
	    r_cam -=0.01;
	    _data->o_cam->SetRotation(r_cam);
            std::cout << "R cam : " << r_cam  << std::endl;
    }

    if (glfwGetKey(_data->window, GLFW_KEY_Z) == GLFW_PRESS)
    {
	    z_scale.x += 0.01;
	    z_scale.y += 0.01;
	    _data->o_cam->SetScale(z_scale);
            std::cout << "Z-x cam : " << z_scale.x << std::endl;
            std::cout << "Z-y cam : " << z_scale.y << std::endl;
    }

    if (glfwGetKey(_data->window, GLFW_KEY_X) == GLFW_PRESS)
    {
	    z_scale.x -= 0.01;
	    z_scale.y -= 0.01;
	    _data->o_cam->SetScale(z_scale);
            std::cout << "Z-x cam : " << z_scale.x << std::endl;
            std::cout << "Z-y cam : " << z_scale.y << std::endl;
    }

}

void SplashState::Update(float delta)
{
	_data->o_cam->SetPosition(glm::vec3(x_cam, y_cam, z_cam));
	_data->o_cam->SetRotation(r_cam);
	_data->o_cam->SetScale(z_scale);
}

void SplashState::Render(float delta)
{
    if(!splash_pause_fade)
      splash_fadein_wave = 1 * cos(2 * 3.14 * 0.001 * (int)(glfwGetTime() * 100));

    if(splash_fadein_wave < 0.1 && !splash_pause_fade)
      splash_pause_fade = true;

    if(glfwGetTime() > 5.0){
      splash_fadein_wave = 1 * sin(2 * 3.14 * 0.001 * (int)(glfwGetTime() * 100));
    }
    if(glfwGetTime() > 7.5)
		_data->state_switch = MAIN_MENU_STATE;
		

	splash_text->draw(
		_data->o_cam->return_matrix(), 
		"CREATED BY : NAHID SEKANDER", 
		SCR_WIDTH/2 - 100, 
		SCR_HEIGHT/2,
		0.75f,
		1.0f, 1.0f, 1.0f);

    auto square_transform = splash_fade_in_out_actor ->GetComponent<TransformComponent>();
    auto square_render 	  = splash_fade_in_out_actor->GetComponent<RenderComponent>();
    auto square_shader 	  = splash_fade_in_out_actor->GetComponent<ShaderComponent>();


	 square_shader->Use();
		//square_shader->SetMatrix4("projection", projection3);
		square_shader->SetMatrix4("projection", _data->o_cam->return_matrix());
    square_shader->SetMatrix4("model", square_transform->transform(
						vec2(0, 0), 
						vec2(SCR_WIDTH, SCR_HEIGHT), 0.0f));
    square_shader->SetVector3f("color", vec3(0.0f, 0.0f, 0.0f));
    square_shader->SetFloat("alpha", abs(splash_fadein_wave));
	 square_render->drawSquare();

}
