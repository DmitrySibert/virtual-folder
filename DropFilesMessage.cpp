#include "DropFilesMessage.h"

DropFilesMessage::DropFilesMessage(std::list<char*> files, const bool isRequest, const string channelName, const string messageType, const string UUID)
	:BaseMessage(isRequest, channelName, messageType, UUID), files(files)
{
}

void DropFilesMessage::preSerialize(Writer<StringBuffer> &writer) const
{
	BaseMessage::preSerialize(writer);
	writer.String("Files");	
	writer.StartArray();
	for (std::list<char*>::const_iterator it = this->files.begin(); it != this->files.end(); ++it)
	{
		writer.String(*it);
	}
	writer.EndArray();
}

DropFilesMessage::~DropFilesMessage()
{
}
