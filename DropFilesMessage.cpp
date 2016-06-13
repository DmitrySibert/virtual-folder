#include "DropFilesMessage.h"

DropFilesMessage::DropFilesMessage(std::list<char*> files, std::list<bool> isFolderFlags, string folder, const string messageMapId)
	:BaseMessage(messageMapId), files(files), isFolderFlags(isFolderFlags), folder(folder)
{
}

void DropFilesMessage::preSerialize(Writer<StringBuffer> &writer) const
{
	BaseMessage::preSerialize(writer);
	writer.String("files");	
	writer.StartArray();
	std::list<bool>::const_iterator itFlags = this->isFolderFlags.begin();
	for (std::list<char*>::const_iterator it = this->files.begin(); it != this->files.end(); ++it, ++itFlags)
	{
		writer.StartObject();
		writer.String("logicPath");
		writer.String(this->folder.c_str());
		writer.String("isFolder");
		writer.Bool(*itFlags);
		writer.String("filePath");
		writer.String(*it);
		writer.EndObject();
	}
	writer.EndArray();
}

DropFilesMessage::~DropFilesMessage()
{
}
