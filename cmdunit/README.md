# simulOS | CMDunit

<br>

## Classes

<br>

### CommandHandler
```bash
- shell: Shell*

+ CommandHandler(inp_shell: Shell*)
+ ~CommandHandler()
+ processCommand(user_input: string): int
+ parseCommand(user_input: const reference): vector <string>
+ executeCommand(user_input_vec: vector <string>): int
```

<br>

### Command
```
# key: string
# arg_num: int
# description: string

+ Command( key: string, arg_num: int, description: string )
+ getKey(): const string
+ getArgNum(): const int
+ getDescription(): const string
+ operate( shell: Shell&, cmd_args: vector <string> ): virtual int = 0
```

<br>

### CommandRegistry
```
- commandMap: unordered_map < string , Command* >

+ registerCommand(key: string, cmd: Command*): static bool
+ getCommand(key: string): static Command*
+ hasCommand(key: string): bool
+ getAllCommandNames(): vector <string>
```

<br>
<br>

## Helper Functions

### CommandError
```
CommandError(err_message: const string&): void
```

<br>

**Author**: Oyatillo Axadjonov










