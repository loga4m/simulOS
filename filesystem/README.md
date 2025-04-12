### simulOS:: FileSystem|FileSystemObject | DirectoryObject | FileObject

#### FileSystem Class
`
FileSystem
- root_dir: DirectoryObject*
+ FileSystem()
+ ~FileSystem()
+ getRootDir()
`

#### FileSystemObject Abstract Class
`
FileSystemObject
`-` name: string
- parent: DirectoryObject*
- created_at: string
- updated_at: string = "(empty)"
`#`  
`
