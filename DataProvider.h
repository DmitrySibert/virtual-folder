#pragma once

#include <list>
#include <curl/curl.h>
#include <string>
#include <rapidjson\document.h>
#include <rapidjson\writer.h>
#include <rapidjson\stringbuffer.h>
#include "IJsonSerializable.h"
#include "ContentMessage.h"
#include "LogMessage.h"
#include "OpenFileMessage.h"
#include "DropFilesMessage.h"

using namespace std;

struct FolderElement{
	bool isFolder;
	const wchar_t* name;
};

class DataProvider
{
private:
	string getFoldersContentJson(const char* path);
	const char* url = "http://localhost:9000/";
public:
	DataProvider();
	list<FolderElement> getFoldersContent(const char* path);
	bool runFile(const char* file);
	void dropFiles(std::list<char*> files, string folder);
	void logInfo(const char* message);
	~DataProvider();
private:
	wchar_t* charToWChar(const char* text);
	string doJsonPost(IJsonSerializable& requestBody);
};

