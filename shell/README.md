# simulOS | Shell

<br>

Shell unit of the program mainly serves to initiate an interactive session for users.
As it is passed to the **Command** interface which enables adding new programs unrelated to the core system, Shell also functions as a medium to give access to FileSystem resources by those programs.

<br>

### Shell
```bash
- name: string
- fsystem: FileSystem*
- cmdHandler: CommandHandler*
- root_dir: DirectoryObject*
- current_dir: DirectoryObject*
+ Shell()
+ ~Shell()
+ startSession(): int
+ addHistory(): int
+ getName(): const string
+ getRootDir(): const DirectoryObject*
+ getCurrentDir(): const DirectoryObject*
+ getHistory(): const string
+ changeCurrentDir(): DirectoryObject*
```

<br>

**Author**: Oyatillo Axadjonov