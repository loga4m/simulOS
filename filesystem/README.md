# simulOS:: FileSystem | FileSystemObject | DirectoryObject | FileObject | Utility Functions

## Special Notes

### Design of FileSystemObjects
In this design, assignning an extension for files is not allowed since the most intrinsic part, which a ".", is not allowed in naming. Instead, **DirectoryObject** and **FileObject** is differentiated using inherent getter **isDir()**.

<br>

### FileSystemObject::remove()
This function is used to self-remove by Directory and FilObject classes. The end result of using this function is that the object will be deleted. However, your pointer with to the deleted object will NOT be NULLIFIED. Thus, make sure to set your pointer to NULLPTR.

<br>

### FileSystemObjects -- Factory Method ::create()
Creating **FileSystemObject**s is only possible using **DirectoryObject::create()** or **FileObject::create()**. Using **FileSystemObject** of object creation is impossible since the class is **abstract**.
This design has been chosen intentionally to enforce **dynamic memory allocation** which is a requirement for the proper work of **FileSystemObject::remove()** function.

<br>

### DirectoryObject::create()
This static factory method is used to ensure that DirectoryObject is created using dynamic memory allocation. Althoug it valides arguments for some cases, it DOES NOT check the case when name is empty and parent is nullptr. This is doen intentionally in the current design as it allows creating the root directory by FileSytem with empty name and nullptr parent. Therefore, MAKE SURE at least one of your arguments is valid in passing. Checking for validity of **parent** is recommended as **name** is validated **automatically** when **parent** is **valid**. 

<br>
<br>

## Classes

### FileSystem
```bash
- root_dir: DirectoryObject*
+ FileSystem()
+ ~FileSystem()
+ getRootDir()
```

<br>

### FileSystemObject Abstract Class
```bash
- name: string
- parent: DirectoryObject*
- created_at: string
- updated_at: string = "(empty)"
# FileSystemObject(
        name: string,
        parent: DirectoryObject*
        is_dir: bool
    )
    |
    ---> intializes values
    Calls: getCurrentTime() to initialize created_at member variable
    Does: if parent is existent, calls parent's addChildObject member function to bind itself to its parent
    WARNING: Do not pass nullptr for parent! This is only allowed for internal root directory set up

# nameValidator(name: const string&) static bool
    |
    ---> validates names in creation and renaming
    Does not permit dots and slashes in file names
    You can find all disallowed characters in the implementation file
    @returns true --> on success false --> if name fails to meet requreiements

+ ~FileSystemObject(): virtual --> deletes root_dir

+ remove(): int 
    |
    ---> a function to self-remove of objects; used by DirectoryObjects & FileObject classes
    @returns 0 --> success; -1 --> failure when a user attempts to remove the root directory
    WARNING: Don't forget to set your object to nullptr after removel; otherwise, it would lead to undefined behavior

+ getName(): const string
+ getParent(): string
+ getCreatedTime(): const string
+ getUpdatedTime(): const string

+ changeUpdatedTime(): int --> updates updated_at member variable to calling time
    @returns 0 --> success

+ rename(new_name: string): int --> updates name by new_name; 
    @returns 0 --> success; -1 failure aborting when a user attempts to rename the root directory

+ isDir(): bool
+ displayContent(): const virtual int = 0 --> virtual function resolving to the implementation of derived classes

+ displayInfo(): int 
    |
    ---> displays main information about the current object
    STDOUT: name, is directory, parent directory name, location, created at, updated at
    @returns 0 --> success
```

<br>

### DirectoryObject Class : public FileSystemObject
```bash
- childObjects: vector of FileSystemObject*
- DirectoryObject(
        name: string,
        parent: DirectoryObject*
    )
+ ~DirectoryObject() override 
    |
    ---> this overridden desctructor deletes all childObjects belonging to it

+ create(
        name: string,
        parent: DirectoryObject*
    ): static DirectoryObject*
    |
    ---> a factory method to force creating DirectoryObjct by dynamic allocation;
    Warning: this method returns pointer to a memory address. DirectoryObject constructor is inaccessible.

+ addChildObject(childObject: FileSystemObject*) int
    @returns 0 --> success; -1 --> failure when the passed object is already exists

+ removeChildObject(childObject* FileSystemObject*) int
    |
    ---> removes passed childObject, if it exists, from childObjects
    @returns 0 --> success

+ getChild(name: string): FileSystemObject* 
    |
    ---> returns a child object; in case it fails, returns **nullptr**
    Warning: If you want to use specific attributes (member functions or variables) 
             of either DirectoryObject or FileObject, you have to typecast current object
             to them. It is allowed.

+ displayContent(): const override int
    |
    ---> prints out the content of current directory
    STDOUT: list of childObjects
    @returns 0 --> success
```

<br>

### FileObject : public FileSystemObject
```bash
- content: string
- FileObject(
        name: string,
        parent: DirectoryObject*
    )
+ ~FileObject() override --> uses default de-constructor
+ create(
        name: string,
        parent: DirectoryObject*
    ): static FileObject*
    |
    ---> a factory method to force creating FileObject by dynamic allocation;
    Warning: this method returns pointer to a memory address. FileObject constructor is inaccessible.

+ rewrite(new_content: string) int 
    |
    ---> totally replaces the current content by new_content
    @returns 0 --> success

+ addWrite(new_content: string) int 
    |
    ---> addes new_content to the current content
    @returns 0 --> success

+ read() const string
    @returns content

+ displayContent() const override int 
    STDOUT: name, content
    @returns 0 --> success
```

<br>
<br>

## Utility Functions

### pathBuilder
```bash
pathBuilder(fsystemObject: FileSystemObject*): string
    |
    ---> given a valid object, this function builds path in string type and returns it
    @returns "/" immediately if fsystemObject's parent is nullptr (meaning, this object is the root director)
    @returns "(invalid)" if nullptr, or non-existent object, is passed
    @returns path if everything is successful
```

<br>

### getCurrentTime
```bash
getCurrentTime(): string
    |
    ---> uses standard library to return current time in format "year/month/day hours:min:sec"
    @returns string
```

<br>

### objectLocator
```bash
objectLocator(
        root_dir: DirectoryObject*,
        current_dir: DirectoryObject*,
        path: string
    )
    @returns the object shown in the path on success
    @returns root_dir if path is "/" or path.lengh is 0 (typical behavior when calling only "cd" in Linux)
    
    Actions:
        - if path starts with "/", the traversal from the root directory
        - if path does not start with any slashes ("/"), the traversal starts from current directory
        - every ".." is a command to step out above in the hierarchy
            - during the traversal, if the parent of current object of traversal is nullptr,
              this is considered as an "Attempt to leave the root directory." and *nullptr* is returned
        - every "." is a command to continue looping without changng the object of traversal
        - if the current object of the traversal happens to be a *FileObject*,
          the traversal terminates. If it is evident that traversal didn't terminate
          at the end, the function raises "Not found."
    
    Handles all error cases mentioned below:
        - Passing non-existent paths
            example path: dir1/dir2 -- where either is non-existent
        - Injecting FileObject in path (this is an error if DirectoryObject is followed by it)
            example path: dir1/dir2/file1/dir3 -- evidently, file1 cannot have *childObjects*
        - Attempt to leave the root directory
            current_dir: root_dir
            example path: ../ -- this is forbidden
```

<br>

### FileSystemError
```bash
FileSystemError(err_message: const string&): void
    |
    ---> a helper function to print customized error messages
    STDCERR: FileSystemError: {err_message} 
    @returns void
```

<br>

**Author:** Oyatillo Axadjonov
