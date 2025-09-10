### Sep 10, 2025
- Added 'apps' and 'alias' programs
  - custom name validator is needed for 'alias' program
- Added built-in error for command arguments
  - 'ls' program does not work without arguments.
  - This may look like a drawback, but this enhancement removed a lot of boilerplate from adding programs
- Separated FileSystemObject::nameValidator to a separate unit `filesystem/utils` for further use by other modules
- Needs documentation changes now
