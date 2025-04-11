#include "CMDunit.h"
#include "../filesystem/FileSystem.h"
#include "../shell/Shell.h"

#include <string>
#include <unordered_map>


std::unordered_map<std::string, Command*> main_cmd_mapper = {
        "cd": CDCommand
};


CommandHandler::CommandHandler(
		Shell* inp_shell
		)
	: shell{ inp_shell }
	, cmd_mapper{ main_cmd_mapper }
{}

int CommandHandler::parse()
{
	execute();
	return 0;
}

int CommandHandler::execute()
{
	return 0;
}


Command::Command(Shell* inp_shell,
		std::string inp_cmd_key,
		int inp_arg_num,
		std::string inp_description)
	: shell{ inp_shell }
	, cmd_key{ inp_cmd_key }
	, arg_num{ inp_arg_num }
	, description{ inp_description }
{};

