#include <iostream>
#include "FileSystem.h"


// FileSystem implementation

FileSystem::FileSystem()
{
	root_dir = new DirectoryObject("", nullptr, "default", true);
	std::cout << "Root directory created" << std::endl;
}

FileSystem::~FileSystem()
{
	delete root_dir;
}

DirectoryObject* FileSystem::createDirectory(
		std::string name,
		DirectoryObject* parent,
		std::string created_at,
		bool is_dir)
{
	return new DirectoryObject(name, parent, created_at, is_dir);	
}

FileObject* FileSystem::createFile(
                std::string name,
                DirectoryObject* parent,
                std::string created_at,
                bool is_dir)
{
        return new FileObject(name, parent, created_at, is_dir);
}


DirectoryObject* FileSystem::getRootDir()
{
	return root_dir;
}


// =============================== //
// FileSystemObject implementation //
// =============================== //

FileSystemObject::FileSystemObject(
		std::string inp_name,
		DirectoryObject* inp_parent,
		std::string inp_created_at,
		bool inp_is_dir)
	: name{ inp_name }
	, parent{ inp_parent }
	, created_at{ inp_created_at }
	, is_dir{ inp_is_dir }
{
	if (inp_parent) {
		inp_parent->addChildObject(this);
	}
};

FileSystemObject::~FileSystemObject() = default;

std::string FileSystemObject::getName() const
{
	return name;
}

/*
 * Remove this object from the file system and frees up the memory
 * IMPORTANT: This works only for {DirectoryObject|FileObject} created using dynamic memory allocation
 * To ensure dynamic memory allocation, use factory methods defined in FileSystem class
 * @return 0 on succes, -1 if the object is a root directory,
 *	-2 if the object appears stack-allocated
 * 
 * Got this DOC from Claude.ai
 * Learn the solution from Claude.ai
 */
int FileSystemObject::remove()
{
	if (parent == nullptr)
	{
		std::cout << "Cannot remove root directory. Forbidden." << std::endl;
		return -1;
	}


	parent->removeChildObject(this); // parent: DirectoryObject*
	delete this;
	return 0;
}



DirectoryObject* FileSystemObject::getParent() const
{
	return parent;
}

// std::string FileSystemObject::getPath()

std::string FileSystemObject::getCreatedDate() const
{
	return created_at;
}

std::string FileSystemObject::getUpdatedDate() const
{
	return updated_at;
}

int FileSystemObject::changeUpdatedDate(std::string new_date)
{
	updated_at = new_date;
	return 0;
}

int FileSystemObject::rename(std::string new_name)
{
	name = new_name;
	return 0;
}

bool FileSystemObject::isDir() const
{
	return is_dir;
}

int FileSystemObject::displayContent() const
{
	std::cout << "Access denied" << std::endl;
	return 0;
}



// ================================ //
//  DirectoryObject implementation  //
// ================================ //

DirectoryObject::DirectoryObject(
		std::string inp_name,
		DirectoryObject* inp_parent,
		std::string inp_created_at,
		bool inp_is_dir)
	: FileSystemObject(
		inp_name, inp_parent,
		inp_created_at, inp_is_dir)
{}

DirectoryObject::~DirectoryObject() = default;

int DirectoryObject::addChildObject(FileSystemObject* newChildObject)
{
	childObjects.push_back(newChildObject);
	return 0;
}

int DirectoryObject::removeChildObject(FileSystemObject* childObject)
{
	for (int index = 0; index < childObjects.size(); index++)
	{
		if (childObjects.at(index) == childObject)
		{
			childObjects.erase(childObjects.begin() + index);
			break;
		}
	}
	return 0;
}

int DirectoryObject::displayContent() const
{
	for (FileSystemObject* child: childObjects)
	{
		std::cout << child->getName() << ((child->isDir()) ? "/":"")  << "    ";
	}
	std::cout << std::endl;
	return 0;
}

// =============================== //
//    FileObject implementation    //
// =============================== //

FileObject::FileObject(
		std::string inp_name,
		DirectoryObject* inp_parent,
		std::string inp_created_at,
		bool inp_is_dir
		)
	: FileSystemObject(
			inp_name, inp_parent,
			inp_created_at, inp_is_dir)
{}

FileObject::~FileObject() = default;

int FileObject::rewrite(std::string new_content)
{
	content = new_content;
	return 0;
}

int FileObject::addWrite(std::string new_content)
{
	content += new_content;
	return 0;
}

std::string FileObject::read() const
{
	return content;
}

int FileObject::displayContent() const 
{
	std::cout << std::endl;
	std::cout << content << std::endl;
	std::cout << std::endl;
	return 0;
}


int main()
{
	FileSystem fsys{};
	DirectoryObject* root_dir = fsys.getRootDir();
	std::cout << root_dir->getName() << std::endl;
	DirectoryObject dir1 {"programs", root_dir, "11/04/2025 10:32PM", true};
	std::cout << (root_dir == nullptr) << std::endl;
	root_dir->remove();
	FileObject file1 {"simba", &dir1, "11/04/2025 10:33PM", false};
	file1.rewrite("Helloooooo from file 1!");
	FileObject* file2 = new FileObject{"simbajon", &dir1, "11/04/2025 10:34PM", false};
	file2->addWrite("Helloooooo from file 2!");
	root_dir->displayContent();
	dir1.displayContent();
	file1.displayContent();
	file2->displayContent();
	file1.remove();
	file2->remove();
	return 0;
}

