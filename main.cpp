#pragma comment(lib, "hv.lib")

#include <iostream>
#include <string>
#include "include/hv/json.hpp"
#include "include/hv/WebSocketClient.h"

hv::WebSocketClient wsclient;

void OnMessage(const std::string &msg)
{
		if(msg[0] == '$')
		{
			std::string temp;
			for ( int i = msg.find(' ') + 1; i < msg.length(); i++ )
				temp += msg [i];
			wsclient.send(temp);
		}
		else
		{
			nlohmann::json omMsg = nlohmann::json::parse(msg);
			
		}
}

void OnOpen()
{
	
}

int main(int argc, char** argv)
{
	// WebSocket Client Set
	reconn_setting_t reconn;
	reconn_setting_init(&reconn);
	reconn.min_delay = 1000;
	reconn.max_delay = 10000;
	reconn.delay_policy = 2;

	wsclient.onmessage = OnMessage;
	wsclient.onopen = OnOpen;
	wsclient.onclose = [ ] ()
		{
			std::cout << "OnClose!";
			exit(0);
		};

	// Port Input
	if (argc == 0 )
	{
		std::string port;
		int iport = 0;
		std::cout << "Please Input Server Port" << std::endl;
		std::cin >> port;
		for (int i = 0; i < port.size(); i++ )
		{
			if (!isdigit(port.at(i)) )
			{
				std::cout << "Port at " << std::to_string(i) << " is not digit!" << std::endl;
				exit(0);
			}
		}
		std::istringstream iss(port);
		iss >> iport;
		if (iport >= 0 && iport <= 65535)
			wsclient.open(( "ws://127.0.0.1:" + std::to_string(iport) + "/" ).c_str());
		else
		{
			std::cout << "Port not good!" << std::endl;
			exit(0);
		}
	}
	else
	{
		if (argv[1] == "-url")
			wsclient.open(argv[2]);
		else
		{
			std::cout << "Command Error!" << std::endl;
			exit(0);
		}
	}

	// Not Exit
	while ( true );

	return 0;
}
