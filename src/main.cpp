/*********************************************************************************
*                             Author: Nahid Sekander                             *
*       File Name: /home/fnky/C0de/new_multi_component_engine/src/main.cpp       *
*                   Creation Date: September 29, 2022 10:38 PM                   *
*                   Last Updated: September 30, 2022 01:30 AM                    *
*                              Source Language: cpp                              *
*                                                                                *
*                            --- Code Description ---                            *
*                                  main source                                   *
*********************************************************************************/

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
#include <future>

#include <bits/stdc++.h>
#include <cstddef>
#include <ctime>

#include <fstream>




#include "../include/GameData/GameData.h"

//States 
#include "../include/States/splash_state.h"
#include "../include/States/main_menu_state.h"
#include "../include/States/game_play_state.h"
#include "../include/States/game_over_state.h"
#include "../include/States/loading_play_state.h"

//Network includes
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

//JSON libaries
#include "../include/rapidjson/document.h"
#include "../include/rapidjson/writer.h"
#include "../include/rapidjson/ostreamwrapper.h"



const double fpsLimit = 1.0 / 60.0;
double lastRenderTime = 0;  // number of seconds since the last loop
double lastUpdateTime = 0;  // number of seconds since the last loop
double lastFrameTime = 0;   // number of seconds since the last frame
unsigned int renderFrames = 0;


//
GLFWwindow* create_openGL_window(int opengl_major_ver, int opengl_minor_ver, const char* win_title, int screen_width, int screen_height);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

//
void Initialize();
void Update(GLFWwindow* window);


//Networking
void create_socket(int &server, struct sockaddr_in &a, int &new_socket, int PORT);
void * read_socket(int &new_socket, char *buffer, const char *message);
void power_off_socket();

//Networking Attributes
int server_fd, new_socket, valread;
struct sockaddr_in address;
int opt = 1;
int addrlen = sizeof(address);
char buffer[1024] = { 0 };
bool socket_recv = false;


//Creating JSON File
void write_to_json();

//JSON Attributes
rapidjson::StringBuffer w;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


bool update_flag 	= false;
bool keepLooping 	= true;
bool process_Input_flag = false;
std::mutex g_Mutex;




using namespace std::chrono_literals;
using namespace std;
GameData *_data;



void main_play_audio()
{
  while(keepLooping)
  {
    if(update_flag)
    {
      std::lock_guard<std::mutex> mtx(g_Mutex);
      _data->machine->GetActiveState()->SoundUpdate();
    }  
  }
}



int main()
{
	clock_t start, end;
	start = clock();

  _data = new GameData();

	_data->machine =  new StateMachine();
	//_data->state_switch = new States;
	_data->window = create_openGL_window(3, 3, "Nahid Window", SCR_WIDTH, SCR_HEIGHT);
//	_data->machine->AddState(St(new SplashState(*_data)), false);	
//	_data->machine->AddState(St(new MainMenuState(*_data)), false);	
	//_data->machine->AddState(St(new GamePlayState(*_data)), false);	
	_data->machine->AddState(St(new LoadingPlayState(*_data)), false);	
	//_data->machine->AddState(St(new GameOverState(*_data)), false);	
	_data->state_switch = CURRENT;
	_data->level = LEVEL_1;
	//_data->level = LEVEL_2;
 


  	Initialize();
	std::cout << "[main] Loading Assets\n";


	
	auto a1 = std::async(std::launch::async, Update, _data->window);
	auto a2 = std::async(std::launch::async, main_play_audio);


	//write_to_json();


	std::cout << "Server Staring ...\n";

	create_socket(server_fd, address, new_socket, 8080);

	//put this on its own thread
	//read_socket(new_socket, buffer, "SERVER: ");
	/*
	std::thread t(&read_socket, std::ref(new_socket), 
				    std::ref(buffer), 
				    std::ref("SERVER::!"));
	*/


	//const char* sock_data = player_data.c_str();
	//const char* sock_data = _data->pd.x_pos_text.c_str();
	//const char* sock_data = _data->pd.y_pos_text.c_str();
	const char* sock_data = _data->pd.player_data.c_str();


	auto a3 = std::async(std::launch::async, read_socket, 
									std::ref(new_socket), std::ref( buffer), 
									//std::ref(c_data));
									//std::ref("Player Position: \n"));
									std::ref(sock_data));

	

	//update_flag 	   = true;
	//process_Input_flag = true;


    // render loop
    // -----------
    std::cout << "Beginning Render Loop" << std::endl;
    while (!glfwWindowShouldClose(_data->window))
    {
        double now = glfwGetTime();
        double deltaTime = now - lastRenderTime;

		std::cout <<"Player Data " << _data->pd.player_data << std::endl;

		//std::cout << "Player Position Test : " << pd_xpos << ", " << pd_ypos << std::endl;


		/*
		//std::cout << "Player P Test: "<< "From Data:" << _data->pd.y_pos <<"\n From main:" << *player_xpos 
		std::cout << "Player P Test: "<<
		"\nString Test: " << _data->pd.x_pos_text << ", " << _data->pd.y_pos_text << std::endl;

		std::cout << "Player Position Test : " << _data->pd.x_pos << ", " 
											   << _data->pd.y_pos << std::endl;
		*/

		//
		//std::cout << "Player Position Test : " << *player_xpos << ", " 
		//									   << *player_ypos << std::endl;
		

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

        //std::cout << "Rendering ..." << std::endl;
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


	power_off_socket();
    std::cout << "Deleting\n";
    update_flag = false;
    keepLooping = false;
	

    std::this_thread::sleep_for(50ms);
    _data->machine->GetActiveState()->DeleteData();

    delete _data->o_cam;
    _data->machine->Clear();
    delete _data->machine;
  //  delete _data->ld;
    //delete _data->world;
    delete _data; 

    glfwTerminate();

    end = clock();
	  double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	  std::cout << "Time taken by program is :" << std::fixed
		  << time_taken << std::setprecision(5);
	  std::cout << " sec" <<std::endl;

	  //std::cout << "Frames per sec " << renderFrames/time_taken << std::endl;
	  std::cout << "Frames per sec " << renderFrames/glfwGetTime() << std::endl;

    return 0;
}


void Initialize()
{
    _data->o_cam =  new Orthographic_camera(0.0f, static_cast<float>(SCR_WIDTH), static_cast<float>(SCR_HEIGHT), 0.0f, -1.0f, 100.0f);
    _data->o_cam->SetScale(glm::vec3(1.0f, 1.0f, 0.0f));
//	  _data->ld = new LoadingGameObjects();
     //   _data->o_cam->SetPosition(glm::vec3(x_cam, y_cam, z_cam));
    //-----------------------Resource Loading-------------------------------


    //    thrid_sprite_render->LoadSprite("assets/venom.png", vec2(100, 100), vec2(100, 100));
    /////======================================================================
	update_flag = false;
	_data->machine->GetActiveState()->Init();
    std::cout << "Done Initializing ... "  << std::endl;
	update_flag 	   = true;
    //LoadAssets();
}


void Update(GLFWwindow *window)
{
	clock_t start, end;
	start = clock();
	unsigned int updateFrame = 0;
 
    std::this_thread::sleep_for(50ms);
	while(keepLooping)
	{
        double now = glfwGetTime();
        double deltaTime = now - lastUpdateTime;

		processInput(window);
		
		if(update_flag)
		{	
			std::lock_guard<std::mutex> mtx(g_Mutex);

			// This if-statement only executes once every 60th of a second
        	if ((now - lastFrameTime) >= fpsLimit)
        	{
    			_data->machine->GetActiveState()->Input(0.0f);
    			_data->machine->GetActiveState()->Update(0.0f);
				      
				write_to_json();
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
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	//bool keepLooping = true;

	//std::cout << "Beginning Input Loop" << std::endl;
	//	if(process_Input_flag)
		{	
		    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
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



		    //std::this_thread::sleep_for(10ms);
			//std::cout << "Input..." << std::endl;
		}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


//Intialize all opengl glad and glfw
GLFWwindow* create_openGL_window(int opengl_major_ver, int opengl_minor_ver, const char* win_title, int screen_width, int screen_height)
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
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwSetWindowPos(window, 0, 0);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;

    }

	  glfwSwapInterval(1);
	  //Disable v-sync
      //glfwSwapInterval(0);

    return window;
}

void power_off_socket(){

	std::cout << "Connection CLosing!\n";	
	// closing the connected socket
	close(new_socket);
	// closing the listening socket
	shutdown(server_fd, SHUT_RDWR);

}

void * read_socket(int &new_socket, char *buffer, const char *message)
{
	//while(true){
		std::cout << "Listening...\n";
		if ((new_socket = accept(server_fd, (struct sockaddr*)&address,
					(socklen_t*)&addrlen))
			< 0) {
					perror("accept");
					exit(EXIT_FAILURE);
				}	

		valread = read(new_socket, buffer, 1024);
			
		socket_recv = true;
		
		auto client_ip = ( address.sin_addr.s_addr);
		auto client_port = ntohs(address.sin_port);


		if(socket_recv)
		{
			std::cout << "Connection Found!!!\n";	
			//std::cout << "From : " << client_ip;
			printf("%d.%d.%d.%d\n",
  			int(address.sin_addr.s_addr&0xFF),
  			int((address.sin_addr.s_addr&0xFF00)>>8),
  			int((address.sin_addr.s_addr&0xFF0000)>>16),
  			int((address.sin_addr.s_addr&0xFF000000)>>24));
			printf("Port : %d\n", client_port);

			while(true){
				
    			std::this_thread::sleep_for(100ms);
				

				std::cout << "Client Message: " << buffer << std::endl;

				//send(new_socket, "Component Engine: \n", strlen("Component Engine: \n"), 0);
				send(new_socket, message, strlen(message), 0);
			}
			socket_recv = false;

		}

	//}
}

void create_socket(int &server_fd, 
		   struct sockaddr_in &address, 
		   int &new_socket,
		   int PORT)
{
	std::cout << "Searching For Connection ...\n";
	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET,
				SO_REUSEADDR | SO_REUSEPORT, &opt,
				sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr*)&address,
			sizeof(address))
			< 0) {
				perror("bind failed");
				exit(EXIT_FAILURE);
			}

	if (listen(server_fd, 3) < 0) {
				perror("listen");
				exit(EXIT_FAILURE);
			}
}

void write_to_json(){
	rapidjson::Writer<rapidjson::StringBuffer> writer(w);
	writer.StartObject();
	writer.Key("xpos");
    writer.Int(_data->pd.x_pos);
    //writer.String(_data->pd.x_pos_text.c_str());
    writer.Key("ypos");
    writer.Int(_data->pd.y_pos);
    //writer.String(_data->pd.y_pos_text.c_str());
    writer.EndObject();

    const char *test = w.GetString();
    ofstream myFile("player.json");

    myFile << test;


}
