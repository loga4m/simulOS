# simulOS | OS

<br>

This unit of program contains OS class which is called by `main`. It instantiates exactly one instances of FileSytem and Shell, and they are both dependent on the OS.

When an intance of OS is created, it calls its start function which calls Shell::startSession() which starts interactive session for a user. When Shell session is closed by a user, the OS instance calls stop.

After it, before the main function stops, OS calls its deconstructor which first deletes the Shell instance (this order is safe) followed by the removal of the FileSystem instance.

<br>

```
- fsystem: FileSystem*
- shell: Shell*
+ OS();
    ^---- Creates **fsystem** and assignes it to **shell** during its creation 
+ ~OS();
    ^---- Cleans up **fsystem** and **shell**
```
