#include "DeleteFilesMessage.h"



DeleteFilesMessage::DeleteFilesMessage(std::list<char*> files, string folder, const string messageMapId)
	:BaseMessage(messageMapId), files(files), folder(folder)
{
}

void DeleteFilesMessage::preSerialize(Writer<StringBuffer> &writer) const
{
	BaseMessage::preSerialize(writer);
	writer.String("files");
	writer.StartArray();
	for (std::list<char*>::const_iterator it = this->files.begin(); it != this->files.end(); ++it)
	{
		writer.StartObject();
		writer.String("logicPath");
		writer.String(this->folder.c_str());
		writer.String("filePath");
		writer.String(*it);
		writer.EndObject();
	}
	writer.EndArray();
}

DeleteFilesMessage::~DeleteFilesMessage()
{
}
