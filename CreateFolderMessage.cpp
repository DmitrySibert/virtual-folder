#include "CreateFolderMessage.h"



CreateFolderMessage::CreateFolderMessage(char* files, string folder, const string messageMapId)
	:BaseMessage(messageMapId), file(file), folder(folder)
{
}

void CreateFolderMessage::preSerialize(Writer<StringBuffer> &writer) const
{
	BaseMessage::preSerialize(writer);
	writer.String("files");
	writer.StartArray();
	writer.StartObject();
	writer.String("logicPath");
	writer.String(this->folder.c_str());
	writer.String("isFolder");
	writer.Bool(true);
	writer.String("filePath");
	writer.String(this->file);
	writer.EndObject();
	writer.EndArray();
}

CreateFolderMessage::~CreateFolderMessage()
{
}
