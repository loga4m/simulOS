#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "CMDunit.h"
#include "../filesystem/FileSystem.h"
#include "../shell/Shell.h"

std::unordered_map<std::string, Command*> CommandRegistry::commandMap {};

bool CommandRegistry::registerCommand(std::string key, Command* cmd)
{
	if (commandMap.find(key) == commandMap.end() && cmd)
	{
		commandMap.insert({key, cmd});
		return true; // on success
	}
	return false; // on failure
}

Command* CommandRegistry::getCommand(std::string key)
{
	if (hasCommand(key))
	{
		return commandMap.at(key);
	}
	return nullptr;
}

bool CommandRegistry::hasCommand(std::string key)
{
	return commandMap.find(key) != commandMap.end();
}

std::vector<std::string> CommandRegistry::getAllCommandNames()
{
	std::vector<std::string> cmd_names = {};

	for (auto key_value: commandMap)
	{
		cmd_names.push_back(key_value.first);
	}

	return cmd_names;
}

CommandHandler::CommandHandler(Shell* inp_shell)
	: shell{ inp_shell }
{}

CommandHandler::~CommandHandler()
{
	shell = nullptr;
}

int CommandHandler::processCommand(std::string user_input)
{
	shell->addHistory(user_input);
	std::vector<std::string> result = parseCommand(user_input);	
	int code = executeCommand(result);
	return code;
}


std::vector<std::string> CommandHandler::parseCommand(const std::string& user_input)
{
	if (user_input.empty())
	{
		return {};
	}
	std::vector<std::string> result {};
	size_t index = 0;
	std::string mover = "";

	while (index < user_input.length())
	{
		if (user_input.at(index) == ' ')
		{
			if (!mover.empty())
			{
				result.push_back(mover);
			}
			mover.clear();
		}
		else {
			mover += user_input.at(index);
		}
		index++;
	}

	if (!mover.empty())
	{
		result.push_back(mover);
	}
	/*  ^
	 *  |__This handles the case when user_input does not
	 *     end with empty space. This results in loop quitting
	 *     due to the length condition without adding mover.
	 */

	return result;
}


int CommandHandler::executeCommand(std::vector<std::string> command_vec)
{
	if (command_vec.empty())
	{ return 0; }
	
	std::string key = command_vec.front();
	command_vec.erase(command_vec.begin()); 
	// ^--- remove command part and keep only arguments

	// Find matching command
	Command* matching_command = CommandRegistry::getCommand(key);
	if (!matching_command)
	{
		// print
		CommandError(key);
		return -1; // exit with error code
	}
	int code = matching_command->operate(*shell, command_vec);
	return code;
}

Command::Command(std::string inp_key, int inp_arg_num, std::string inp_description)
	: key{ inp_key }
	, arg_num{ inp_arg_num }
	, description{ inp_description }
{}

std::string Command::getKey() const
{ return key; }

int Command::getArgNum() const
{ return arg_num; }

std::string Command::getDescription() const
{ return description; }

void CommandError(const std::string& cmd)
{
	std::cout << "CommandUnitError: Command '" << cmd << "'"
		<< " not found." << std::endl;
}
