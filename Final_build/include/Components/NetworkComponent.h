#pragma once

#include "Component.h"
//Network includes
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>

//JSON libaries
#include "../rapidjson/document.h"
#include "../rapidjson/writer.h"

#include "../GameData/GameData.h"


//#define PORT		5500
#define PORT		2222
#define TEST_PORT	5500
#define MAXLINE 1024


class NetworkComponent : public Component
{
private: 
	int _sockfd;
	int _test_sockfd;
	char buffer[MAXLINE];
	const char *hello;
	struct sockaddr_in servaddr, cliaddr;
	struct sockaddr_in test_servaddr, test_cliaddr;
	socklen_t len;
	int n;
	bool server_listening;

	void parseJSON(GameData* _data, const char* json);

public:
	NetworkComponent(Component* parent_);	
	~NetworkComponent();
		bool onCreate();
	void onDestroy();
	void update(const float deltat );
	void net_update(GameData *_data);
	void draw() const;

	

	void initUDPSocket(int &sockfd, 
										struct sockaddr_in &servaddr, 
										struct sockaddr_in &cliaddr, 
										uint16_t port);
	
	void recieve_send(GameData *_data,  
										socklen_t &len, 
										int &n, 
										struct sockaddr_in &cliaddr, 
										int &test_sockfd, 
										int &sockfd, 
										char buffer[MAXLINE]);
	
	
	void power_off_socket(int &sock_);
	//void power_off_socket();
	
};
