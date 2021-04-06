/****************************************************************************    
 * Dominic Mazza    
 * Computer Project #4  
 *****************************************************************************/

#include <iostream>
#include <algorithm>
#include <fcntl.h>
#include <string>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <experimental/filesystem>
#include <sys/stat.h>
#include <time.h>
#include <memory>

namespace fs = std::experimental::filesystem;
extern char **environ;

/*------------------------------------------------------------------------
 Name: splitByDelimiter

 Purpose: Splits string str by delimiter char
 Receive: String to split, character to delimit by, vector to put split
 string in
 Return: Nothing
--------------------------------------------------------------------------*/
void splitByDelimiter(std::string const &str, const char delim, std::vector<std::string> &out)
{
	size_t start;
	size_t end = 0;

	while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
	{
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
}

/*------------------------------------------------------------------------
 Name: shortFileDescriptor

 Purpose: Prints absolute path, permissions, and size of file in bytes
 Receive: Filepath token given on command line, a vector of DIRLIST directories,
 and a boolean toggling whether or not this function is being used by 
 longFileDescriptor
 Return: Nothing
--------------------------------------------------------------------------*/
void shortFileDescriptor(const std::string &filepath, std::vector<std::string> &vecEnviron, bool longOut = false)
{
	for (std::string item : vecEnviron)
	{
		fs::path path;
		// Makes sure that for the local directory, a slash isn't added,
		// which would invalidate the filepath
		if (item == "")
		{
			path = filepath;
		}
		else
		{
			path = item + "/" + filepath;
		}
		// Using filesystem instead of stat here because I am
		// not smart and didn't read the specs all the way through.
		// Also, it works just fine with this and allows for easy filepath
		// checking with the filesystem library.
		if (fs::exists(path))
		{

			path = fs::canonical(path);

			// Absolute path without ../ or ./
			std::cout << "Path: " << path << std::endl;

			// Permissions for file
			fs::perms p = fs::status(path).permissions();
			std::cout << "Permissions: "
					  << ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
					  << ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
					  << ((p & fs::perms::owner_exec) != fs::perms::none ? "x" : "-")
					  << ((p & fs::perms::group_read) != fs::perms::none ? "r" : "-")
					  << ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-")
					  << ((p & fs::perms::group_exec) != fs::perms::none ? "x" : "-")
					  << ((p & fs::perms::others_read) != fs::perms::none ? "r" : "-")
					  << ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
					  << ((p & fs::perms::others_exec) != fs::perms::none ? "x" : "-")
					  << std::endl;

			// Size of file in bytes
			std::cout << "Size: " << fs::file_size(path) << " bytes" << std::endl;

			// Adds a spacer if it is just a short file descriptor
			if (!longOut)
			{
				std::cout << "-------------------------------------" << std::endl
						  << std::endl;
			}
		}
	}
}

/*------------------------------------------------------------------------
 Name: longFileDescriptor

 Purpose: Prints absolute path, permissions, size of file in bytes, 
 user id, group id, and timestamps for last read/write/status change
 Receive: Filepath token given on command line and a vector of DIRLIST 
 directories
 Return: Nothing
--------------------------------------------------------------------------*/
void longFileDescriptor(const std::string &filepath, std::vector<std::string> &vecEnviron)
{
	for (std::string item : vecEnviron)
	{
		fs::path path;
		if (item == "")
		{
			path = filepath;
		}
		else
		{
			path = item + "/" + filepath;
		}
		if (fs::exists(path))
		{
			shortFileDescriptor(filepath, vecEnviron, true);

			struct stat sfile;
			stat((item + filepath).c_str(), &sfile);

			// Owner and Group IDS
			std::cout << "Owner: " << sfile.st_uid << std::endl;
			std::cout << "Group: " << sfile.st_gid << std::endl;

			// Last read time
			timespec_get(&sfile.st_atim, TIME_UTC);
			char buff[100];
			strftime(buff, sizeof buff, "%a %b %d %r %Y", gmtime(&sfile.st_atim.tv_sec));
			std::cout << "Last read: " << buff << std::endl;

			// Last write time
			memset(buff, 0, sizeof buff);
			timespec_get(&sfile.st_mtim, TIME_UTC);
			strftime(buff, sizeof buff, "%a %b %d %r %Y", gmtime(&sfile.st_mtim.tv_sec));
			std::cout << "Last write: " << buff << std::endl;

			// Last status change time
			memset(buff, 0, sizeof buff);
			timespec_get(&sfile.st_ctim, TIME_UTC);
			strftime(buff, sizeof buff, "%a %b %d %r %Y", gmtime(&sfile.st_ctim.tv_sec));
			std::cout << "Last access: " << buff << std::endl;

			std::cout << "-------------------------------------" << std::endl
					  << std::endl;
		}
	}
}

/*------------------------------------------------------------------------
 Name: main

 Purpose: Ingests command line arguments and processes environment
 variable DIRLIST 
 Recieves: argc and argv, the command line arguments
 Return: int exit code
--------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
	bool longPrint = false;
	std::vector<std::string> vecFilePath;
	std::vector<std::string> vecEnviron;
	vecEnviron.push_back("");
	for (int i = 1; i < argc; i++)
	{
		std::string argString = std::string(argv[i]);

		// Checks for a flag
		if (argString[0] == '-')
		{
			// Checks to make sure flag is an acceptable flag
			if (argString == "-L" || argString == "-S")
			{
				// Adds to vecFilePath in order to check which flag is being processed in loop
				vecFilePath.push_back(argString);
				continue;
			}
			else
			{
				std::cout << "Invalid flag used." << std::endl;
				exit(1);
			}
		}
		else
		{
			// If argument is not a flag, it is parsed as a file name
			vecFilePath.push_back(argString);
		}
	}

	// Processes DIRLIST using getenv
	if (const char *envDirlist = std::getenv("DIRLIST"))
	{
		std::string envDirlistString = std::string(envDirlist);
		splitByDelimiter(envDirlistString, ':', vecEnviron);
	}

	// Loops through all filepath and flag arguments
	for (std::string item : vecFilePath)
	{
		// Toggles longPrint based on which flag is found
		if (item == "-L")
		{
			longPrint = true;
		}
		else if (item == "-S")
		{
			longPrint = false;
		}

		// Utilizes longFileDescriptor and shortFileDescriptor as necessary
		if (longPrint)
		{
			longFileDescriptor(item, vecEnviron);
		}
		else
		{
			shortFileDescriptor(item, vecEnviron);
		}
	}
}
