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


/*
*  	A function to buidl string path for a FileSystem Object.
*	@returns string path
*/
std::string pathBuilder(FileSystemObject* fsystemObject)
{
	if (fsystemObject->getParent() == nullptr)
	{
		return "/";
	}

	std::string path = "";
	FileSystemObject* head = fsystemObject; // for bottom-up traversal
	
	while (head->getParent())
	{
		path = "/" + head->getName() + path;
		head = head->getParent();
	}

	return path;
}


FileSystemObject* objectLocator(
	DirectoryObject* root_dir, 
	DirectoryObject* current_dir, 
	std::string path
)
{
	std::string err_message = "Not Found.";
	if (path.length() == 0) { FileSystemError(err_message); } // Obviously


	FileSystemObject* mover = nullptr; // Initiliazing mover for further use
	int index = 0;


	int firstChar = path.at(0); // Getting first chracter to detect where to start
	if (firstChar == 47) // ASCII 47: '/'
	{
		// ASCII 47 means '/' which is root directory
		// Traversal starts from index 1, skipping the root dir. slsh
		mover = root_dir;
		index = 1; 
	}
	else { mover = current_dir; } // In any else case, traversal starts from current directory



	path += "/"; //  This makes sure that the traversal goes till the end
	int length = path.length();
	std::string path_part = "";

	// ^-- This helps to keep track of each sub-paths

	while (index < length) // If the path is correct, index is exactly equal to length
	{
		// If mover becomes a FileObject from the prev. iteration, then immediately break
		if (!mover->isDir())
		{
			break;
		}
		if (path.at(index) == '/')
		{

			// '..' is a command to go one step out
		
			if (path_part == "..")
			{
				if (!mover->getParent())
				{
					// ^...if the current directory is the root dir., 
					// then accessing parent returns nullptr, which
					// means there is no way further. Therefore,
					// the path is incorrect.

					FileSystemError(err_message);
					return nullptr;
				}

				// In the else case, update subpath tracker and
				// change current mover to its parent.
				path_part = "";
				mover = mover->getParent();
				index++;
				continue;
			}

			if (path_part == ".")
			{
				// ^... '.' is a special command commanding 'stay there'.
				// So, just update subpath, increment, and continue traversal.
				path_part = "";
				index++;
				continue;
			}

			FileSystemObject* foundChild = static_cast<DirectoryObject*>(mover)->findChild(path_part);
			// If no cases are handled, it is time to check current subpath whether
			// it is in the mover drectory. If a path is correct, then there is a solution.

			if (!foundChild)
			{
				FileSystemError(err_message);
				return nullptr;
			}

			path_part = "";
			mover = foundChild;
			index++;
			continue;
		}
		path_part += path.at(index);
		index++;
	}

	std::cout << index << std::endl << length << std::endl;
	
	if (index != length)
	{
		std::cout << mover->getName() << std::endl;
		std::cout << "There" << std::endl;
		FileSystemError(err_message);
		return nullptr;
	}

	return mover;

}


void FileSystemError(std::string err_message)
{
	std::cerr << "FileSystemError: " << err_message << std::endl;
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
		FileSystemError("Cannot remove the root directory. Forbidden.");
		return -1;
	}

	parent->removeChildObject(this);
	delete this;
	return 0;
}


std::string FileSystemObject::getName() const{ return name; }

DirectoryObject* FileSystemObject::getParent() const{ return parent; }

std::string FileSystemObject::getPath()
{
	return pathBuilder(this);
}

std::string FileSystemObject::getCreatedDate() const { return created_at; }

std::string FileSystemObject::getUpdatedDate() const { return updated_at; }

int FileSystemObject::changeUpdatedDate(std::string new_date)
{
	updated_at = new_date;
	return 0;
}

int FileSystemObject::rename(std::string new_name)
{
	if (parent == nullptr)
	{
		FileSystemError("Cannot rename the root directory. Forbidden.");
		return -1;
	}
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
	std::string created_at
)
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

FileSystemObject* DirectoryObject::findChild(std::string name)
{
	for (FileSystemObject* childObject: childObjects)
	{
		std::cout << "Child: " << childObject->getName() << std::endl;
		if (childObject->getName() == name)
		{
			return childObject;
		}
	}

	return nullptr;
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
	std::string created_at)
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
// 	DirectoryObject* dir2 = DirectoryObject::create("programs", dir1, "12/04/2025 10:33PM");
// 	std::cout << (root_dir == nullptr) << std::endl;
// 	FileObject* file1 = FileObject::create("simba", dir1, "11/04/2025 10:33PM");
// 	FileObject* file2 = FileObject::create("dumbo", dir2, "12/04/2025 10:33PM");
// 	file1->rewrite("Helloooooo from file 1!");
// 	file1->addWrite("\n Cool!");
// 	// root_dir->remove();
// 	// file1->remove();
// 	// root_dir->displayContent();
// 	// dir1->displayContent();
// 	// dir1->remove();
// 	// root_dir->displayContent();
// 	// file1->displayContent();

// 	// std::cout << pathBuilder(file1) << std::endl;
// 	root_dir->rename("Dangerous");
// 	file1->rename("milkyway");
// 	dir1->rename("galacticon");
// 	// root_dir->displayContent();
// 	// dir1->displayContent();
// 	// file1->displayContent();
// 	std::cout << pathBuilder(file1) << std::endl;
// 	// std::cout << pathBuilder(dir1) << std::endl;
// 	// std::cout << pathBuilder(root_dir) << std::endl;

// 	// FileSystemObject* finds = objectLocator(root_dir, dir1, "/adadadas/asdasdasd");
// 	// std::cout << (finds==nullptr) << std::endl;


// 	FileSystemObject* finds = objectLocator(root_dir, dir1, ".././galacticon/programs/dumbo");
// 	if (finds)
// 	{
// 		std::cout << (finds->getName()) << std::endl;
// 	} else {
// 		std::cout << "Uxladi" << std::endl;
// 	}
// 	return 0;
// }

