//////////////////////////////////////////////////////////////////////////////
///------------------------Component System---------------------------------
#include "../../include/Components/TransformComponent.h"
#include "../../include/Components/ShaderComponent.h"
#include "../../include/Components/RenderComponent.h"


#include "../../include/Actors/Actor.h"
#include "../../include/Actors/Texture_Actor.h"

#include "../../include/GameData/GameData.h"
#include "../../include/States/splash_state.h"


#include <algorithm>
#include <cstdio>

std::shared_ptr<Actor> gs_actor;
std::shared_ptr<Actor> animate_actor;

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

//GamePlayState::GamePlayState(GameDataRef& data) : _data(data) 
SplashState::SplashState(GameData& data)
//GamePlayState::GamePlayState(GameDataRef& data)
{

	//_data = &data;

	_data = std::move(&data);

    printf("Game Play State!\n");
//    _data = std::move(data);
    splash_fade_in_out_actor= std::make_shared<Actor>(nullptr);
   	splash_fade_in_out_actor->AddComponent<TransformComponent>(nullptr, glm::vec2(100, 100), 0.0f);
    splash_fade_in_out_actor->AddComponent<RenderComponent>(nullptr);
    splash_fade_in_out_actor->AddComponent<ShaderComponent>(nullptr);

    auto square_transform = splash_fade_in_out_actor->GetComponent<TransformComponent>();
    auto square_render =    splash_fade_in_out_actor->GetComponent<RenderComponent>();
    auto square_shader =    splash_fade_in_out_actor->GetComponent<ShaderComponent>();

    square_shader->loadShader("shaders/sprite.vs", "shaders/simple.fs");
    square_render->initRenderData();

     gs_actor  = std::make_shared<Actor>(nullptr);
         gs_actor->AddComponent<TransformComponent>(nullptr, glm::vec2(100, 100), 0.0f);
         gs_actor->AddComponent<ShaderComponent>(nullptr);
         gs_actor->AddComponent<RenderComponent>(nullptr);

         auto s_transform = gs_actor->GetComponent<TransformComponent>();
         auto s_render = gs_actor->GetComponent<RenderComponent>();
         auto s_shader = gs_actor->GetComponent<ShaderComponent>();
     s_shader->loadShader("shaders/sprite.vs", "shaders/simpleTriangle.fs");
     s_render->onCreate();


    animate_actor = std::make_shared<Actor>(nullptr);
    	animate_actor ->AddComponent<TransformComponent>(nullptr, glm::vec2(100, 100), 0.0f);
    	animate_actor ->AddComponent<RenderComponent>(nullptr);
    	animate_actor ->AddComponent<ShaderComponent>(nullptr);

    	auto animate_transform = animate_actor ->GetComponent<TransformComponent>();
    	auto animate_render= animate_actor ->GetComponent<RenderComponent>();
    	auto animate_shade = animate_actor ->GetComponent<ShaderComponent>();
    	animate_shade ->loadShader("shaders/sprite.vs", "shaders/sprite.fs");

//	animate_render->renderData(3, 4, frame_x, frame_y);

	animate_render->LoadSprite("assets/images/red.png", 
				    vec2(10, 100), 
				    vec2(95, 128), 
				    3, 4, 0.0f, 
				    vec3(1.0f), 
				    vec2(0, 1));
	
	/*
	animate_render->LoadSprite("assets/images/Cyborg_run.png", 
				    vec2(10, 100), 
				    vec2(288, 48), 
				    6, 1, 0.0f, 
				    vec3(1.0f), 
				    vec2(1, 1));
					*/
	//animate_render->animation_render_Data();



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
    gs_actor->GetComponent<RenderComponent>()->onDestroy();

}

void SplashState::Init()
{

    printf("Hello Game Play\n");

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
   // printf("Main Menu Update\n");
 //       _data.get()->manager->Update();
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
		

    std::cout << "Cos wave : " << abs(splash_fadein_wave) << std::endl;
    std::cout << "Game Time : " << glfwGetTime() << std::endl;

   // printf("Main Menu Render\n");
 
         auto s_render = gs_actor->GetComponent<RenderComponent>();
         auto s_shader = gs_actor->GetComponent<ShaderComponent>();
         auto s_transform = gs_actor->GetComponent<TransformComponent>();

	if(gs_actor){
	s_shader->Use();
                  //s_shader->SetMatrix4("projection", projection2);
                  s_shader->SetMatrix4("projection", _data->o_cam->return_matrix());
                  s_shader->SetMatrix4("model", s_transform->transform(vec2(500.0f, 100.0f), vec2(100.0f, 100.0f), 90.0f));
                  s_shader->SetVector3f("color", vec3(0.0f, 0.0f, 1.0f));
        s_render->draw();
	}

    	auto animate_transform = animate_actor ->GetComponent<TransformComponent>();
    	auto animate_render= animate_actor ->GetComponent<RenderComponent>();
    	auto animate_shade = animate_actor ->GetComponent<ShaderComponent>();
	
	if(animate_actor){
		animate_shade->Use();		
			//animate_shade->SetMatrix4("projection", projection2);
			animate_shade->SetMatrix4("projection", _data->o_cam->return_matrix());
			animate_shade->SetMatrix4("model", animate_transform->transform(vec2(100.0f, 300.0f), vec2(95.f, 125.f), 0.0f));
			animate_shade->SetVector3f("color", vec3(1.0f, 1.0f, 1.0f));
			//animate_render->renderData(3, 4, 1, 0);
			//animate_render->renderData(3, 4, frame_x, frame_y);
			animate_render->renderData(animate_render->get_sprite()->get_num_x_frames(),
						   animate_render->get_sprite()->get_num_y_frames(),
						   animate_render->get_sprite()->get_frame().x,
						   animate_render->get_sprite()->get_frame().y);
		animate_render->drawSprites();
		}


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

		
		{
			//Animation loop
			double current_time = glfwGetTime();
			if(current_time - last_time >= 0.1)
			{
				cout << "Old animation: "  << frame_x << endl;
				animate_render->get_sprite()->set_frames(vec2(frame_x, animate_render->get_sprite()->get_frame().y));
				++frame_x;

				//slower
				//last_time += 0.5;
				last_time += 0.1;
				//Faster animation
				//last_time += 0.01;

				if(frame_x > 6)
					frame_x = 0;
			}
		
		}
}
