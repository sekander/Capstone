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
#include "../../include/Components/NetworkComponent.h"

#include "../../include/Actors/Actor.h"

#include "../../include/GameData/GameData.h"
#include "../../include/States/main_menu_state.h"

#include "../../include/GameData/ObjectCounter.h"
#include <GLFW/glfw3.h>
#include <cstdio>


#include <chrono>
#include <memory>
#include <mutex>
#include <future>


std::shared_ptr<Actor> fade_in_out_actor;                

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//These creates a memory leak

//ALuint *helloBuffer, *helloSource;

//std::shared_ptr<ALuint> helloBuffer;
//std::shared_ptr<ALuint> helloSource;

ALuint helloBuffer, helloSource;
ALint state;

bool stop_audio;
bool stop_update;

float fadein_wave;
bool pause_fade;
double clicked_time;
bool main_menu_button;
bool start_fade;



int windowWidth = 0;
int windowHeight = 0;

using namespace std::chrono_literals;

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
      printf("Deleting Main Menu DATA\n");


      // Cleanup
      //ImGui_ImplOpenGL3_Shutdown();
      //ImGui_ImplGlfw_Shutdown();
      //ImGui::DestroyContext();
    
      //Stop audio loop
      stop_audio = true;

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
      ImGuiStyle& style = ImGui::GetStyle();
     

      ImVec4* colors = ImGui::GetStyle().Colors;
      colors[ImGuiCol_Text]                   = ImVec4(0.75f, 0.75f, 0.75f, 1.00f);
      colors[ImGuiCol_TextDisabled]           = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
      colors[ImGuiCol_WindowBg]               = ImVec4(0.00f, 0.00f, 0.00f, 0.94f);
      colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
      colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
      colors[ImGuiCol_Border]                 = ImVec4(0.75f, 0.00f, 0.00f, 0.50f);
      colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.50f, 0.00f);
      colors[ImGuiCol_FrameBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.54f);
      colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.37f, 0.14f, 0.14f, 0.67f);
      colors[ImGuiCol_FrameBgActive]          = ImVec4(0.39f, 0.20f, 0.20f, 0.67f);
      colors[ImGuiCol_TitleBg]                = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
      colors[ImGuiCol_TitleBgActive]          = ImVec4(0.48f, 0.16f, 0.16f, 1.00f);
      colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.48f, 0.16f, 0.16f, 1.00f);
      colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
      colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
      colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
      colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
      colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
      colors[ImGuiCol_CheckMark]              = ImVec4(0.56f, 0.10f, 0.10f, 1.00f);
      colors[ImGuiCol_SliderGrab]             = ImVec4(1.00f, 0.19f, 0.19f, 0.40f);
      colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.89f, 0.00f, 0.19f, 1.00f);
      colors[ImGuiCol_Button]                 = ImVec4(1.00f, 0.19f, 0.19f, 0.40f);
      colors[ImGuiCol_ButtonHovered]          = ImVec4(0.80f, 0.17f, 0.00f, 1.00f);
      colors[ImGuiCol_ButtonActive]           = ImVec4(0.89f, 0.00f, 0.19f, 1.00f);
      colors[ImGuiCol_Header]                 = ImVec4(0.33f, 0.35f, 0.36f, 0.53f);
      colors[ImGuiCol_HeaderHovered]          = ImVec4(0.76f, 0.28f, 0.44f, 0.67f);
      colors[ImGuiCol_HeaderActive]           = ImVec4(0.47f, 0.47f, 0.47f, 0.67f);
      colors[ImGuiCol_Separator]              = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
      colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
      colors[ImGuiCol_SeparatorActive]        = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
      colors[ImGuiCol_ResizeGrip]             = ImVec4(1.00f, 1.00f, 1.00f, 0.85f);
      colors[ImGuiCol_ResizeGripHovered]      = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
      colors[ImGuiCol_ResizeGripActive]       = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
      colors[ImGuiCol_Tab]                    = ImVec4(0.07f, 0.07f, 0.07f, 0.51f);
      colors[ImGuiCol_TabHovered]             = ImVec4(0.86f, 0.23f, 0.43f, 0.67f);
      colors[ImGuiCol_TabActive]              = ImVec4(0.19f, 0.19f, 0.19f, 0.57f);
      colors[ImGuiCol_TabUnfocused]           = ImVec4(0.05f, 0.05f, 0.05f, 0.90f);
      colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.13f, 0.13f, 0.13f, 0.74f);
      colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
      colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
      colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
      colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
      colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
      colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
      colors[ImGuiCol_TableBorderLight]       = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
      colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
      colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.07f);
      colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
      colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
      colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
      colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
      colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
      colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
    
 











      //io.Fonts->AddFontFromFileTTF("assets/font/Minecraft.ttf", 24.0f);
      io.Fonts->AddFontFromFileTTF("assets/font/Antonio-Bold.ttf", 24.0f);

      //These creates a memory leak
      //Initialize alut
      //helloBuffer = alutCreateBufferHelloWorld();
      //helloBuffer = alutCreateBufferFromFile("assets/sound/main_menu.wav");
      alutInit(0, NULL);
      helloBuffer = alutCreateBufferFromFile("assets/sound/main_menu.wav");
      alGenSources(1, &helloSource);
      alSourcei(helloSource, AL_BUFFER, helloBuffer); 
      
		std::cout << "Total Number of Textures " << ObjectCounter::texture_actor_counter << std::endl;
		std::cout << "Total Number of NPC " << ObjectCounter::npc_actor_counter << std::endl;
		std::cout << "Total Number of Animator " << ObjectCounter::animation_actor_counter << std::endl;
		std::cout << "Total Number of Projectile " << ObjectCounter::projectile_actor_counter << std::endl;
		
		std::cout << "Total Number of RenderComponents " << ObjectCounter::render_component_counter << std::endl;
		std::cout << "Total Number of TransformComponents " << ObjectCounter::transform_component_counter << std::endl;
		std::cout << "Total Number of PhysicsComponents " << ObjectCounter::physic_component_counter << std::endl;
		std::cout << "Total Number of AI Componets " << ObjectCounter::ai_component_counter << std::endl;
  
}

float main_menu_volume = 0.25f;

void MainMenuState::SoundUpdate()
{
    //printf("Hello Main Menu Sound UPdate\n");
    alSourcePlay(helloSource);
    do {
      alGetSourcei(helloSource, AL_SOURCE_STATE, &state);
      alSourcef(helloSource, AL_GAIN, main_menu_volume);
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
      state = AL_STOPPED;
      alSourceStop(helloSource);
    }
    
    if (glfwGetKey(_data->window, GLFW_KEY_O) == GLFW_PRESS)
    {
      std::cout << "Start audio" << std::endl;
      state = AL_PAUSED;
      //state = AL_FALSE;
      //state = AL_PLAYING;
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






  if(fade >= 0.0f)
  {
    fade -= 0.01f;
  }

}

bool menu_screen = false;

void MainMenuState::Render(float delta)
{















    //std::cout << "Time passed : " << glfwGetTime() << std::endl;
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

    //std::cout << "Cos wave : " << abs(fadein_wave) << std::endl;




    // feed inputs to dear imgui, start new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();


    glfwGetWindowSize(_data->window, &windowWidth, &windowHeight);
    //std::cout << "Window Width " << windowWidth << ", " << windowHeight << std::endl;

    ImGui::Begin("main", nullptr, ImGuiWindowFlags_NoDecoration |
                                ImGuiWindowFlags_NoMove );
      ImGui::SetWindowPos("main", ImVec2(10.0f, 10.0f));
      ImGui::SetWindowSize("main", ImVec2(windowWidth - 25 , windowHeight - 25));
      ImGui::CaptureMouseFromApp(false);
      ImGui::SetWindowFontScale(1.0f);
    

        ImGui::BeginChild("Sub", ImVec2(600, 100), false, ImGuiWindowFlags_NoBackground);
          ImGui::SetWindowFontScale(2.0f);
          //ImGui::SetCursorPos(ImVec2(500, 100));
          ImGui::Text("                 2D Zombie \n                   Survival", ImVec2(400, 50));
        ImGui::EndChild();
      

      //ImGui::SetCursorPos(ImVec2(100, 50));
      //ImGui::Text("Title", ImVec2(200, 600));

      static bool start;
      ImGui::SetCursorPos(ImVec2(windowWidth/2 - 50, windowHeight/2));
      start = ImGui::Button("START", ImVec2(100, 50));
      if(start || _data->gs.start_game)
        _data->state_switch = LOADING_PLAY_STATE;

      static bool network;
      ImGui::SetCursorPos(ImVec2(windowWidth/2 - 50, windowHeight/2 + 60));
      //ImGui::SetCursorPos(ImVec2(130, 200));
      network = ImGui::Button("SERVER", ImVec2(100, 50));
      if(network){
//         ImGui::BeginChild("Network", ImVec2(100, 100), false, ImGuiWindowFlags_NoBackground);
          _data->gs.server_on = true;
          _data->gs.searching_for_connection = true;
		    //glfwSetWindowShouldClose(_data->window, true);
      }

      if(_data->gs.connection_established && !_data->gs.searching_for_connection)
      {
          ImGui::SetCursorPos(ImVec2(400, 100));
          ImGui::TextColored(ImColor(0, 255, 0), "Connection Established");
      }



      
      static bool game_over;
      ImGui::SetCursorPos(ImVec2(windowWidth/2 - 50, windowHeight/2 + 120));
      //ImGui::SetCursorPos(ImVec2(130, 240));
      game_over = ImGui::Button("MENU", ImVec2(100, 50));
      if(game_over){
          menu_screen = true;
        //_data->state_switch = GAME_OVER_STATE;
        //_data->gs.server_on = true;
        //glfwSetWindowShouldClose(_data->window, true);
      }

      static bool exit;
      ImGui::SetCursorPos(ImVec2(windowWidth/2 - 50, windowHeight/2 + 180));
      //ImGui::SetCursorPos(ImVec2(100, 160));
      exit = ImGui::Button("EXIT", ImVec2(100, 50));
      if(exit){
        _data->gs.server_listening = false;
        _data->gs.connection_established = false;
        _data->gs.exit_app = true;
		    glfwSetWindowShouldClose(_data->window, true);
      }




    ImGui::End();
    
    if(menu_screen)
    {
        ImGui::Begin("MENU", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
        ImGui::SetWindowPos("MENU", ImVec2(windowWidth/2 - 200, windowHeight/2 - 100));
        ImGui::SetWindowSize("MENU", ImVec2(400 , 300));
        ImGui::CaptureMouseFromApp(true);
        ImGui::SetWindowFontScale(1.0f);
        
          ImGui::SetCursorPos(ImVec2(150, 10));
          ImGui::Text("Menu Screen", ImVec2(100, 50));
        
          //ImGui::SetCursorPos(ImVec2(50, 50));
          //ImGui::Text("Background Music", ImVec2(100, 50));

          ImGui::SliderFloat("Background Music", &main_menu_volume, 0.0f, 1.0f); 
          ImGui::Checkbox("Fullscreen", &_data->gs.fullScreen);
          ImGui::Checkbox("Window Mode", &_data->gs.windowMode);
          
          //ImGui::SetCursorPos(ImVec2(50, 150));
          //ImGui::Text("Sound FX", ImVec2(100, 50));


        static bool exit_menu;
        ImGui::SetCursorPos(ImVec2(150, 230));
        exit_menu = ImGui::Button("EXIT MENU", ImVec2(100, 50));
        if(exit_menu)
            menu_screen = false;
        ImGui::End();
    }


    if(_data->gs.searching_for_connection)
    {
        ImGui::Begin("Network", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
        ImGui::SetWindowPos("Network", ImVec2(windowWidth/2 - 200, windowHeight/2 - 100));
        //ImGui::SetWindowSize("Network", ImVec2(windowWidth - 200 , windowHeight - 200));
        ImGui::SetWindowSize("Network", ImVec2(400 , 200));
        ImGui::CaptureMouseFromApp(false);
          ImGui::SetWindowFontScale(1.0f);
          ImGui::SetCursorPos(ImVec2(150, 100));
          ImGui::Text("Listening for Conection...", ImVec2(100, 50));
        ImGui::End();
    }

	  ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGui::EndFrame();












    
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
      square_shader->SetFloat("alpha", fade);
	  square_render->drawSquare();

}
