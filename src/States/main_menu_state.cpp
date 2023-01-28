/////////////////////////////////////////////////////////////////////////////
///-------------------------------ALUT--------------------------------------
#include <AL/al.h>
#include <AL/alut.h>
/////////////////////////////////////////////////////////////////////////////
///------------------------------IMGUI--------------------------------------
#include "../../include/IMGUI/imgui.h"
#include "../../include/IMGUI/imgui_impl_glfw.h"
#include "../../include/IMGUI/imgui_impl_opengl3.h" 
//////////////////////////////////////////////////////////////////////////////
///------------------------Component System---------------------------------
#include "../../include/Components/TransformComponent.h"
#include "../../include/Components/ShaderComponent.h"
#include "../../include/Components/RenderComponent.h"

#include "../../include/Actors/Actor.h"

#include "../../include/GameData/GameData.h"
#include "../../include/States/main_menu_state.h"


#include <cstdio>


#include <chrono>
#include <mutex>
#include <future>

std::shared_ptr<Actor> s_actor;
std::shared_ptr<Actor> sprite_actor;

std::shared_ptr<Actor> fade_in_out_actor;                

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//These creates a memory leak
ALuint helloBuffer, helloSource;
ALint state;

bool stop_audio;
bool stop_update;

float fadein_wave;
bool pause_fade;
double clicked_time;
bool main_menu_button;
bool start_fade;

using namespace std::chrono_literals;

void render_conan_logo()
{
	ImDrawList *draw_list = ImGui::GetWindowDrawList();
	float sz = 300.0f;
	static ImVec4 col1 = ImVec4(68.0 / 255.0, 83.0 / 255.0, 89.0 / 255.0, 1.0f);
	static ImVec4 col2 = ImVec4(40.0 / 255.0, 60.0 / 255.0, 80.0 / 255.0, 1.0f);
	static ImVec4 col3 = ImVec4(50.0 / 255.0, 65.0 / 255.0, 82.0 / 255.0, 1.0f);
	static ImVec4 col4 = ImVec4(20.0 / 255.0, 40.0 / 255.0, 60.0 / 255.0, 1.0f);
	const ImVec2 p = ImGui::GetCursorScreenPos();
	float x = p.x + 4.0f, y = p.y + 4.0f;
	
  draw_list->AddQuadFilled(ImVec2(x, y + 0.25 * sz), 
                             ImVec2(x + 0.5 * sz, y + 0.5 * sz), 
                             ImVec2(x + sz, y + 0.25 * sz), 
                             ImVec2(x + 0.5 * sz, y), 
                             ImColor(col1));

	draw_list->AddQuadFilled(ImVec2(x, y + 0.25 * sz), 
                             ImVec2(x + 0.5 * sz, y + 0.5 * sz), 
                             ImVec2(x + 0.5 * sz, y + 1.0 * sz), 
                             ImVec2(x, y + 0.75 * sz), 
                             ImColor(col2));

	draw_list->AddQuadFilled(ImVec2(x + 0.5 * sz, y + 0.5 * sz), 
                             ImVec2(x + sz, y + 0.25 * sz), 
                             ImVec2(x + sz, y + 0.75 * sz), 
                             ImVec2(x + 0.5 * sz, y + 1.0 * sz), 
                             ImColor(col3));
	
  draw_list->AddLine(ImVec2(x + 0.75 * sz, y + 0.375 * sz), 
                       ImVec2(x + 0.75 * sz, y + 0.875 * sz), 
                       ImColor(col4));

  draw_list->AddBezierCurve(ImVec2(x + 0.72 * sz, y + 0.24 * sz), 
                              ImVec2(x + 0.68 * sz, y + 0.15 * sz), 
                              ImVec2(x + 0.48 * sz, y + 0.13 * sz), 
                              ImVec2(x + 0.39 * sz, y + 0.17 * sz), 
                              ImColor(col4), 10, 18);

  draw_list->AddBezierCurve(ImVec2(x + 0.39 * sz, y + 0.17 * sz), 
                              ImVec2(x + 0.2 * sz, y + 0.25 * sz), 
                              ImVec2(x + 0.3 * sz, y + 0.35 * sz), 
                              ImVec2(x + 0.49 * sz, y + 0.38 * sz), 
                              ImColor(col4), 10, 18);
}

glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH),
            static_cast<float>(SCR_HEIGHT), 0.0f, -1.0f, 1.0f);

MainMenuState::MainMenuState(GameData& data)
{
    _data = std::move(&data);
    printf("Main Menu State!\n");
    
    fade_in_out_actor= std::make_shared<Actor>(nullptr);
   	fade_in_out_actor->AddComponent<TransformComponent>(nullptr, glm::vec2(100, 100), 0.0f);
    fade_in_out_actor->AddComponent<RenderComponent>(nullptr);
    fade_in_out_actor->AddComponent<ShaderComponent>(nullptr);

    auto square_transform = fade_in_out_actor->GetComponent<TransformComponent>();
    auto square_render = fade_in_out_actor->GetComponent<RenderComponent>();
    auto square_shader = fade_in_out_actor->GetComponent<ShaderComponent>();

    square_shader->loadShader("shaders/sprite.vs", "shaders/simple.fs");
    square_render->initRenderData();

    s_actor  = std::make_shared<Actor>(nullptr);
    s_actor->AddComponent<TransformComponent>(nullptr, glm::vec2(100, 100), 0.0f);
    s_actor->AddComponent<ShaderComponent>(nullptr);
    s_actor->AddComponent<RenderComponent>(nullptr);

    auto s_transform = s_actor->GetComponent<TransformComponent>();
    auto s_render = s_actor->GetComponent<RenderComponent>();
    auto s_shader = s_actor->GetComponent<ShaderComponent>();
    s_shader->loadShader("shaders/sprite.vs", "shaders/simpleTriangle.fs");
    s_render->onCreate();

    sprite_actor = std::make_shared<Actor>(nullptr);
    sprite_actor->AddComponent<TransformComponent>(nullptr, glm::vec2(100, 100), 0.0f);
    sprite_actor->AddComponent<RenderComponent>(nullptr);
    sprite_actor->AddComponent<ShaderComponent>(nullptr);

    auto sprite_transform = sprite_actor->GetComponent<TransformComponent>();
    auto sprite_render = sprite_actor->GetComponent<RenderComponent>();
    auto sprite_shader = sprite_actor->GetComponent<ShaderComponent>();
    sprite_shader->loadShader("shaders/sprite.vs", "shaders/sprite.fs");

    sprite_render->initRenderData();
    sprite_render->LoadSprite("assets/images/spiderman.png", vec2(100, 100), vec2(100, 100));

  
}

MainMenuState::~MainMenuState()
{
    printf("Deleting Main Menu\n");
      // Cleanup
//    DeleteData();
}

void MainMenuState::DeleteData()
{
//    delete _data.get()->ld;
      printf("Deleting Main Menu\n");
      s_actor->GetComponent<RenderComponent>()->onDestroy();


      // Cleanup
      ImGui_ImplOpenGL3_Shutdown();
      ImGui_ImplGlfw_Shutdown();
      ImGui::DestroyContext();
    
        stop_audio = true;
      //Stop audio loop
//      stop_audio = true;

      //Delete alut
      //
      alDeleteSources(1, &helloSource);
      alDeleteBuffers(1, &helloBuffer);
      alutExit();
}

void MainMenuState::Init()
{
      printf("Hello Main Menu\n");
      x_cam = 0.0f;
      y_cam = 0.0f;
      z_cam = 0.0f;
      r_cam = 0.0f;

      z_scale.x = 1.0f;
      z_scale.y = 1.0f;
    
      stop_audio = false;
      stop_update = false;
      //state = AL_PLAYING;
      //state = AL_LOOPING;
      pause_fade = false;
      main_menu_button = false;
      start_fade = false;
      

      // Setup Dear ImGui context
      IMGUI_CHECKVERSION();
      ImGui::CreateContext();
      ImGuiIO &io = ImGui::GetIO();
      // Setup Platform/Renderer bindings
      ImGui_ImplGlfw_InitForOpenGL(_data->window, true);
      ImGui_ImplOpenGL3_Init("#version 330 core");
      // Setup Dear ImGui style
      ImGui::StyleColorsDark();

//These creates a memory leak
      //Initialize alut
      alutInit(0, NULL);
      //helloBuffer = alutCreateBufferHelloWorld();
      //helloBuffer = alutCreateBufferFromFile("assets/sound/main_menu.wav");
      helloBuffer = alutCreateBufferFromFile("assets/sound/main_menu.wav");
      alGenSources(1, &helloSource);
      alSourcei(helloSource, AL_BUFFER, helloBuffer); 
  
}

void MainMenuState::SoundUpdate()
{
    //printf("Hello Main Menu Sound UPdate\n");
    alSourcePlay(helloSource);
    do {
      alGetSourcei(helloSource, AL_SOURCE_STATE, &state);
        if(stop_audio)
            break;


    }while(state ==  AL_PLAYING);
    //std::this_thread::sleep_for(10s);

}

void MainMenuState::Input(float delta)
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

    if (glfwGetKey(_data->window, GLFW_KEY_P) == GLFW_PRESS)
    {
      std::cout << "Stop audio" << std::endl;
      //state = AL_PLAYING;
      state = AL_TRUE;
      alSourceStop(helloSource);
    }
    
    if (glfwGetKey(_data->window, GLFW_KEY_O) == GLFW_PRESS)
    {
      std::cout << "Start audio" << std::endl;
      //state = AL_PAUSED;
      //state = AL_FALSE;
      state = AL_PLAYING;
    }
}

void MainMenuState::Update(float delta)
{
 if(!stop_update){ 
	_data->o_cam->SetPosition(glm::vec3(x_cam, y_cam, z_cam));
	_data->o_cam->SetRotation(r_cam);
	_data->o_cam->SetScale(z_scale);
 }
   // printf("Main Menu Update\n");
 //       _data.get()->manager->Update();
}

void MainMenuState::Render(float delta)
{

    std::cout << "Time passed : " << glfwGetTime() << std::endl;


    //fadein_wave = 200 * sin(2 * 3.14 * 10 * (int)(glfwGetTime() * 100));
    if(!pause_fade){
      fadein_wave = 1 * cos(2 * 3.14 * 0.01 * (int)(glfwGetTime() * 100));
       
     //if(fadein_wave < 0.1)
     //   pause_fade = true;
    }

      
    //Temp fix add a seperate timer 
    if(fadein_wave < 0.05){
    //if(glfwGetTime() > 9.5){
      //fadein_wave = 1 * sin(2 * 3.14 * 0.001 * (int)(glfwGetTime() * 100));
      //if(fadein_wave > 0.95)
      //  std::cout << "TIME TO CHANGE SCREEN" << std::endl;
      pause_fade = true;
    }

    std::cout << "Cos wave : " << abs(fadein_wave) << std::endl;



    // feed inputs to dear imgui, start new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

    // render your GUI
	ImGui::Begin("Triangle Position/Color");
  static bool change_to_game_over = false;
  change_to_game_over = ImGui::Button("Press Me");
  if(change_to_game_over)
  {
    clicked_time = glfwGetTime();
    main_menu_button = true; 
    //if(glfwGetTime() > clicked_time + 3.0)
  }

  if(main_menu_button){
    fadein_wave = 1 * sin(2 * 3.14 * 0.001 * (int)(glfwGetTime() * 100));

    if((glfwGetTime() > clicked_time + 1.5)) 
        _data->state_switch = LOADING_PLAY_STATE;
  }
  //std::cout << "Clicked Time : " << clicked_time << std::endl; 
  //if(main_menu_button && (glfwGetTime() > clicked_time + 1.5)) 
  //    _data->state_switch = LOADING_PLAY_STATE;


	static float rotation = 0.0;
	ImGui::SliderFloat("rotation", &rotation, 0, 2 * 3.14);
	static float translation[] = {0.0, 0.0};
	//ImGui::SliderFloat2("position", translation, -1.0, 1.0);
	ImGui::SliderFloat2("position", translation, 0.0, 600.0);
        static float color[4] = { 1.0f,1.0f,1.0f,1.0f };
        // color picker
        ImGui::ColorEdit3("color", color);
        ImGui::End();

        ImGui::Begin("Conan logo");
        render_conan_logo();
        ImGui::End();
	// Render dear imgui into screen
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

   // printf("Main Menu Render\n");
  //if(!stop_update)
  {
     auto s_render = s_actor->GetComponent<RenderComponent>();
     auto s_shader = s_actor->GetComponent<ShaderComponent>();
     auto s_transform = s_actor->GetComponent<TransformComponent>();
     s_shader->Use();
          //s_shader->SetMatrix4("projection", projection);
          s_shader->SetMatrix4("projection", _data->o_cam->return_matrix());
          s_shader->SetMatrix4("model", s_transform->transform(vec2(400.0f, 100.0f), vec2(100.0f, 100.0f), 90.0f));
          //s_shader->SetVector3f("color", vec3(1.0f, 0.0f, 0.0f));
          s_shader->SetVector3f("color", vec3(color[0], color[1], color[2]));
     s_render->draw();



    auto sprite_render = sprite_actor->GetComponent<RenderComponent>();
    auto sprite_shader = sprite_actor->GetComponent<ShaderComponent>();
    auto sprite_transform = sprite_actor->GetComponent<TransformComponent>();
    sprite_shader->Use();
        sprite_shader->SetMatrix4("projection", _data->o_cam->return_matrix());
        sprite_shader->SetVector3f("color", vec3(1.0f, 1.0f, 1.0f));
        //sprite_shader->SetMatrix4("model", sprite_transform->transform(vec2(125, 325), vec2(100, 100), 0.0f));
        sprite_shader->SetMatrix4("model", sprite_transform->transform(vec2(translation[0], translation[1]), vec2(100, 100), rotation));
    sprite_render->drawSprites();
	  
    
    auto square_transform = fade_in_out_actor ->GetComponent<TransformComponent>();
    auto square_render = fade_in_out_actor->GetComponent<RenderComponent>();
    auto square_shader = fade_in_out_actor->GetComponent<ShaderComponent>();


	 square_shader->Use();
		//square_shader->SetMatrix4("projection", projection3);
		square_shader->SetMatrix4("projection", _data->o_cam->return_matrix());
    square_shader->SetMatrix4("model", square_transform->transform(
						vec2(0, 0), 
						vec2(SCR_WIDTH, SCR_HEIGHT), 0.0f));
    square_shader->SetVector3f("color", vec3(0.0f, 0.0f, 0.0f));
    square_shader->SetFloat("alpha", abs(fadein_wave));
	 square_render->drawSquare();

  }
}
