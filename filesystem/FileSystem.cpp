#include <iostream>
#include <set>
#include <ctime>
#include "FileSystem.h"


// =============================== //
//    FileSystem implementation    //
// =============================== //


FileSystem::FileSystem()
{
	root_dir = DirectoryObject::create("", nullptr);
}


FileSystem::~FileSystem()
{
	delete root_dir;
	root_dir = nullptr;
}
DirectoryObject* FileSystem::getRootDir(){ return root_dir; }


/*
*  	A function to build string path for a FileSystem Object.
*	@returns string path
*/


std::string pathBuilder(FileSystemObject* fsystemObject)
{
	if (fsystemObject == nullptr)
	{
		FileSystemError("Invalid FileSystemObject.");
		return "(invalid)";
	}
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

	if (fsystemObject->isDir())
	{
		path += "/";
	}

	return path;
}


FileSystemObject* objectLocator(
	DirectoryObject* root_dir, 
	DirectoryObject* current_dir, 
	std::string path
)
{
	if (path == "/")
	{
		return root_dir;
	} else if (path.length() == 0)
	{
		return current_dir;
	}
	std::string err_message = "FileSystemObject not found.";

	
	FileSystemObject* mover = nullptr; // Initiliazing mover for further use
	int index = 0;

	
	int firstChar = path.at(0); // Getting first chracter to detect where to start
	if (firstChar == 47) // ASCII 47: '/'
	{
		/*
		 	ASCII 47 means '/' which is root directory
			Traversal starts from index 1, skipping the root dir.
		*/
		mover = root_dir;
		index = 1; 
	}
	else { mover = current_dir; } // In any else case, traversal starts from current directory

	
	if (path.at(path.length() - 1) != '/')
	{
		path += "/"; //  This makes sure that the traversal goes till the end
	}
	int length = path.length();
	std::string path_part = "";
	
	// ^-- This helps to keep track of each sub-paths

	
	while (index < length) // If the path is correct, index is exactly equal to length
	{
		// If mover becomes a FileObject from the prev. iteration, then immediately break
		if (!mover->isDir())
		{std::cout<<"yeah!\n"; break; }
		
		if (path.at(index) == '/')
		{
			// '..' is a command to go one step out in the hierarchy
			if (path_part == "..")
			{
				if (!mover->getParent())
				{
					/*
						^...if the current directory is the root dir., 
						then accessing parent returns nullptr, which
						means there is no way further. Therefore,
						the path is incorrect.
					*/

					FileSystemError("Attempt to leave the root directory. Forbidden.");
					return nullptr;
				}

				/*
					In the else case, update subpath tracker and
					change current mover to its parent.
				*/
				path_part = "";
				mover = mover->getParent();
				index++;
				continue;
			}

			if (path_part == ".")
			{
				/*	
					^... '.' is a special command commanding 'stay there'.
					So, just update subpath, increment, and continue traversal.
				*/
				path_part = "";
				index++;
				continue;
			}

			FileSystemObject* searchResult = static_cast<DirectoryObject*>(mover)->getChild(path_part);
			/*	
				If no cases above are handled, it is time to check the current subpath whether
				it is in the mover drectory. If a path is correct, then there is a solution.
			*/

			if (!searchResult)
			{
				FileSystemError(err_message);
				return nullptr;
			}

			path_part = "";
			mover = searchResult;
			index++;
			continue;
		}
		path_part += path.at(index);
		index++;
	}

	/*	
		If the loop stops and index has not reached length yet,
		that means there is no solution.
		Index is exactly equal to length at the end because 
		everytime the subpath is found, index is incremented.
		That means that even at the last subpath, index is incremented and then loop is exited.
	*/
	if (index != length) 
	{
		FileSystemError(err_message);
		return nullptr;
	}

	return mover;
}


std::string getCurrentTime()
{
	time_t now = time(0);
	tm* localtm = localtime(&now);

	// Date
	std::string result = "";
	result += std::to_string(1900 + localtm->tm_year) + "/";
	result += std::to_string(1 + localtm->tm_mon) + "/";
	result += std::to_string(localtm->tm_mday) + " ";
	
	// Time
	result += std::to_string(localtm->tm_hour) + ":";
	result += std::to_string(localtm->tm_min) + ":";
	result += std::to_string(localtm->tm_sec);

	return result;
}


void FileSystemError(const std::string& err_message)
{
	std::cerr << "FileSystemError: " << err_message << std::endl;
}


// =============================== //
// FileSystemObject implementation //
// =============================== //


FileSystemObject::FileSystemObject(
		std::string inp_name,
		DirectoryObject* inp_parent,
		bool inp_is_dir)
	: name{ inp_name }
	, parent{ inp_parent }
	, is_dir{ inp_is_dir }
	, created_at{ getCurrentTime() }
{
	if (inp_parent) {
		inp_parent->addChildObject(this);
	}
};


bool FileSystemObject::nameValidator(const std::string& name)
{
	std::set<char> disallowedCharacters = {
		'@', '#', '^', '%', '$', '&', '*',
		'(', ')', '=', '!', '~', '\\', '/',
		'|', '.', ',', '?', '[', ']', ';', 
		':', '`', '"', '\''
	};
	if (!name.length())
	{ return false; }
	for (int index = 0; index < name.length(); index++)
	{
		if (disallowedCharacters.count(name.at(index)))
		{ return false; }
	}
	return true;
}


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


std::string FileSystemObject::getCreatedTime() const { return created_at; }
std::string FileSystemObject::getUpdatedTime() const {
	if (updated_at.length() == 0)
	{
		return "(empty)";
	}
	return updated_at; 
}


int FileSystemObject::changeUpdatedTime()
{
	updated_at = getCurrentTime();
	return 0;
}


int FileSystemObject::rename(std::string new_name)
{
	if (parent == nullptr)
	{
		FileSystemError("Cannot rename the root directory. Forbidden.");
		return -1;
	}
	if (!nameValidator(new_name))
	{
		FileSystemError("Invalid name for FileSystemObject.");
		return -1;
	}
	
	name = new_name;
	changeUpdatedTime();

	return 0;
}
bool FileSystemObject::isDir() const { return is_dir; }


int FileSystemObject::displayInfo()
{
	std::cout << "----" << getName() << "----" << std::endl;
	std::cout << "Is Directory: " << isDir() << std::endl;

	std::cout << "Parent Directory: " 
				<< ( (getParent()) ? getParent()->getName():"null" ) 
				<< "/" << std::endl;

	std::cout << "Location: " << getPath() << std::endl;
	std::cout << "Created at: " << getCreatedTime() << std::endl;
	std::cout << "Updated at: " << getUpdatedTime() << std::endl;
	
	return 0;
}


// ================================ //
//  DirectoryObject implementation  //
// ================================ //


DirectoryObject::DirectoryObject(
		std::string inp_name,
		DirectoryObject* inp_parent)
	: FileSystemObject(
		inp_name, inp_parent, true)
{}


DirectoryObject::~DirectoryObject()
{
	for (int childObjIndex = 0; childObjIndex < childObjects.size(); childObjIndex++)
	{
		/*
		 *    
		 *    This is a place where dark things happened (Apr 15, 11:48 PM)
		 *    leading to Segmentaion Fault.
		 *
		 *    Lesson: When iterating a container object,
		 *    do not change its content that changes its size!
		 *    This can result in a behavior you don't expect.
		 *
		 * */	
		delete childObjects.at(childObjIndex);
		childObjects.at(childObjIndex) = nullptr;
	}
}

/*
 *	WARNING: Do not abuse this factory method by
 *	passing empty name and nullptr parent argument!
 *	This has been only allowed for FileSystem constructor
 *	to create the default root directory.
 */

DirectoryObject* DirectoryObject::create(
	std::string name,
	DirectoryObject* parent
)
{
	if (nameValidator(name) && !parent)
	{
		FileSystemError("Invalid parent DirectoryObject.");
		return nullptr;
	}
	else if (!nameValidator(name) && parent)
	{
		FileSystemError("Invalid name for DirectoryObject.");
		return nullptr;
	}
	return new DirectoryObject(name, parent);
}

int DirectoryObject::addChildObject(FileSystemObject* newChildObject)
{
	for (FileSystemObject* childObject: childObjects)
	{
		if (childObject == newChildObject)
		{
			return -1;
		}
	}
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


FileSystemObject* DirectoryObject::getChild(std::string name)
{
	for (FileSystemObject* childObject: childObjects)
	{
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
		DirectoryObject* inp_parent
	)
	: FileSystemObject(
		inp_name, inp_parent, false)
{}


FileObject::~FileObject() = default;

FileObject* FileObject::create(
	std::string name,
	DirectoryObject* parent)
{
	if (nameValidator(name) && parent)
	{
		return new FileObject(name, parent);
	}
	return nullptr;
}

int FileObject::rewrite(std::string new_content)
{
	content = new_content;
	changeUpdatedTime();
	return 0;
}


int FileObject::addWrite(std::string new_content)
{
	
	content += new_content;
	changeUpdatedTime();
	return 0;
}


std::string FileObject::read() const { return content; }


int FileObject::displayContent() const 
{
	std::cout << "----" << getName() << "----" << std::endl;
	std::cout << content << std::endl;
	return 0;
}

