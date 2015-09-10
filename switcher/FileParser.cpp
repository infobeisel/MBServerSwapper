#include "FileParser.h"
#include "Defines.h"
#include <iostream>

FileParser* FileParser::instance = 0;

FileParser* FileParser::get()
{
	if (instance == 0)
		instance = new FileParser();
	return instance;
}
FileParser::~FileParser()
{
	//dtor
}

bool FileParser::openFile(LPCWSTR filename)
{

	/** copypaste from http://cs.dvc.edu/HowTo_Cparse.html **/
	// create a file-reading object
	file = CreateFile(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);
	if (file == INVALID_HANDLE_VALUE) return false;
	return true;
}

void FileParser::closeFile() {
	CloseHandle(file);
}

std::vector<std::string> FileParser::readEntries()
{
	std::vector<std::string> res;
	char buf[FILE_MAX_CHARS + 1] = { 0 };
	if (file != INVALID_HANDLE_VALUE)
	{
		ReadFile(file, &buf, FILE_MAX_CHARS, NULL, NULL);
		char delimiter[] = "|";

		char* p;//alternative, breaks the function . but this class isnt used at the moment
		// unsafe ! char* p = strtok(buf, delimiter);
		//up to the end of file
		while (p != NULL) {
			std::string str = std::string(p);
			//std::cout << str << "\n";
			//unsafe			p = strtok(NULL, delimiter);
			res.insert(res.end(), str);
		}
	}
	return res;
}
