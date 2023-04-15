#include <iostream>
#include <thread>
#include "../../include/Components/Component.h"
#include "../../include/Components/NetworkComponent.h"
	
static int parseFailed = 0;

using std::cout;
NetworkComponent::NetworkComponent(Component* parent_)
: Component(parent_)
{
}

NetworkComponent::~NetworkComponent(){
	cout << "Netwrok Component Removed\n";
}

bool NetworkComponent::onCreate(){

	initUDPSocket(_test_sockfd, servaddr, cliaddr, TEST_PORT);

	return true;
}

void NetworkComponent::onDestroy(){
	//power_off_socket(_sockfd);
}

void NetworkComponent::update(const float delta)
{
	std::cout << "Hello from Transform " << delta << std::endl;
}

void NetworkComponent::net_update(GameData *_data)
{
	


	//std::cout << "Hello from Transform " << delta << std::endl;
	recieve_send(_data, len, n, cliaddr, _test_sockfd, _sockfd, buffer);
}


void NetworkComponent::draw()const {}

//UDP
//###############################################################################################################################

void NetworkComponent::power_off_socket(int &sock_)
{
	std::cout << "Closing Connection" << std::endl;

	shutdown(sock_, SHUT_RDWR);
	//close(sockfd);


}


//void initUDPSocket(int &sockfd, struct sockaddr_in &servaddr, struct sockaddr_in &cliaddr){
void NetworkComponent::initUDPSocket(int &sockfd, struct sockaddr_in &servaddr, struct sockaddr_in &cliaddr, uint16_t port){

	std::cout << "Initalizing UDP Server..." << std::endl;
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	//servaddr.sin_port = htons(PORT);
	servaddr.sin_port = htons(port);
	
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	server_listening = true;
}


void NetworkComponent::recieve_send( GameData *_data, socklen_t &len, int &n, struct sockaddr_in &cliaddr, int &test_sockfd, int &sockfd,  char buffer[MAXLINE]){
//void recieve_send( socklen_t &len, int &n, struct sockaddr_in &cliaddr, int &sockfd,  char buffer[MAXLINE]){



		int i = 0;
		std::cout << "Sever is offline" << std::endl;
		_data->gs.server_listening = server_listening;

		//Need to pull this bool
		//while(server_listening)
		while(_data->gs.server_listening)
		{
		//while(!_data->gs.exit_app){
		//while(true){


			if(_data->gs.server_on)
			//if(_data->gs.server_on)
			{
				std::cout << "Sever is online " << std::endl;
				_data->gs.sending_test_packet = true;
				//if(!server_listening)
				//	break;
					
				//std::cout << "Server is Listening..." << std::endl;
				//Might need to adjust value
				//std::this_thread::sleep_for(50ms);
				//std::this_thread::sleep_for(100ms);

				i++;

				len = sizeof(cliaddr); //len is value/result
				std::cout << "Listening..." << std::endl;


				_data->gs.searching_for_connection = true;
				if(_data->gs.connection_established)
					_data->gs.sending_test_packet = false;

				//Sockel time out must have
				struct timeval tv;
				tv.tv_sec = 0;
				tv.tv_usec = 100;
				
				if(!_data->gs.connection_established  )
				{

					if (setsockopt(test_sockfd, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) {
					//if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) {
						perror("Error");
						//if(!server_listening)
						//	break;
						_data->gs.connection_established = false;
						std::cout << "socket reset" << std::endl;


					}
				}

				if(_data->gs.sending_test_packet)
				{
				//Send out a test packet to determine if connection is available
				    if(_data->gs.searching_for_connection && !_data->gs.connection_established)
				    {
				    	std::cout << "Searching For Connection...";
				    	//n = recvfrom(sockfd, (char *)buffer, MAXLINE,
				    	n = recvfrom(test_sockfd, (char *)buffer, MAXLINE,
				    			MSG_WAITALL, ( struct sockaddr *) &cliaddr,&len);
				    	buffer[n] = '\0';

				    	const char* sendToClient = "Connected to Server";


				    	//sendto(sockfd, (const char *)sendToClient, strlen(sendToClient),
				    	sendto(test_sockfd, (const char *)sendToClient, strlen(sendToClient),
				    		MSG_CONFIRM, (const struct sockaddr *) &cliaddr,len);


				    	if ((buffer != NULL) && (buffer[0] == '\0')) {
				    		printf("buffer is empty\n");
				    	}
				    	else{
				    		//std::cout << buffer << std::endl;
								std::cout << "Connection found!!" << std::endl;

				    		_data->gs.connection_established = true;
				    		_data->gs.searching_for_connection = false;

				    		//server_listening = false;
								_data->gs.server_listening = false;
				    	}
				    
						}
				}
			}
		}

		power_off_socket(test_sockfd);

		initUDPSocket(sockfd, servaddr, cliaddr, PORT);
		std::cout << "Data Ready to transmit with client" << std::endl;
		//_data->state_switch = LOADING_PLAY_STATE;


		while(_data->gs.connection_established)
		{
			if(_data->gs.start_game)
			{
					//std::cout << "Data Transmitting" << std::endl;

					_data->gs.sending_test_packet = false;
					//Connection is established loop here
					//if(_data->gs.connection_established){}
					n = recvfrom(sockfd, (char *)buffer, MAXLINE,
							MSG_WAITALL, ( struct sockaddr *) &cliaddr,&len);
					buffer[n] = '\0';
					//std::cout << "Connection Established..." << std::endl;

					//add universal bool

					//if(std::string(buffer) == "Exit")
					//	_data->gs.connection_established = false;


					printf("Client : %s\n", buffer);

					auto client_port = ntohs(cliaddr.sin_port);
					
					printf("%d.%d.%d.%d\n",
					int(cliaddr.sin_addr.s_addr&0xFF),
					int((cliaddr.sin_addr.s_addr&0xFF00)>>8),
					int((cliaddr.sin_addr.s_addr&0xFF0000)>>16),
					int((cliaddr.sin_addr.s_addr&0xFF000000)>>24));
					//printf("Port : %d\n", client_port);

					parseJSON(_data, buffer);
					if(parseFailed > 10000)
						_data->gs.connection_established = false;


					//Check for client close flag


					std::string json = "{\"xpos\":" + std::to_string(_data->pd.x_pos) +
								       ",\"ypos\":" + std::to_string(_data->pd.y_pos) + 
								       ",\"health\":" + std::to_string(_data->pd.playerHealth) + 
								       ",\"med\":" + std::to_string(_data->pd.totalMedkit) + 
								       ",\"emg\":" + std::to_string(_data->pd.totalEmergencykit) + 
								       ",\"ant\":" + std::to_string(_data->pd.totalAntidotes) + 
								       ",\"arm\":" + std::to_string(_data->pd.playerArmor) + 
								       ",\"add\":" + std::to_string(_data->pd.totalAddrenaline) + 
								       ",\"trp\":" + std::to_string(_data->pd.totalTraps) + 
								       ",\"rep\":" + std::to_string(_data->pd.totalRepairKit) + 
								       ",\"frt\":" + std::to_string(_data->pd.totalFortify) + 
									   
									   
									   
									   
									   "}" + '\0';

					const char* hello = json.c_str();


					sendto(sockfd, (const char *)hello, strlen(hello),
						MSG_CONFIRM, (const struct sockaddr *) &cliaddr,len);
					//std::cout<<"Hello message sent."<<std::endl;
			}





			

	}

	std::cout << "Server is closed!!!" << std::endl;

	power_off_socket(_sockfd);




















	
}

//###############################################################################################################################



void NetworkComponent::parseJSON(GameData *_data, const char* json){

	// Parse the JSON document
	rapidjson::Document doc;
	doc.Parse(json);

	// Check if the document is valid
	if (doc.HasParseError()) {
		std::cerr << "Error: failed to parse JSON document"
				<< std::endl;
		parseFailed += 1;
		//_data->gs.connection_established = false;
		return;
	}

	//_data->gs.start_game = true;
	//Maybe could remove
	//_data->gs.connection_established = true;
	//_data->gs.searching_for_connection = false;

	// Get the "name" member
	//if (doc.HasMember("touchX") && doc["touchX"].IsInt()) {
	if (doc.HasMember("touchX") && doc["touchX"].IsString()) {
		//std::string name = std::to_string( doc["touchX"].GetInt());
		std::string touchX = doc["touchX"].GetString();
		//std::cout << "Touch X: " << touchX << std::endl;
	}
	
	if (doc.HasMember("DpadL") && doc["DpadL"].IsString()) {
		//std::string name = std::to_string( doc["touchX"].GetInt());
		std::string dpadL = doc["DpadL"].GetString();
		//std::cout << "Dpad Left: " << dpadL << std::endl;

		_data->pd.dpadL = stoi(dpadL);
	}
	
	if (doc.HasMember("DpadR") && doc["DpadR"].IsString()) {
		//std::string name = std::to_string( doc["touchX"].GetInt());
		std::string dpadR = doc["DpadR"].GetString();
		//std::cout << "Dpad Right: " << dpadR << std::endl;

		_data->pd.dpadR = stoi(dpadR);
	}
	
	if (doc.HasMember("DpadU") && doc["DpadU"].IsString()) {
		//std::string name = std::to_string( doc["touchX"].GetInt());
		std::string dpadU = doc["DpadU"].GetString();
		//std::cout << "Dpad Up: " << dpadU << std::endl;

		_data->pd.dpadU = stoi(dpadU);
	}

	if (doc.HasMember("DpadD") && doc["DpadD"].IsString()) {
		//std::string name = std::to_string( doc["touchX"].GetInt());
		std::string dpadD = doc["DpadD"].GetString();
		//std::cout << "Dpad Down: " << dpadD << std::endl;

		_data->pd.dpadD = stoi(dpadD);
	}


	if (doc.HasMember("A") && doc["A"].IsString()) {
		//std::string name = std::to_string( doc["touchX"].GetInt());
		std::string A = doc["A"].GetString();
		//std::cout << "A: " << A << std::endl;

		_data->pd.A = stoi(A);
	}
	
	if (doc.HasMember("B") && doc["B"].IsString()) {
		//std::string name = std::to_string( doc["touchX"].GetInt());
		std::string B = doc["B"].GetString();
		//std::cout << "B: " << B << std::endl;

		_data->pd.B = stoi(B);
	}

	if (doc.HasMember("X") && doc["X"].IsString()) {
		//std::string name = std::to_string( doc["touchX"].GetInt());
		std::string X = doc["X"].GetString();
		//std::cout << "X: " << X << std::endl;

		_data->pd.X = stoi(X);
	}

	
	if (doc.HasMember("Y") && doc["Y"].IsString()) {
		//std::string name = std::to_string( doc["touchX"].GetInt());
		std::string Y = doc["Y"].GetString();
		//std::cout << "Y: " << Y << std::endl;

		_data->pd.Y = stoi(Y);
	}

	
	if (doc.HasMember("L") && doc["L"].IsString()) {
		//std::string name = std::to_string( doc["touchX"].GetInt());
		std::string L = doc["L"].GetString();
		//std::cout << "L: " << L << std::endl;

		_data->pd.L = stoi(L);
	}
	
	if (doc.HasMember("L2") && doc["L2"].IsString()) {
		//std::string name = std::to_string( doc["touchX"].GetInt());
		std::string L2 = doc["L2"].GetString();
		//std::cout << "L2: " << L2 << std::endl;

		_data->pd.L2 = stof(L2);
	}



	if (doc.HasMember("R") && doc["R"].IsString()) {
		//std::string name = std::to_string( doc["touchX"].GetInt());
		std::string R = doc["R"].GetString();
		//std::cout << "R: " << R << std::endl;

		_data->pd.R = stoi(R);
	}

	if (doc.HasMember("R2") && doc["R2"].IsString()) {
		//std::string name = std::to_string( doc["touchX"].GetInt());
		std::string R2 = doc["R2"].GetString();
		//std::cout << "R2: " << R2 << std::endl;

		_data->pd.R2 = stof(R2);
	}
	
	if (doc.HasMember("LJOYX") && doc["LJOYX"].IsString()) {
		//std::string name = std::to_string( doc["touchX"].GetInt());
		std::string LJOYX = doc["LJOYX"].GetString();
		//std::cout << "LJOYX: " << LJOYX << std::endl;

		_data->pd.LJOYX = stof(LJOYX);
	}
	
	if (doc.HasMember("LJOYY") && doc["LJOYY"].IsString()) {
		//std::string name = std::to_string( doc["touchX"].GetInt());
		std::string LJOYY = doc["LJOYY"].GetString();
		//std::cout << "LJOYY: " << LJOYY << std::endl;

		_data->pd.LJOYY = stof(LJOYY);
	}

	if (doc.HasMember("RJOYX") && doc["RJOYX"].IsString()) {
		//std::string name = std::to_string( doc["touchX"].GetInt());
		std::string RJOYX = doc["RJOYX"].GetString();
		//std::cout << "RJOYX: " << RJOYX << std::endl;

		_data->pd.RJOYX = stof(RJOYX);
	}
	
	if (doc.HasMember("RJOYY") && doc["RJOYY"].IsString()) {
		//std::string name = std::to_string( doc["touchX"].GetInt());
		std::string RJOYY = doc["RJOYY"].GetString();
		//std::cout << "RJOYY: " << RJOYY << std::endl;

		_data->pd.RJOYY = stof(RJOYY);
	}

	if (doc.HasMember("touchPad_1") && doc["touchPad_1"].IsString()) {
		std::string pad1 = doc["touchPad_1"].GetString();
		_data->pd.touchPad_1 = stof(pad1);
	}
	if (doc.HasMember("touchPad_2") && doc["touchPad_2"].IsString()) {
		std::string pad2 = doc["touchPad_2"].GetString();
		_data->pd.touchPad_2 = stof(pad2);
	}
	if (doc.HasMember("touchPad_3") && doc["touchPad_3"].IsString()) {
		std::string pad3 = doc["touchPad_3"].GetString();
		_data->pd.touchPad_3 = stof(pad3);
	}
	if (doc.HasMember("touchPad_4") && doc["touchPad_4"].IsString()) {
		std::string pad4 = doc["touchPad_4"].GetString();
		_data->pd.touchPad_4 = stof(pad4);
	}
	if (doc.HasMember("touchPad_5") && doc["touchPad_5"].IsString()) {
		std::string pad5 = doc["touchPad_5"].GetString();
		_data->pd.touchPad_5 = stof(pad5);
	}
	if (doc.HasMember("touchPad_6") && doc["touchPad_6"].IsString()) {
		std::string pad6 = doc["touchPad_6"].GetString();
		_data->pd.touchPad_6 = stof(pad6);
	}
	if (doc.HasMember("touchPad_7") && doc["touchPad_7"].IsString()) {
		std::string pad7 = doc["touchPad_7"].GetString();
		_data->pd.touchPad_7 = stof(pad7);
	}
	if (doc.HasMember("touchPad_8") && doc["touchPad_8"].IsString()) {
		std::string pad8 = doc["touchPad_8"].GetString();
		_data->pd.touchPad_8 = stof(pad8);
	}
	if (doc.HasMember("touchPad_9") && doc["touchPad_9"].IsString()) {
		std::string pad9 = doc["touchPad_9"].GetString();
		_data->pd.touchPad_9 = stof(pad9);
	}
	if (doc.HasMember("touchPad_10") && doc["touchPad_10"].IsString()) {
		std::string pad10 = doc["touchPad_10"].GetString();
		_data->pd.touchPad_10 = stof(pad10);
	}
	if (doc.HasMember("touchPad_11") && doc["touchPad_11"].IsString()) {
		std::string pad11 = doc["touchPad_11"].GetString();
		_data->pd.touchPad_11 = stof(pad11);
	}
	if (doc.HasMember("touchPad_12") && doc["touchPad_12"].IsString()) {
		std::string pad12 = doc["touchPad_12"].GetString();
		_data->pd.touchPad_12 = stof(pad12);
	}
	if (doc.HasMember("touchPad_13") && doc["touchPad_13"].IsString()) {
		std::string pad13 = doc["touchPad_13"].GetString();
		_data->pd.touchPad_13 = stof(pad13);
	}


	/*
	if (doc.HasMember("DpadD") && doc["DpadD"].IsString()) {
		//std::string name = std::to_string( doc["touchX"].GetInt());
		std::string name = doc["DpadD"].GetString();
		std::cout << "Name: " << name << std::endl;

		_data->pd.dpadD = stoi(name);
	}
	
	
	if (doc.HasMember("DpadL") && doc["DpadL"].IsString()) {
		//std::string name = std::to_string( doc["touchX"].GetInt());
		std::string name = doc["DpadL"].GetString();
		std::cout << "Name: " << name << std::endl;

		_data->pd.dpadL = stoi(name);
	}
	
	if (doc.HasMember("DpadR") && doc["DpadR"].IsString()) {
		//std::string name = std::to_string( doc["touchX"].GetInt());
		std::string name = doc["DpadR"].GetString();
		std::cout << "Name: " << name << std::endl;

		_data->pd.dpadR = stoi(name);
	}
	*/



}
