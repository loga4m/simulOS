#include <iostream>
#include <string>
#include <vector>
#include "../../../filesystem/FileSystem.h"
#include "../../../cmdunit/CMDunit.h"
#include "../../../shell/Shell.h"


/*
 *   Author: Elshod
 *   Reviewer: Oyatillo Axadjonov: 
 *   		comment -> Kudos for correctly interpreting the core system code!!!
 *
 * */

class TouchCommand : public Command {
public:
    TouchCommand()
	    : Command("touch", 1, "Creates a new file")
    {
    	CommandRegistry::registerCommand("touch", this);
    }

	int operate(Shell& shell, std::vector<std::string> cmd_args) override {
		if (cmd_args.size() != 1) {
			std::cout << "Error: Bad argument." << std::endl;
			return -1;
		}
		std::string file_name = cmd_args.front(); // Chotkiy
		DirectoryObject* current_dir = shell.getCurrentDir();
        
		if (current_dir->getChild(file_name)) {
			std::cout << "Error: File already exists." << std::endl;
			return -1;
		}

		FileObject* new_file = FileObject::create(file_name, current_dir);
		if (new_file) {
			std::cout << "FileSytem: File '" << file_name << "' created." << std::endl;
			current_dir->displayContent();
			return 0;
		
		}
		else {
			FileSystemError("File with bad name.");
		}
		return -1; 
	}
};


static TouchCommand touchCommandInstance;
