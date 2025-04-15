#include <iostream>
#include <string>
#include <vector>
#include "../../../filesystem/FileSystem.h"
#include "../../../cmdunit/CMDunit.h"
#include "../../../shell/Shell.h" 

    class CDcommand : public Command // inheritance
    {
    public:
        CDcommand()
		: Command{ "cd", 1, "Changes current directory." }
	{
		CommandRegistry::registerCommand("cd", this);
	}
        int operate(Shell& shell, std::vector<std::string> cmd_args) {
        	if (cmd_args.size() != 1)
		{
			std::cout << "Bar argument(s)." << std::endl;
			return -1;
		}

		std::string path=cmd_args.front();
		FileSystemObject* ch_dir = objectLocator(shell.getRootDir(), shell.getCurrentDir(), path);

        	if (!ch_dir) {
			return -1; 
		}
		shell.changeCurrentDir(static_cast<DirectoryObject*>(ch_dir));
		return 0;
	}
    };


static CDcommand cdCommandInstance;
