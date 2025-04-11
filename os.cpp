#include "./filesystem/FileSystem.h"
#include "./shell/Shell.h"
#include "os.h"
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <thread> // chrono and this are used for waiting

OS::OS()
{
	filesystem = new FileSystem{};
	shell = new Shell(filesystem);
}

OS::~OS()
{
	delete filesystem;
	delete shell;
}


int OS::start()
{
	// Print Fancy OS messages
	std::vector<std::string> initMsgs {
		"Initiating OS...",
		"Initiating Filesystem...",
		"Initiating Shell...",
		"**Success**",
		"Welcome to simulOS!",
		"Entering the simulsh..."
	};

	for (std::string msg: initMsgs)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		std::cout << msg << std::endl;
	}
	std::cout << std::endl;

	// Start shell session
	int signal = shell->startSession(); // store the response
	if (signal == -2) { stop(); } // -2 signal is shutdown signal
	return (signal == -2) ? 0:1;
}


int OS::stop()
{
	// Print a fancy OS shutdown message
	std::cout << std::endl;
	std::cout << "Shutting the system down...\n" << "Bye..." << std::endl;
	return 0;
}

