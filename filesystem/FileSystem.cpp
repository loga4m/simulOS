#include <iostream>
#include "FileSystem.h"


// =============================== //
//    FileSystem implementation    //
// =============================== //

FileSystem::FileSystem()
{
	root_dir = DirectoryObject::create("", nullptr, "default");
	std::cout << "Root directory created" << std::endl;
}


FileSystem::~FileSystem()
{
	delete root_dir;
}


DirectoryObject* FileSystem::getRootDir(){ return root_dir; }


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


/*
*   Member function to self-remove an object.
*   Developers are forced to create objects using new via factory methods.
*   @return -1 removing the root directory is forbidden
*			0 on success
*/	

FileSystemObject::~FileSystemObject() = default;
int FileSystemObject::remove()
{
	if (parent == nullptr)
	{
		std::cout << "Cannot remove the root dir. Forbidden." << std::endl;
		return -1;
	}


	parent->removeChildObject(this);
	delete this;
	return 0;
}


std::string FileSystemObject::getName() const{ return name; }

DirectoryObject* FileSystemObject::getParent() const{ return parent; }

// std::string FileSystemObject::getPath()

std::string FileSystemObject::getCreatedDate() const { return created_at; }

std::string FileSystemObject::getUpdatedDate() const { return updated_at; }

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

bool FileSystemObject::isDir() const{ return is_dir; }


// ================================ //
//  DirectoryObject implementation  //
// ================================ //

DirectoryObject::DirectoryObject(
		std::string inp_name,
		DirectoryObject* inp_parent,
		std::string inp_created_at)
	: FileSystemObject(
		inp_name, inp_parent,
		inp_created_at, true)
{}


DirectoryObject::~DirectoryObject()
{
	for (FileSystemObject* childObject: childObjects)
	{
		delete childObject;
	}
}


DirectoryObject* DirectoryObject::create(
		std::string name,
		DirectoryObject* parent,
		std::string created_at)
{
	return new DirectoryObject(name, parent, created_at);
}


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
	if (childObjects.size() == 0)
	{
		std::cout << "(empty)" << std::endl;
		return 0;
	}
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
		std::string inp_created_at
		)
	: FileSystemObject(
			inp_name, inp_parent,
			inp_created_at, false)
{}


FileObject::~FileObject() = default;

FileObject* FileObject::create(
		std::string name,
		DirectoryObject* parent,
		std::string created_at
	)
{
	return new FileObject(name, parent, created_at);
}


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


std::string FileObject::read() const { return content; }


int FileObject::displayContent() const 
{
	std::cout << std::endl;
	std::cout << content << std::endl;
	std::cout << std::endl;
	return 0;
}



// Tester --------\/
// int main()
// {
// 	FileSystem fsys{};
// 	DirectoryObject* root_dir = fsys.getRootDir();
	
// 	// std::cout << root_dir->getName() << std::endl;
// 	DirectoryObject* dir1 = DirectoryObject::create("programs", root_dir, "11/04/2025 10:32PM");
// 	std::cout << (root_dir == nullptr) << std::endl;
// 	FileObject* file1 = FileObject::create("simba", dir1, "11/04/2025 10:33PM");
// 	file1->rewrite("Helloooooo from file 1!");
// 	file1->addWrite("\n Cool!");
// 	// file1->remove();
// 	root_dir->displayContent();
// 	dir1->displayContent();
// 	dir1->remove();
// 	root_dir->displayContent();
// 	// file1->displayContent();
// 	return 0;
// }

