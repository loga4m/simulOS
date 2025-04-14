#ifndef CLEAR_H
#define CLEAR_H

#include <string>
#include <vector>
#include "../../../cmdunit/CMDunit.h"

/*
 *
 *   Author: Oyatillo Axadjonov
 *
 * */

class Shell;

class ClearCommand : public Command
{
public:
	ClearCommand();
	int operate(Shell& shell, std::vector<std::string> cmd_args) override;
};


#endif
