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

string DataProvider::getFoldersContentJson(const char* path){

	CURL *curl;
	CURLcode res;
	string buffer;
	struct curl_slist *headers = NULL; // init to NULL is important 
	curl_slist_append(headers, "Accept: application/json");
	curl_slist_append(headers, "Content-Type: application/json");
	curl_slist_append(headers, "charsets: utf-8");
	curl = curl_easy_init();

	StringBuffer jsonBuffer;
	Writer<StringBuffer> requestBody(jsonBuffer);
	requestBody.StartObject();
	requestBody.String("IsRequest");
	requestBody.Bool(true);
	requestBody.String("To");
	requestBody.StartObject();
	requestBody.String("Name");
	requestBody.String("FolderContent");
	requestBody.EndObject();
	requestBody.String("Type");
	requestBody.String("Path");
	requestBody.String("ID");
	requestBody.String("c69fb066-c0f4-11e4-8dfc-aa07a5b093db");
	requestBody.String("Path");
	requestBody.String(path);
	requestBody.EndObject();
	string json = jsonBuffer.GetString();

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
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json.c_str());
		res = curl_easy_perform(curl);
		/* always cleanup */
		curl_easy_cleanup(curl);
	}

	return buffer;
}

wchar_t* charToWChar(const char* text)
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
	Value& folderContent = doc["FolderContent"];
	for (SizeType i = 0; i < folderContent.Size(); i++)
	{
		const Value& folderElementJson = folderContent[i];
		FolderElement folderElement;
		folderElement.isFolder = folderElementJson["isFolder"].GetBool();
		wchar_t* title = charToWChar(folderElementJson["title"].GetString());
		folderElement.name = title;
		foldersContent.push_back(folderElement);
	}
	
	return foldersContent;
}

DataProvider::~DataProvider()
{
}
