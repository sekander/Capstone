//////////////////////////////////////////////////////////////////////////////
///------------------------Component System---------------------------------
#include "../../include/Components/TransformComponent.h"
#include "../../include/Components/ShaderComponent.h"
#include "../../include/Components/RenderComponent.h"


#include "../../include/Actors/Actor.h"

#include "../../include/GameData/GameData.h"
#include "../../include/States/game_over_state.h"

/////////////////////////////////////////////////////////////////////////////
///------------------------------IMGUI--------------------------------------
#include "../../include/IMGUI/imgui.h"
#include "../../include/IMGUI/imgui_impl_glfw.h"
#include "../../include/IMGUI/imgui_impl_opengl3.h" 

#include <cstdio>
#include <math.h>


std::shared_ptr<Actor> go_fade_in_out_actor;                

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;



glm::mat4 projection3 = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH),
            static_cast<float>(SCR_HEIGHT), 0.0f, -1.0f, 1.0f);

float ss_wave;

GameOverState::GameOverState( GameData& data)
{
	_data = std::move(&data);

    printf("Game Over State!\n");


    go_fade_in_out_actor= std::make_shared<Actor>(nullptr);
   	go_fade_in_out_actor->AddComponent<TransformComponent>(nullptr, glm::vec2(100, 100), 0.0f);
    go_fade_in_out_actor->AddComponent<RenderComponent>(nullptr);
    go_fade_in_out_actor->AddComponent<ShaderComponent>(nullptr);

    auto go_square_transform = go_fade_in_out_actor->GetComponent<TransformComponent>();
    auto go_square_render = go_fade_in_out_actor->GetComponent<RenderComponent>();
    auto go_square_shader = go_fade_in_out_actor->GetComponent<ShaderComponent>();

    go_square_shader->loadShader("shaders/sprite.vs", "shaders/simple.fs");
    go_square_render->initRenderData();





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

  if(go_fade_in >= 0.0f)
  {
    go_fade_in -= 0.01f;
  }


}

void GameOverState::Render(float delta)
{
   // printf("Main Menu Render\n");
	ss_wave = 200 * sin(2 * 3.14 * 10 * (int)(glfwGetTime() * 100));
 
    
    // feed inputs to dear imgui, start new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();


    //glfwGetWindowSize(_data->window, &windowWidth, &windowHeight);
    //std::cout << "Window Width " << windowWidth << ", " << windowHeight << std::endl;

    ImGui::Begin("main", nullptr, ImGuiWindowFlags_NoDecoration |
                                ImGuiWindowFlags_NoMove );
      ImGui::SetWindowPos("main", ImVec2(10.0f, 10.0f));
      ImGui::SetWindowSize("main", ImVec2(_data->gs.SCR_WIDTH - 25 , _data->gs.SCR_HEIGHT - 25));
      ImGui::CaptureMouseFromApp(false);
      ImGui::SetWindowFontScale(1.0f);
    

        ImGui::BeginChild("Sub", ImVec2(600, 100), false, ImGuiWindowFlags_NoBackground);
          ImGui::SetWindowFontScale(2.0f);
          //ImGui::SetCursorPos(ImVec2(500, 100));
          ImGui::Text("GAME OVER!!!", ImVec2(400, 50));
        ImGui::EndChild();
      

      //ImGui::SetCursorPos(ImVec2(100, 50));
      //ImGui::Text("Title", ImVec2(200, 600));

      static bool start;
      ImGui::SetCursorPos(ImVec2(_data->gs.SCR_WIDTH/2 - 50, _data->gs.SCR_HEIGHT/2));
      start = ImGui::Button("PLAY AGAIN", ImVec2(100, 50));
      //if(start || _data->gs.start_game)
      if(start )
        _data->state_switch = LOADING_PLAY_STATE;


      static bool exit;
      ImGui::SetCursorPos(ImVec2(_data->gs.SCR_WIDTH/2 - 50, _data->gs.SCR_HEIGHT/2 + 180));
      //ImGui::SetCursorPos(ImVec2(100, 160));
      exit = ImGui::Button("EXIT", ImVec2(100, 50));
      if(exit){
        _data->gs.server_listening = false;
        _data->gs.connection_established = false;
        _data->gs.exit_app = true;
		    glfwSetWindowShouldClose(_data->window, true);
      }




    ImGui::End();
    
	ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGui::EndFrame();




























    auto go_square_transform = go_fade_in_out_actor ->GetComponent<TransformComponent>();
    auto go_square_render = go_fade_in_out_actor->GetComponent<RenderComponent>();
    auto go_square_shader = go_fade_in_out_actor->GetComponent<ShaderComponent>();

	  go_square_shader->Use();
		//square_shader->SetMatrix4("projection", projection3);
	    go_square_shader->SetMatrix4("projection", _data->o_cam->return_matrix());
        go_square_shader->SetMatrix4("model", go_square_transform->transform(
						vec2(0, 0), 
						vec2(SCR_WIDTH, SCR_HEIGHT), 0.0f));
        go_square_shader->SetVector3f("color", vec3(0.0f, 0.0f, 0.0f));
        go_square_shader->SetFloat("alpha", go_fade_in);
	    go_square_render->drawSquare();
}
