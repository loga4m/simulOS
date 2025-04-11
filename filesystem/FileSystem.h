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
	
	FileObject* createFile(
			std::string name, 
			DirectoryObject* parent, 
			std::string create_at, 
			bool is_dir);
	DirectoryObject* createDirectory(
			std::string name, 
			DirectoryObject* parent, 
			std::string created_at, 
			bool is_dir);
	DirectoryObject* getRootDir();

};

class FileSystemObject
{
private:

	std::string name {""};
	DirectoryObject* parent {nullptr};
	std::string created_at {""};
	std::string updated_at {""};
	bool is_dir;

public:
	
	FileSystemObject(
		std::string inp_name,
		DirectoryObject* inp_parent,
		std::string inp_created_at,
		bool inp_is_dir
	);
	
	~FileSystemObject();
	int remove();	
	std::string getName() const;
	DirectoryObject* getParent() const;
	
	// string getPath();
	std::string getCreatedDate() const;
	std::string getUpdatedDate() const;

	int changeUpdatedDate(std::string new_date);
	int rename(std::string new_name);
	bool isDir() const;
	virtual int displayContent() const;
	int displayInfo() const;

};


class DirectoryObject : public FileSystemObject
{
private:
	std::vector<FileSystemObject*> childObjects {};

public:
	
	DirectoryObject(
		std::string inp_name,
		DirectoryObject* inp_parent,	
		std::string inp_created_at,
		bool inp_is_dir
	);
	
	~DirectoryObject();

	int addChildObject(FileSystemObject* childObject);
	int removeChildObject(FileSystemObject* childObject);
	int displayContent() const override;
};


class FileObject : public FileSystemObject
{
private:
	std::string content {""};

public:
	FileObject(
		std::string inp_name,
		DirectoryObject* inp_parent,
		std::string inp_created_at,
		bool inp_is_dir);
	~FileObject();

	int rewrite(std::string new_content);
	int addWrite(std::string new_content);
	std::string read() const;
	int displayContent() const override;

};

#endif
