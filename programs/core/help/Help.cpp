#include <iostream>
#include <string>
#include <vector>
#include "Help.h"
#include "../../../cmdunit/CMDunit.h"
#include "../../../shell/Shell.h"

HelpCommand::HelpCommand()
	: Command{ "help", -1, "A program that fetches information about specified commands" }
{
	CommandRegistry::registerCommand("help", this);
}

int HelpCommand::operate(Shell& shell, std::vector<std::string> cmd_args)
{
	HelpProgram* program = new HelpProgram();
	int code = program->run(shell, cmd_args);
	return code;
}

int HelpProgram::run(const Shell& shell, std::vector<std::string> cmd_args)
{
	if (cmd_args.empty())
	{
		std::cout << "help: No arguments provided." << std::endl;
		return -1;
	}
	
	const int TAB_LEN = 5;
	const std::string args_display_words = "Number of allowed arguments (-1 : means any): ";
	const int CHAR_PER_LINE = args_display_words.length();
	const std::string description_display_word = "description";
	const int descrp_word_len = description_display_word.length();


	for (std::string arg: cmd_args)
	{
		std::cout << std::endl;
		Command* cmd = CommandRegistry::getCommand(arg);
		if (!cmd)
		{
			std::cout << "help: Command '" << arg << "' not found." << std::endl;
			continue;
		}
		
		std::cout << "help:";
		
		int diff_without_word = (CHAR_PER_LINE - cmd->getKey().length());
		
		printCharNTimes(diff_without_word / 2, '_');
		std::cout << cmd->getKey();
		printCharNTimes(diff_without_word / 2, '_');
		std::cout << std::endl; 

		printCharNTimes(TAB_LEN, ' ');
		std::cout << "Number of allowed arguments (-1 : means any): " << cmd->getArgNum() << std::endl;
		std::cout << std::endl;

		printCharNTimes(TAB_LEN, ' ');
			
		diff_without_word = (CHAR_PER_LINE -  descrp_word_len); 
		
		printCharNTimes(diff_without_word / 2, '_');
		std::cout << description_display_word;	
		printCharNTimes(diff_without_word / 2, '_');
		std::cout << std::endl;

		std::string description = cmd->getDescription();

		printCharNTimes(TAB_LEN, ' '); // initial TAB
		for (int index = 0; index < description.length(); index++)
		{
			if ((index % CHAR_PER_LINE) == 0)
			{ 
				std::cout << std::endl;
				printCharNTimes(TAB_LEN, ' ');
			}
			std::cout << description.at(index);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	return 0;
}

void printCharNTimes(const int N, const char character)
{	
	for (int i = 0; i < N; i++)
	{ std::cout << character; }
}

static HelpCommand helpCommanInstance;
