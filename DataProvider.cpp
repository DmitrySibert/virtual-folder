#include "DataProvider.h"

using namespace rapidjson;

DataProvider::DataProvider()
{
}

//Callback - функция, которая записывает данные,
//полученные запросом на удаленный сервер, в указанный буфер
int writer(char *data, size_t size, size_t nmemb, string *buffer)
{
	//переменная - результат, по умолчанию нулевая
	int result = 0;
	//проверяем буфер
	if (buffer != NULL)
	{
		//добавляем к буферу строки из data, в количестве nmemb
		buffer->append(data, size * nmemb);
		//вычисляем объем принятых данных
		result = size * nmemb;
	}
	//вовзращаем результат
	return result;
}

string DataProvider::doJsonPost(IJsonSerializable& requestBody)
{
	CURL *curl;
	CURLcode res;
	string buffer;
	struct curl_slist *headers = NULL; // init to NULL is important 
	curl_slist_append(headers, "Accept: application/json");
	curl_slist_append(headers, "Content-Type: application/json");
	curl_slist_append(headers, "charsets: utf-8");
	curl = curl_easy_init();
	if (curl) {
		//curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
		//задаем опцию - получить страницу по адресу 
		curl_easy_setopt(curl, CURLOPT_URL, this->url);
		//задаем опцию отображение заголовка страницы
		//curl_easy_setopt(curl, CURLOPT_HEADER, 1);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		//указываем функцию обратного вызова для записи получаемых данных
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
		//указываем куда записывать принимаемые данные
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
		string requestMessageJson = requestBody.serialize();
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, requestMessageJson.c_str());
		res = curl_easy_perform(curl);
		/* always cleanup */
		curl_easy_cleanup(curl);
	}

	return buffer;
}

string DataProvider::getFoldersContentJson(const char* path){

	ContentMessage message(path, "folderContentId");
	return this->doJsonPost(message);
}

wchar_t* DataProvider::charToWChar(const char* text)
{
	size_t size = strlen(text) + 1;
	wchar_t* wa = new wchar_t[size];
	mbstowcs(wa, text, size);
	return wa;
}

list<FolderElement> DataProvider::getFoldersContent(const char* path)
{
	string buff = this->getFoldersContentJson(path);
	const char* foldersContentJson = buff.c_str();
	Document doc;
	doc.Parse(foldersContentJson);
	list<FolderElement> foldersContent;
	Value& folderContent = doc["folderContent"];
	for (SizeType i = 0; i < folderContent.Size(); i++)
	{
		const Value& folderElementJson = folderContent[i];
		FolderElement folderElement;
		folderElement.isFolder = folderElementJson["isFolder"].GetBool();
		wchar_t* title = charToWChar(folderElementJson["name"].GetString());
		folderElement.name = title;
		foldersContent.push_back(folderElement);
	}
	
	return foldersContent;
}

void DataProvider::logInfo(const char* info)
{
	LogMessage message(info, "loggerId");
	this->doJsonPost(message);
}

bool DataProvider::runFile(const char* file)
{
	OpenFileMessage message(file, "runFile");
	this->doJsonPost(message);

	return true;
}

void DataProvider::dropFiles(std::list<char*> files, std::list<bool> isFolderFlags, string folder)
{
	DropFilesMessage message(files, isFolderFlags, folder, "startFilesDeleting");
	this->doJsonPost(message);
}

void DataProvider::deleteFiles(std::list<char*> files, string folder)
{
	DeleteFilesMessage message(files, folder, "filesUpload");
	this->doJsonPost(message);
}

void DataProvider::createFolder(char* files, string folder)
{
	CreateFolderMessage msg(files, folder, "filesUpload");
	this->doJsonPost(msg);
}

DataProvider::~DataProvider()
{
}
