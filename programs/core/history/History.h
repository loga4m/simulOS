#ifndef HISTORY_H
#define HISTORY_H

#include <vector>
#include <string>

class Shell;
#include "../../../cmdunit/CMDunit.h"


/*
 *
 *   Author: Oyatillo Axadjonov
 *
 * */


class HistoryCommand : public Command
{
public:
	HistoryCommand();
	int operate(Shell& shell, std::vector<std::string> args) override;
};

class HistoryApp
{
public:
	int run(const Shell& shell, std::vector<std::string> command_v);
};

#endif
