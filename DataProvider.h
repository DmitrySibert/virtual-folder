#pragma once

#include <list>
#include <curl/curl.h>
#include <string>
#include <rapidjson\document.h>
#include <rapidjson\writer.h>
#include <rapidjson\stringbuffer.h>

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
	~DataProvider();
};

