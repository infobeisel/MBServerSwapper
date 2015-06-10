#ifndef FILEPARSER_H
#define FILEPARSER_H
#include "Defines.h"
#include <Windows.h>

class FileParser
{
public:
	FileParser(){}
	virtual ~FileParser();
	static FileParser* get();
	bool openFile(LPCWSTR filename);
	void closeFile();
	/** reads file's content and returns it in form of a vector of strings (using delimiter : ";" ) **/
	std::vector<std::string> readEntries();
protected:
private:
	static FileParser* instance;
	HANDLE  file = INVALID_HANDLE_VALUE;
};

#endif // FILEPARSER_H
