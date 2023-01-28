//////////////////////////////////////////////////////////////////////////////
///------------------------Component System---------------------------------
#include "../../include/Components/TransformComponent.h"
#include "../../include/Components/ShaderComponent.h"
#include "../../include/Components/RenderComponent.h"


#include "../../include/Actors/Actor.h"

#include "../../include/GameData/GameData.h"
#include "../../include/States/game_over_state.h"


#include <cstdio>
#include <math.h>

std::shared_ptr<Actor> ss_actor;
std::shared_ptr<Actor> square_actor;                


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;



glm::mat4 projection3 = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH),
            static_cast<float>(SCR_HEIGHT), 0.0f, -1.0f, 1.0f);

float ss_wave;

GameOverState::GameOverState( GameData& data)
{

	//_data = &data;
	
	_data = std::move(&data);

    printf("Game Over State!\n");

//    _data = std::move(data);
     ss_actor  = std::make_shared<Actor>(nullptr);
         ss_actor->AddComponent<TransformComponent>(nullptr, glm::vec2(100, 100), 0.0f);
         ss_actor->AddComponent<ShaderComponent>(nullptr);
         ss_actor->AddComponent<RenderComponent>(nullptr);

         auto s_transform = ss_actor->GetComponent<TransformComponent>();
         auto s_render = ss_actor->GetComponent<RenderComponent>();
         auto s_shader = ss_actor->GetComponent<ShaderComponent>();
     s_shader->loadShader("shaders/sprite.vs", "shaders/simpleTriangle.fs");
     s_render->onCreate();


    square_actor  = std::make_shared<Actor>(nullptr);
   	square_actor ->AddComponent<TransformComponent>(nullptr, glm::vec2(100, 100), 0.0f);
    	square_actor ->AddComponent<RenderComponent>(nullptr);
        square_actor->AddComponent<ShaderComponent>(nullptr);

    	auto square_transform = square_actor ->GetComponent<TransformComponent>();
    	auto square_render = square_actor ->GetComponent<RenderComponent>();
    	auto square_shader = square_actor ->GetComponent<ShaderComponent>();

    square_shader->loadShader("shaders/sprite.vs", "shaders/hypno.fs");
    square_render->initRenderData();

	x_cam = 0.0f;
	y_cam = 0.0f;
	z_cam = 0.0f;
	r_cam = 0.0f;

	z_scale.x = 1.0f;
	z_scale.y = 1.0f;
}


GameOverState::~GameOverState()
{
    printf("Deleting Game Over State\n");
//    DeleteData();
}

void GameOverState::DeleteData()
{
//    delete _data.get()->ld;
    printf("Deleting Game Over State\n");
    ss_actor->GetComponent<RenderComponent>()->onDestroy();

}

void GameOverState::Init()
{
    printf("Hello Game Over State\n");
}

void GameOverState::SoundUpdate()
{
    //printf("Hello Game Over Sound UPdate\n");
}

void GameOverState::Input(float delta)
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

void GameOverState::Update(float delta)
{
	_data->o_cam->SetPosition(glm::vec3(x_cam, y_cam, z_cam));
	_data->o_cam->SetRotation(r_cam);
	_data->o_cam->SetScale(z_scale);
   // printf("Main Menu Update\n");
 //       _data.get()->manager->Update();
}

void GameOverState::Render(float delta)
{
   // printf("Main Menu Render\n");
	ss_wave = 200 * sin(2 * 3.14 * 10 * (int)(glfwGetTime() * 100));
 
         auto s_render = ss_actor->GetComponent<RenderComponent>();
         auto s_shader = ss_actor->GetComponent<ShaderComponent>();
         auto s_transform = ss_actor->GetComponent<TransformComponent>();

	 s_shader->Use();
                  //s_shader->SetMatrix4("projection", projection3);
                  s_shader->SetMatrix4("projection", _data->o_cam->return_matrix());
                  s_shader->SetMatrix4("model", s_transform->transform(vec2(100.0f, 200.0f), vec2(100.0f, 100.0f), 90.0f));
                  s_shader->SetVector3f("color", vec3(1.0f, 1.0f, 0.0f));
         s_render->draw();



    	 auto square_transform = square_actor ->GetComponent<TransformComponent>();
    	 auto square_render = square_actor ->GetComponent<RenderComponent>();
    	 auto square_shader = square_actor ->GetComponent<ShaderComponent>();
 	
	 square_shader->Use();
		//square_shader->SetMatrix4("projection", projection3);
		square_shader->SetMatrix4("projection", _data->o_cam->return_matrix());
		square_shader->SetMatrix4("model", square_transform->transform(
						vec2(125 - abs(ss_wave)/2 + 200, 325 - abs(ss_wave)/2 - 200), 
						vec2(abs(ss_wave) + 250.f,abs(ss_wave) + 250.f), 0.0f));
		square_shader->SetFloat("R", 1.0f);
		square_shader->SetFloat("G", 0.0f);
		square_shader->SetFloat("B", 0.5f);
		square_shader->SetFloat("time", glfwGetTime());
	 square_render->drawSquare();





}
