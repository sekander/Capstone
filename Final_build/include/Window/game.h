#pragma once

#include <memory>
#include <iostream>
#include <cstdint>
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


#include "../GameData/GameData.h"

//States 
#include "../States/splash_state.h"
#include "../States/main_menu_state.h"
#include "../States/game_play_state.h"
#include "../States/game_over_state.h"
#include "../States/loading_play_state.h"


#include "../Actors/Actor.h"

//#define PORT		5500
//#define TEST_PORT	5501
//#define PORT	5500
//#define MAXLINE 50
//#define MAXLINE 1024




class Game {

	public:
		Game();
		~Game();

		void Initialize();

		GLFWwindow* create_openGL_window(int opengl_major_ver, 
					 	 int opengl_minor_ver, 
					 	 const char* win_title, 
					 	 int screen_width, 
					 	 int screen_height);


		void Run();
		void NetworkUpdate();
		void SoundUpdate();
    void Update();
		void Render();                                                                                  


		void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		void processInput(GLFWwindow *window);
		void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);   
		void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	
		void error_callback( int error, const char* description );
		static void key_callback( GLFWwindow* window, int key, int scancode, int action, int mods );

		
	
	private:
		// settings
		const double fpsLimit = 1.0 / 60.0;
		double lastRenderTime = 0;  // number of seconds since the last loop
		double lastUpdateTime = 0;  // number of seconds since the last loop
		double lastFrameTime = 0;   // number of seconds since the last frame
		unsigned int renderFrames = 0;

		const unsigned int SCR_WIDTH = 800;
		const unsigned int SCR_HEIGHT = 600;


		bool update_flag 	= false;
		bool keepLooping 	= true;
		bool process_Input_flag = false;
		std::mutex g_Mutex;

		GameData *_data;
		const char *test;
		//Actor *networkActor;
		std::shared_ptr<Actor> networkActor;
    	GLFWmonitor* monitor;
    	const GLFWvidmode* mode;

};

