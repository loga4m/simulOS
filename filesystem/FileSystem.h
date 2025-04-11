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

class FileSystemObject
{
protected:

	std::string name {""};
	DirectoryObject* parent {nullptr};
	std::string created_at {""};
	std::string updated_at {""};
	bool is_dir;
    FileSystemObject(
		std::string inp_name,
		DirectoryObject* inp_parent,
		std::string inp_created_at,
		bool inp_is_dir
	);

public:
	
	
	virtual ~FileSystemObject();
	int remove();	
	
	std::string getName() const;
	DirectoryObject* getParent() const;
	
	// string getPath();
	std::string getCreatedDate() const;
	std::string getUpdatedDate() const;

	int changeUpdatedDate(std::string new_date);
	int rename(std::string new_name);
	bool isDir() const;
	virtual int displayContent() const = 0;
	int displayInfo() const;

};


class DirectoryObject : public FileSystemObject
{
private:
	std::vector<FileSystemObject*> childObjects {};
	DirectoryObject(
		std::string inp_name,
		DirectoryObject* inp_parent,	
		std::string inp_created_at);

public:
	
	~DirectoryObject() override;

	static DirectoryObject* create(std::string name, 
		DirectoryObject* parent, 
		std::string created_at);
	

	int addChildObject(FileSystemObject* childObject);
	int removeChildObject(FileSystemObject* childObject);
	int displayContent() const override;
};


class FileObject : public FileSystemObject
{
private:
	std::string content {""};
	FileObject(
		std::string inp_name,
		DirectoryObject* inp_parent,
		std::string inp_created_at);

public:
	
	~FileObject() override;

	static FileObject* create(std::string name, 
		DirectoryObject* parent, 
		std::string created_at);


	int rewrite(std::string new_content);
	int addWrite(std::string new_content);
	std::string read() const;
	int displayContent() const override;

};

#endif
