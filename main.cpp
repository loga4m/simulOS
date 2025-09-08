#include "./cmdunit/CMDunit.h"
#include "./filesystem/FileSystem.h"
#include "./os/os.h"
#include "./shell/Shell.h"
#include "iostream"

int main()
{
    OS os{};
    os.start();
    return 0;
}
