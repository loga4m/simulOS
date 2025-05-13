# simulOS -- simulated Operating System

## Description
This is a program that tries to simulate Linux operating system by imitating several features.
Namely, they are shell, filesystem, command handling unit, and core/user-defined programs.

<br>

## Running the program
```bash
    git clone https://github.com/oyatillonewuu/simulOS
    cd simulOS
    make // if you have it on your system
    ./simulos
```
If you don't have **make** utility on your system, run the program typically and ensure that all source (\***.cpp**) files are compiled. 

<br>

## System components & workflow
Except programs part, all parts are defined as classes, with not mentioned OS class aggregating them. They are organized in a directories resembling modules.

OS class serves to instantiate FileSytem and Shell.

<br>

## Shell
**Shell** is a class/sub-program that allows a user to interact with the system, and run core/usr(user-defined) programs. As user writes a command and hits the enter, Shell implicitly redirects the control to **CommandHandler** class of command unit. 

<br>

## Command Handling
**CommandHandler** parses the user input and tries to match a command from the commands of existing programs. Any matching command found, it will execute it. The control is returned back to Shell.

<br>

## Extensibility feature
**simulOS** has been designed to provide extensibility before compilation, if not on runtime. This means that others can include their programs with their corresponding commands. This design is made possible by creating an interface that makes core/user-defined program commands plug-in-able.

### The Interface for Extending
The interface, **Command**, is provided by the command unit. Beyond giving extensibility, it also provides an access to **FileSystem** resources by passing Shell which has the main FileSytem resources which are root directory and current directory.

To use the extensibility feature, a developer creates a class for the command of their app. This class inherits from **Command** abstract (or interface in this context) class and passes necessary arguments like the keyword of a command, its number of arguments, and the description. The **virtual** function operate has to be ***overriden***, or adjusted. Then a developer has two choices: either write their program in this command class or write another class for the program logic and make it callable from the command they defined. This depends on how large is their program.

After the program command and logic is implemented, the developer has to registerCommand function provided by CommandRegistry class -- which loads core/user-defined programs before the main program runs.

<br>

## About FileSystem and its rules
**FileSystem** class organizes files and directories and their management in the system. Files and directories are the same except for some differences like files have content while directories can have children. Also, currently, there is no support for file extensions and, thus, including **dots** and **slashes** is strictly disallowed. So the creation of files/directories violating the naming is automatically disregarded.

<br>

## Design

### Operation Execution Success & Error Handling

All main system operations use integer-based code to indicate different errors. Here are primary ones:
```
    0 -- success
    -1 -- error
    -2 -- shutdown/exit system/Shell signal
```

<br>

## Limitations

**Limitation #1**: To add meaning to errors, some error handlers directly print their error message to **STDOUT** alongside their integer status code. However, this design comes with a tradeoff that these operations cannot return messages to callers that may potentially use these messages.

<br>

**Limitation #2**: As mentioned, there is no support for file extensions.

<br>

**Limitation #3**: In FileSystem management, there is need to create Directories or Files. Due to another functionality which requires that these objects are **strictly dynamically allocated**, using *direct intializaton via* **constructor** is **strictly disallowed**. Any attempt to do so, the system will crash raising errors.
Thus, to **enforce** dynamic memory allocation, factory methods inside DirectoryObject and FilObject classes have been implemented.

<br>

**Limitation #4**: This limitation is the self-removal of Directory or File objects. TO delete them, this function uses **delete** keyword which **requires** that the object to be deleted is of a **pointer** type. If a developer uses thefactory methods mentioned above, there should be no errors.

<br>

**Limitation #5**: FileSystem and other parts of the system massively user pointers for their operation. Tere are cases where objects potentially can be used with references which are safer than pointers.

<br>

**Limitation #6**: When creating FileSystem objects, the system automatically assigns their creation time. The limitation is that **string** type is used for timekeeping. This also applicable for for function that assigns time of update of a particular file/directory.

<br>

**Limitation #7**: This limitation is that the system is just a simulator.

<br>
