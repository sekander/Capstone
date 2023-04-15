#include "../../include/Window/game.h"
#include <GLFW/glfw3.h>
#include <future>
#include <memory>
#include <thread>
#include "../../include/Components/NetworkComponent.h"
#include "../../include/GameData/ObjectCounter.h"


/////////////////////////////////////////////////////////////////////////////
///------------------------------IMGUI--------------------------------------
#include "../../include/IMGUI/imgui.h"
#include "../../include/IMGUI/imgui_impl_glfw.h"
#include "../../include/IMGUI/imgui_impl_opengl3.h" 

using namespace std::chrono_literals;
using namespace std;







Game::Game(){
    


  	_data = new GameData();
	  _data->machine =  new StateMachine();
    _data->o_cam =  new Orthographic_camera(0.0f, static_cast<float>(SCR_WIDTH), static_cast<float>(SCR_HEIGHT), 0.0f, -1.0f, 100.0f);

    //networkActor = new Actor(nullptr);
    networkActor = std::make_shared<Actor>(nullptr);
}
Game::~Game(){
  cout << "Deleting GAME !!!!!!!" << endl;

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  networkActor->GetComponent<NetworkComponent>()->onDestroy();
  networkActor = nullptr;
  //delete networkActor;
}

void Game::Initialize()
{

	  _data->window = create_openGL_window(3, 3, "Nahid Window", SCR_WIDTH, SCR_HEIGHT);
//	  _data->machine->AddState(St(new MainMenuState(*_data)), false);	
//	  _data->machine->AddState(St(new GameOverState(*_data)), false);	
	  _data->machine->AddState(St(new SplashState(*_data)), false);	
//	  _data->machine->AddState(St(new LoadingPlayState(*_data)), false);	
	  _data->state_switch = CURRENT;
	  _data->level = LEVEL_1;
	  _data->gs.server_on = false;
	  _data->gs.connection_established = false;
	  _data->gs.searching_for_connection = false;
    _data->gs.start_game = false; 
    _data->gs.fullScreen = false;
    _data->gs.windowMode = false;
   
   // networkActor->AddComponent<NetworkComponent>(nullptr);
    _data->o_cam->SetScale(glm::vec3(1.0f, 1.0f, 0.0f));
	  update_flag = false;
	  _data->machine->GetActiveState()->Init();
    std::cout << "Done Initializing ... "  << std::endl;
	  update_flag 	   = true;


    networkActor->AddComponent<NetworkComponent>(nullptr);
    networkActor->GetComponent<NetworkComponent>()->onCreate();
    
}


void Game::Run()
{
 // std::thread t([this]( ) {
  std::future<void> iotaFuture = std::async(std::launch::async,
  [this](){
    SoundUpdate();
  });
 
  //std::thread t1([this]( ) {
  std::future<void> iotaFuture2 = std::async(std::launch::async,
  [this](){
    Update();
  });

  iotaFuture.get();
  iotaFuture2.get();
  //t.join();
  //t1.join();

  Render();
}

void Game::NetworkUpdate()
{
    networkActor->GetComponent<NetworkComponent>()->net_update(_data);
}



void Game::SoundUpdate()
{
    std::cout << "Begin Audio Loop" << std::endl;
 //   std::future<void> iotaFuture = std::async(std::launch::async,
 //   [this](){
    //std::thread t([this]( ) {
    


        while(keepLooping)
      {
        if(update_flag)
        {
          //std::lock_guard<std::mutex> mtx(g_Mutex);
          _data->machine->GetActiveState()->SoundUpdate();
        }  
      }
   

 //   });


    //iotaFuture.get();
    //t.join();


}

void Game::Update()
{
    std::cout << "Begin Update Loop" << std::endl;
  
            clock_t start, end;
	          start = clock();
	          unsigned int updateFrame = 0;
 
              //write_to_json();
              std::this_thread::sleep_for(50ms);
              while(keepLooping )
              {
                double now = glfwGetTime();
                double deltaTime = now - lastUpdateTime;

                processInput( _data->window);
                
                if(update_flag)
                {	
                  std::lock_guard<std::mutex> mtx(g_Mutex);

                  // This if-statement only executes once every 60th of a second
                      if ((now - lastFrameTime) >= fpsLimit)
                      {
                      _data->machine->GetActiveState()->Input(0.0f);
                      _data->machine->GetActiveState()->Update(0.0f);
                          
                        updateFrame++;
                    // only set lastFrameTime when you actually draw something
                        lastFrameTime = now;
                  }	
                  // set lastUpdateTime every iteration
                      lastUpdateTime = now;
                }
              }
               
              end = clock();
              double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
              std::cout << "UPDATE THREAD : Time taken by program is :" << std::fixed
                  << time_taken << std::setprecision(5);
              std::cout << " sec" <<std::endl;
              //std::cout << "UPDATE THREAD : Frames per sec " << updateFrame/time_taken << std::endl;
              std::cout << "UPDATE THREAD : Frames per sec " << updateFrame/glfwGetTime() << std::endl;
              //_data->gs.server_listening = false;
              //_data->gs.server_on = false;

}

void Game::Render()
{
    std::cout << "Begin Render Loop" << std::endl;
	  clock_t start, end;
	  start = clock();
    // render loop
    // -----------
    std::cout << "Beginning Render Loop" << std::endl;
    while (!glfwWindowShouldClose(_data->window))
    {
        double now = glfwGetTime();
        double deltaTime = now - lastRenderTime;

		// This if-statement only executes once every 60th of a second
        if ((now - lastFrameTime) >= fpsLimit)
        {
        	if(_data->state_switch == 0)
        	{
            update_flag = false;
    			  std::this_thread::sleep_for(50ms);
        		_data->machine->GetActiveState()->DeleteData();
        		_data->machine->AddState(St(new SplashState(*_data)), true);
        		_data->machine->ProcessState();
        		_data->machine->GetActiveState()->Init();
            	update_flag = true;
				_data->state_switch = CURRENT;
        	}
        	if(_data->state_switch == 1)
        	{
            update_flag = false;
    			  std::this_thread::sleep_for(50ms);
         		_data->machine->GetActiveState()->DeleteData();
         		_data->machine->AddState(St(new MainMenuState(*_data)), true);
         		_data->machine->ProcessState();
        		_data->machine->GetActiveState()->Init();
            update_flag = true;
				_data->state_switch = CURRENT;
        	}
        	if(_data->state_switch == 2)
        	{
            update_flag = false;
    			  std::this_thread::sleep_for(50ms);
        		_data->machine->GetActiveState()->DeleteData();
        		_data->machine->AddState(St(new LoadingPlayState(*_data)), true);
        		_data->machine->ProcessState();
        		_data->machine->GetActiveState()->Init();
            update_flag = true;
				_data->state_switch = CURRENT;
        	}
        	if(_data->state_switch == 3)
        	{
            update_flag = false;
    			  std::this_thread::sleep_for(50ms);
        		_data->machine->GetActiveState()->DeleteData();
        		_data->machine->AddState(St(new GamePlayState(*_data)), true);
        		_data->machine->ProcessState();
        		_data->machine->GetActiveState()->Init();
            update_flag = true;
				_data->state_switch = CURRENT;
        	}
        	if(_data->state_switch == 4)
        	{
            update_flag = false;
    			  std::this_thread::sleep_for(50ms);
        		_data->machine->GetActiveState()->DeleteData();
        		_data->machine->AddState(St(new GameOverState(*_data)), true);
        		_data->machine->ProcessState();
        		_data->machine->GetActiveState()->Init();
            update_flag = true;
				_data->state_switch = CURRENT;
        	}

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
			  _data->machine->GetActiveState()->Render(0.0f);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(_data->window);
        glfwPollEvents();
		// only set lastFrameTime when you actually draw something
        lastFrameTime = now;
        renderFrames++;
		}
		// set lastUpdateTime every iteration
        lastRenderTime = now;

        //	glfwSetWindowShouldClose(_data->window, true);
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------


    update_flag = false;
    keepLooping = false;
	

    std::this_thread::sleep_for(50ms);

		_data->gs.connection_established = false;
    delete _data->o_cam;
    _data->machine->GetActiveState()->DeleteData();
    //_data->gs.connection_established = false;

    _data->machine->Clear();
    delete _data->machine;
    delete _data; 

    glfwTerminate();

    end = clock();
	  double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	  std::cout << "Time taken by program is :" << std::fixed
		  << time_taken << std::setprecision(5);
	  std::cout << " sec" <<std::endl;

	  //std::cout << "Frames per sec " << renderFrames/time_taken << std::endl;
	  std::cout << "Frames per sec " << renderFrames/glfwGetTime() << std::endl;
		//server_listening = false;
    _data->gs.server_listening = false;
}

//error handling function
void error_callback( int error, const char* description )
{
    fprintf( stderr, "Error: %s\n", description );
}

void key_callback( GLFWwindow* window, int key, int scancode, int action, int mods )
{
    if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
    {
        glfwSetWindowShouldClose( window, GLFW_TRUE );
    }
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void Game::processInput(GLFWwindow *window)
{
		{	
			//if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || _data->pd.touchPad_4 == 1)
			if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS )
		        glfwSetWindowShouldClose(window, true);
		  
   	    	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
			{
				_data->state_switch = SPLASH_STATE;
		  	}
		    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
			{
				_data->state_switch = MAIN_MENU_STATE;
			}
		    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
			{
				_data->state_switch = LOADING_PLAY_STATE;
			}
        /*
		    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
			  {
				  _data->state_switch = PLAY_STATE;
			  }
        */

			if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
			  {
				  _data->state_switch = GAME_OVER_STATE;
			  }

			  if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
			  {
				  _data->machine->GetActiveState()->DeleteData();
			  }




			if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS || _data->gs.fullScreen )
			//if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
      {
        _data->gs.windowMode = false;
        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        _data->gs.fullScreen = false;
      }
      else if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS || _data->gs.windowMode)
      //if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
      {
        _data->gs.fullScreen = false;
        glfwSetWindowMonitor(window, NULL, 0, 0, SCR_WIDTH, SCR_HEIGHT, 0);
        _data->gs.windowMode = false;

      }



		}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}



// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void Game::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void Game::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
}

//Intialize all opengl glad and glfw 
GLFWwindow* Game::create_openGL_window(int opengl_major_ver, int opengl_minor_ver, const char* win_title, int screen_width, int screen_height)
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, opengl_major_ver);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, opengl_minor_ver);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // glfw window creation
    // --------------------

    GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, win_title, NULL, NULL);
    //GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, win_title, glfwGetPrimaryMonitor(),NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
//        return -1;
        //glfwSetWindowShouldClose(window, true);

    }
    monitor = glfwGetPrimaryMonitor();
    //monitor = glfwGetWindowMonitor(window);
    mode = glfwGetVideoMode(monitor);

    //glfwSetWindowMonitor(window, NULL, 0, 0, SCR_WIDTH, SCR_HEIGHT, 0);





    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
        //glfwSetWindowShouldClose(window, true);

    }

    return window;

}



