#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <vector>

class FileSystemObject;
class DirectoryObject;
class FileObject;

class FileSystem
{
private:
	
	DirectoryObject* root_dir {nullptr};

public:
	
	FileSystem();
	~FileSystem();
	
	DirectoryObject* getRootDir();

};

std::string pathBuilder(FileSystemObject* fsystemObject);
FileSystemObject* objectLocator(
	DirectoryObject* root_dir, 
	DirectoryObject* current_dir, 
	std::string path
);
std::string getCurrentTime();
void FileSystemError(const std::string& err_message);


class FileSystemObject
{
private:

	std::string name {""};
	DirectoryObject* parent {nullptr};
	std::string created_at {""};
	std::string updated_at {""};
	bool is_dir;

protected: 
	// ^-- as the constructor should be accessible in derived classes
	FileSystemObject(
		std::string inp_name,
		DirectoryObject* inp_parent,
		bool inp_is_dir
	);
	static bool nameValidator(const std::string& name);
	// ^-- for name validation
public:
	
	virtual ~FileSystemObject();
	int remove();	

	std::string getName() const;
	DirectoryObject* getParent() const;

	std::string getPath();
	std::string getCreatedTime() const;
	std::string getUpdatedTime() const;

	int changeUpdatedTime();
	int rename(std::string new_name);
	bool isDir() const;
	virtual int displayContent() const = 0;
	int displayInfo();

};


class DirectoryObject : public FileSystemObject
{
private:
	
	DirectoryObject(
		std::string inp_name,
		DirectoryObject* inp_parent
	);

public:
	
	std::vector<FileSystemObject*> childObjects {};
	~DirectoryObject() override;

	static DirectoryObject* create(
		std::string name,
		DirectoryObject* parent
	);
	
	int addChildObject(FileSystemObject* childObject);
	int removeChildObject(FileSystemObject* childObject);
	FileSystemObject* findChild(std::string name);
	int displayContent() const override;

};


class FileObject : public FileSystemObject
{
private:

	std::string content {""};
	FileObject(
		std::string inp_name,
		DirectoryObject* inp_parent
	);

public:
	
	~FileObject() override;

	static FileObject* create(
		std::string name,
		DirectoryObject* parent
	);

	int rewrite(std::string new_content);
	int addWrite(std::string new_content);
	std::string read() const;
	int displayContent() const override;

};

#endif
