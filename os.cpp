#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread> // chrono and this are used for waiting
#include "./filesystem/FileSystem.h"
#include "./shell/Shell.h"
#include <vector>
#include "os.h"

OS::OS()
{
	fsystem = new FileSystem{};
	shell = new Shell(fsystem);
}

OS::~OS()
{
	delete shell;
	delete fsystem;
	/*
	 * Interesting case: if we do the above in the reverse order,
	 * it is very dangerous.
	 * Shell has dependence on fsystem and history -- a FileSystemObject.
	 * In my case, I tried to delete history on Shell's destructor
	 * which resulted in root_dir having 1 child in ChildObjects pointing to deleted memory.
	 * Also, as I observed, deleting a childObject from Parent dir was not done
	 * in ~DirectoryObject constructorin. But this may work automatical.
	*/
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
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		std::cout << msg << std::endl;
	}
	std::cout << std::endl;

	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	// Start shell session
	int signal = shell->startSession(); // store the response
	stop();
	return signal;
}


int OS::stop()
{
	// Print a fancy OS shutdown message
	std::cout << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(20));
	std::cout << "Shutting the system down..." << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(20));
	std::cout << "Bye..." <<std::endl;
	return -2;
}
