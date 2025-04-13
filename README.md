# simulOS -- simulated Operating System

This is a program that tries to simulate Linux operating system by imitating several features.
Namely, they are shell, filesystem, command handling unit, and core/user-defined programs.

Except programs part, all parts are defined as classes, with not mentioned OS class aggregating them. They are organized in a directories resembling modules.

OS class serves to instantiate FileSytem and Shell.

**Shell** is a class/sub-program that allows a user to interact with the system, and run core/usr(user-defined) programs. As user writes a command and hits the enter, Shell implicitly redirects the control to **CommandHandler** class of command unit. 

**CommandHandler** parses the user input and tries to match a command from the commands of existing programs. Any matching command found, it will execute it.

**simulOS** has been designed to provide extensibility before compilation, if not on runtime. This means that others can include their programs with their corresponding commands. This design is made possible by creating an interface that makes user-defined program commands plug-in-able.

The interface, **Command**, is provided by command unit. Beyond giving extensibility, it also provides an access to **FileSystem** resources.

**FileSystem** class organizes files and directories and their management in the system. Files and directories are the same except for some differences like files have content while directories can have children. Also, currently, there is no support for file extensions and, thus, including **dots** and **slashes** is strictly disallowed, and the creation of files/directories violating naming is disregarded.




