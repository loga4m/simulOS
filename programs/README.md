# simulOS | Writing your plug-in-able programs

<br>

Before moving to part of creating your own programs, it is useful to remember about the CMDunit, or thecommand unit, asa whole.
Here is a little diagram for user input flow:

```bash
Shell => listening to commands => user types => enter => 
=> Shell accepts => Pass the user input to CommandHandler::processCommand =>
=> call CommandHandler::parseCommand() to seprate the command and arguments =>
=> return parsed result => CommandHandler accepts => Result is passed =>
=> CommandHandler::executeCommand() => find matching command, to do so call =>
=> CommandRegistry::getCommand() => "it gives or NULLIFIES (returns nullptr)" =>
=> if no match, return -1 => otherwise, get the matching command and call =>
=> matching_command->operate()[look down] => Your Program -> OKAY .
```

<br>

CAUTION: Pass Shell and command_args (not thecommand!) to operate, it is MANDATORY   

<br>

## Now, how does the system recognize your command?

<br>

As you've noticed above, there is a class called CommandRegistry which manages command registration.

It has a **static variable** that **maps** **keywords** with command **classes**. To enable registration and access to commands in the variable, the class provides **static functions (or methods)**.

The **static** is important here. In the context of the abovementioned variable, this means that the variable is loaded before the **main** runs, which is ***critical***.

In the context of functions, the **static** allows us to access those functions **without** the **CommandRegistry** class ***instane***.

<br>

To sum up all the points, CommandRegistry mainly
1. Provides commandMap variable to load commands before the main
2. Provides registerCommand() that enables registering commands
3. Provides the command lookup functionality

<br>

## But, what is the command here about which the whole point talked?

<br>

This is the most essential part. Your programs are **essentially commands** as a user accesses them with commands. Commands mainly have their keyword, acceptable argument numbers, and description. This pattern repeats in every program you create.

<br>

Thus, the system provides you an **abstract Command class** which serves as an interface.

<br>

The first thing you do before you move to the **main logic** of your program is that you create your program's command class which **inherits** from **Command**. As it is an abstract class, it **requires** you to ***override*** the **operate** function which is called by CommandHandler (more about them in cmdunit/README.md) to execute the user command. Also, you are required to pass necessary arguments the **Command** constructors.

<br>

Given you obey one requirement, you have a very good chance to write any logic to your program (yes, limited, but not too much). This requirement, which happens when you write your progrgam command, is to:

1. Register your command in you program command's **constructor** using CommandRegistry::registerCommand()
2. Do not change the **operate** operate function ad its arguments : Shell& shell, vector<string> command_args

<br>

After you write your program command and the program itself, you should create a static instance of your command in the global scope of your implementation file. If you do so, when program runs, the following happens:
1. A **static** instance of YourProgramCommand is created and kept alive till the **main** ends
2. When instance is being created, the command **constructor** is called
3. As you wrote registration in it, it registers YourProgramCommand to the CommandRegistry::commandMap variable
4. Now, your program works.

<br>

## Before moving to the template for writing your program, here are some recommendations:

<br>

### 1. Categorization
Logically categorize your program to either **core** or **usr** (look below for the difference).
Create a new directory in the chosen category. For example, for **history** program, choose /core and create History directory here.

<br>

### 2. Separate the implementation and header files. Never mix them!

<br>

### 3. Including other units 
In the header file, try to avoid including header files of other units like **FileSystem**, **Shell**, etc. As Shell's name is used, you can ***forward-declare*** at the top of your header file. However, you **must** include ***"CMDunit.h"***  header file.

<br>

### 4. Program command and Program Logic
If your pogram logic is small, you can do all the things in the ***overriden*** **operate** function. Otherwise, separate the program logic to another class. For example, **MyProgramNameAppClass**. Then, create an instance of your class inside t**operate** and call functions that run your program. ***This way you clearly separate your program command from the program logic implementation.***

<br>

### 5. Obey to the return codes. **Make sure that *operate* returns integer status code**.
*The difference between core and usr is that core programs do operations specifically targeted to the system. In contrary, usr applications include utilities, text-editors (they can be included to core as well), games, etc.

<br>

That's all for the theory, now it is time to implementation.

<br>

## Implementation Steps & Template

1. Choose the right category
2. Create a directory for your program
3. Create an implementation and header files for your program
4. Start from the header file
5. Include "../../../cmdunit/CMDunit.h" -- extremely critical
6. Declare (not define, since you are in a header file) your command
    - Inherit from Command
    - Declare Constructor
    - Declare operate with exactly similar signature as in Command (look at /cmdunit/CMDunit.h)
7. If your app is large, declare another class for it
8. Keep in mind that your program should start from **operate** even if it is totaly another class
9. Move to the implementation file
10. Start from the constructor
    - Pass the required arguments to **Command** constructor. 
        Arguments are: key, accepted arguments number, command/program description
    - Register your command using **CommandRegistry::registerCommand(<keyword_in_str>, this)** 
        - **this** is really ***this***. You pass your command class to the registrar.
11. Do your implementation
12. At the end, include static instance creation of your command class
13. Make sure your source (implementation) file is included to compilation! If you're using the Makefile of this project, just run make!

<br>

### Here is an example with a template
*Note that this is done for a program enough large to have a separate class.

```bash
    cd programs // go to programs
    cd core //  go to core
    mkdir YourProgramName // create the directory of your program
    cd YourProgramName
    touch YourProgram.h // create your header file
    touch YourProgram.cpp // implementation file
```

<br>

### Header file
```cpp
    #ifndef YOUR_PROGRAM_H // use guards, please!
    #define YOUR_PROGRAM_H


    // Standard library includes at the top
    #include "../../../cmdunit/CMDunit.h"
    // Other includes. Follow hierary (more below after this example)
    
    class Shell; // forward declare Shell as its name (only name! not properties) is used

    class YourCommandName : public Command // inheritance
    {
    public:
        YourCommandName(); // constructor
        int operate(Shell& shell, std::vector<std::string> cmd_args);
        // whatever you want
    };

    class YourProgramLogic
    {
    public:
        //  You can either declare your constructor or leave it as default
        
        int run(// your args, if any); // example function; this is called by operate
        
        // do whatever you want
    }

    #endif
```

### Implementation file

```cpp
    // standard library includes, they are high in hierarchy (very independent)
    // You can include FileSystem.h too, if you need

    #include "../../../cmdunit/CMDunit.h" // you MUST include it
    #include "../../../shell/Shell.h" // now, you can safely do so
    
    // other includes 

    YourCommandName::YourCommandName()
        : Command{ "your_command_name_key", <arg_num>, "your command/program description" } 
        // What if th description is long: Make concise. If still long, try to find other ways.
        // No solution by the system currently.
    {
        CommandRegistry::registerCommand("your_command_key", this); // this is this! -- pointer
    }

    int YourCommandName::operate(Shell& shell, std::vector<std::string> cmd_args)
    {
        .......
    }

    // do whatever you want (but avoid global variables even if static!)
    // for example,

    YourProgramLogic::run(// args, if declared in the header file)
    {
        ......
    }

    // At the end

    static YourCommandName yourCommandInstance;
    // Congrats! Now it should self-register and work!

```

*Include hierarchy is the order of includes by their level of dependence on each other. The higher the order, the more independent is the module.
Standard Library modules are totally independent from our programs. They are included first.*

<br>

As to our own:
- FileSystem.h -- the most independent
- CMDunit.h
- Shell.h


#### Important: Make sure your source (implementation) file is included to compilation! If you're using the Makefile of this project, just run make!

<br>

**Author**: Oyatillo Axadjonov
