### Apr 15, 8:51 PM

<br>

#### Change on the `cd` command
Before this correction, the `cd` command program malfunctioned allowing a user to move to a FileObject. After changing the current directory to that FileObject, `cd ..` command didn't work. But with a shallow logic, it had to.

Analyzing the `cd` program code, I've found that there was no checker for the **FileSystemObject** type to detect whether the object found by **objectLocator** was a DirectoryObject type or FileObject type. After that, the program used **static_cast** to cast the **FileSystemObject**(returned by **objectLocator**) to **DirectoryObject**. To my surprise, despite having a **DirectoryObject** type for **current_dir**, the operation succeeded.

As for the **objectLocator**, there was no problem. `cd ..` problem ocurred because **objectLocator** raised an error saying **FileSystemObject not found** which is technically correct as **objectLocator** stops traversal when the current object of the traversal is a FileObject. Then it cheks whether there is remaining part of the path. If so, the path is incorrect since FileObject cannot have children and thus no further path.

The same thing happened in the case above as current_dir was marked as FileObject and was passed when `cd ..` was called.

The problem is seems to be with the casting itself. To check, I changed it to **dynamic_cast** and used inherent **displayInfo**(prints the information about that object) function. First of all, the current drectory didn't change. Secondly, the current directory was just root_dir! Then, I did the same for **static_cast** and it showed that file's info. But, it is still ambiguous whether **dynamic_cast** actually changed the object to **root_dir**, **prevented**, or casted the object to its parent object. To answer this, I tried to change the **current directory** to a valid one. If it changes to **root_dir**, it happens. If it does not, then either it **prevents** or casts the object to its **parent**.

As to the results, the suspicion is false. To ensure that **dynamic_cast**  line of the code worked, I manually printed a message before function **returned**. It ***worked***. So, either the cast was **prevented** or **done**. To make sure, I check the **changeCurrentDir** function whether there was any type "catchers". There was no.

So, it ***dynamically casted to the parent directory***. For now, this is the most logical conclusion based on the evidence.

As I don't know how static_cast and dynamic_cast work, I am including object type checker before the code goes to the cast line.

<br>

### Apr 15, 10:04 PM
Issue occurred:
    - source: `touch` program
    - problem: does not allow creation of a file with a name that a drectory in the current dir holds
    - expected: it has to allow since the objects have two different types
Solution:
    - the program uses DirectoryObject::getChild(`name`) function, which returns ***FileSytemObject*** type
    - thus, we need to check whether the resulting object is a `DirectoryObject`. If so, allow file creation.

<br>
<br>

#### UPDATE
Abandoning this feature as it even Linux does not allow having the files and directories with the same name, unless an extension differentiates them.

<br>

For curiosity: If I allowed, it would be a problem for the `info` program since it uses **objectLocator** which 
uses getChild which returns the first matching child!
Indeed, this was proved in the issue below in case of **rm** program. Also, it was proved for it too.

<br>
<br>

#### UPDATE 10:26 PM
ISSUE Detected: In the hypothetical case of allowing a DirectoryObject and FileObject having the same name, rm does not care whether it is file or not! It just uses FileSystemObject::remove function on the object returned by getChild! 

<br>

Conclusion of the last two issues: 
- Do not allow creation with the same name.
- In programs, check whether the result objects of your lookups are exactly what you want!
- BIG SYSTEM CHANGE: Use either **templates** or **function overloading** for handling different types.
    - THE ANSWER TO BIG WHY: Allowing the base class to handle different types means allowing **ambiguity**.

For now, rolling back naming change.

<br>
<br>

#### UPDATE 10:40
- Updating `ls` program's output
- Added type handlers to `rm` and `rmf` as they were able to delete Directory and File (respectively) too which i sdisallowed
- Updated error message of `mkdir` for naming (two cases: either a file or directory with this name exists. For simplicity, just prints `FileSystemObject` instead of telling exactly)

<br>

#### UPDATE 10:50
- addHistory is not changing the update time. The issues is with addWrite function (similarly, rewrite too) in FileSystemObject. Adding changeUpdatedTime function call.

<br>
<br>

#### UPDATE 10:56
- `ls (empty argument)` is listing root_dir content: undesired behavior
- After an analysis, I've found that there was a logic error in `objectLocator` which returned root_dir if the given path was either "/" or empty. In reality, it should return current_dir in case the path is empty, and this is well followed in the rest of logic where path is not empty and traversal starts from current_dir if path does not start with "/". Empty case is a special case of it.

<br>
<br>

#### UPDATE 11:03
When created many FileSystemObjects, a segmantation fault is happening after shutdown command is executed. This should be due to FileSystem clean up.

Specifically, I detected that it is occurring in the DirectoryObject deconstructor which iterates on `childObjects` vector, deleting each child and removing from the vector.

<br>
<br>

I am assuming:
1. error is because the size of vector is changing
2. and so the object of iteration! 
3. And so it is attempting to use `delete` on on a deleted address!
All of the assumptions are indeed true based on the debug result below!

<br>

### Logs
```bash
    original
    0x6331f98b5de0
    0x6331f98b6160
    0x6331f98b6200
    0x6331f98b6300
    
    error is here
    Size changing: 4
    0x6331f98b5de0
    original

    error is here
    Size changing: 3
    0x6331f98b6200
    
    error is here
    Size changing: 2
!=> 0x6331f98b6300
    
    error is here
    Size changing: 1
!=> 0x6331f98b6300
    Segmentation fault (core dumped)

```

<br>

### The code:
```cpp
357 DirectoryObject::~DirectoryObject()
358 {
359         std::cout << "original" << std::endl;
360         for (FileSystemObject* childObj: childObjects)
361         {
362                 std::cout << childObj << std::endl;
363         }
364         for (FileSystemObject* childObject: childObjects)
365         {
366                 std::cout << "error is here" << std::endl;
367                 std::cout << "Size changing: " << childObjects.size() << std::endl;
368                 std::cout << childObject << std::endl;
369                 this->removeChildObject(childObject);
370                 delete childObject;
371         }
372 }
```

<br>

Curious: how does that type of iteration work????
Interestingly, as we can see from logs, the following pattern is followed. Denote object vector: {1,2,3,4}
- There are 4 four addresses
1. Free address one. Remove child from the vector. So, we move to the second.
2. So far, we have: {2,3,4}. Second object is 3. Delete & remove. So, next object is third.
3. So far, we have: {2, 4}. Got 4, deleted & removed. {2}????????
4. Accessed again 4!
This is exactly what happened above. So, how does that way of iteration actually work? 

<br>

**Solution 1**: copy the childObjects list wholly and do iteration on the copy while removing from actual vector
This solution is expensive as FileSystem gets larger.

<br>

**So, solution 2**:

Don't remove from childObjects. To prevent dangling pointer, set each deleted object to nullptr and let it remain in the vector. To do so, we can only use pure iteration with index. I think so.

Results
<br>

### Logs (adjusted for readability)
```bash
    original
    0x5becfe899de0
    0x5becfe89a160
    0x5becfe89a230
    0x5becfe89a300
    0x5becfe89a3f0
    0x5becfe89a550
    0x5becfe89a620
    
    0x5becfe89a760
    error is here
    Size changing: 8
    0x5becfe899de0
    
    original
    error is here
    Size changing: 8
    0x5becfe89a160
    
    original
    error is here
    Size changing: 8
    0x5becfe89a230
    original
    
    error is here
    Size changing: 8
    0x5becfe89a300
    original
    
    error is here
    Size changing: 8
    0x5becfe89a3f0
    
    original
    error is here
    Size changing: 8
    0x5becfe89a550
    
    error is here
    Size changing: 8
    0x5becfe89a620
    
    error is here
    Size changing: 8
    0x5becfe89a760
```

<br>

### Code
```cpp
357 DirectoryObject::~DirectoryObject()
358 {
359         std::cout << "original" << std::endl;
360         for (FileSystemObject* childObj: childObjects)
361         {
362                 std::cout << childObj << std::endl;
363         }
364         for (int childObjIndex = 0; childObjIndex < childObjects.size(); childObjIndex++)
365         {
366                 std::cout << "error is here" << std::endl;
367                 std::cout << "Size changing: " << childObjects.size() << std::endl;
368                 std::cout << childObjects.at(childObjIndex) << std::endl;
369
370                 delete childObjects.at(childObjIndex);
371                 childObjects.at(childObjIndex) = nullptr;
372         }
373 }
```

Now, "error is here" is false. Error is nowhere! Working well here.
Tested with nested objects. Working fine.

### UPDATE: 11:53 PM
Removing print debugger :)


### Sep 13, 2025, 09:15 AM

I was working on the issue of RM & history. The problem was that after
rm-ing the shell history file, any command caused double free error.

I don't know why it is called double free, but I have identified that
the cause was the shell->addHistory(...) call in the CMDunit::process_command
function. Subsequently, in Shell::addHitory, the system tried to access
the history variable to get its content via getHistory which accesses history
pointer with "->" operator.
As of internals of RM command, it uses FileObject::remove function which
essentially deletes itself. However, if there is a pointer variable to this
object, it does not set the pointer to NULL, resulting in a **danging pointer**.

Based on the current knowledge, I believe this is the only case that
history variable will be corrupted. Thus, I added try-catch block to 
addHistory function.

It tries to access the content of the object at `history`, and in case of
any error, it re-creates the history file.

At the same time, does not check whether the `history` variable was
corrupted by freeing but not setting to NULL or just was simply corrupted.

Again, as I believe RM-ing is the only way for it to be corrupted, I don't need to
handle it.


# ^->**It didn't work.**
