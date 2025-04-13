#include "iostream"
#include "./filesystem/FileSystem.h"
#include "./cmdunit/CMDunit.h"
#include "./shell/Shell.h"
#include "os.h"

int main()
{
	OS os{};
	int x = os.start();
	return 0;
}
