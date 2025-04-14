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


	for (int arg_index = 0; arg_index < cmd_args.size(); arg_index++)
	{
		std::string arg = cmd_args.at(arg_index); // get string
		Command* cmd = CommandRegistry::getCommand(arg);
		if (!cmd)
		{
			if (cmd_args.front() != arg 
					&& CommandRegistry::hasCommand(
						cmd_args.at(arg_index - 1)
					)
			) // for printing \n in a smart way
			{ std::cout << std::endl; }
			std::cout << "help: Command '" << arg << "' not found." << std::endl;
			continue;
		}
		
		std::cout << std::endl;
		std::cout << "help:";
		
		int diff_without_word = (CHAR_PER_LINE - cmd->getKey().length());
		
		printCharNTimes(diff_without_word / 2, '_');
		
		/*-------------------*/ std::cout << cmd->getKey(); /*-------------------*/ 
		// ^--- these comments demonstrate the role of 
		// printCharNTimes call which is filling for centering.

		printCharNTimes(diff_without_word / 2, '_');
		std::cout << std::endl; 

		printCharNTimes(TAB_LEN, ' '); // print TAB
		std::cout <<  args_display_words<< cmd->getArgNum() << std::endl;
		std::cout << std::endl;

		printCharNTimes(TAB_LEN, ' '); // print TAB
		diff_without_word = (CHAR_PER_LINE -  descrp_word_len); 
		
		printCharNTimes(diff_without_word / 2 - 3, ' ');
		
		/*-------------------*/ std::cout << "## " << description_display_word << " ##"; /*-------------------*/ 	
		// ^--- these comments demonstrate the role of 
		// printCharNTimes call which is filling for centering.
		
		printCharNTimes(diff_without_word / 2 - 3, ' ');
		std::cout << std::endl;

		std::string description = cmd->getDescription();

		printCharNTimes(TAB_LEN, ' '); // print TAB as (index % CHAR_PER_LINE) == 0 
					       // condition does not hold for index = 0 
					       // which does not meet the need to print TAB
		for (int index = 0; index < description.length(); index++)
		{
			if ((index + 1) % CHAR_PER_LINE == 0) // if it index is the last line of fit
			{ 
				std::cout << std::endl;
				printCharNTimes(TAB_LEN, ' ');
			}
			std::cout << description.at(index);
		}
		std::cout << std::endl;
	}
	if (CommandRegistry::hasCommand(cmd_args.back()))
	{ std::cout << std::endl; }
	return 0;
}

void printCharNTimes(const int N, const char character)
{	
	for (int i = 0; i < N; i++)
	{ std::cout << character; }
}

static HelpCommand helpCommanInstance;
