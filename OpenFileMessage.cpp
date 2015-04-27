#include "OpenFileMessage.h"

using namespace rapidjson;

OpenFileMessage::OpenFileMessage(const string file, const bool isRequest, const string channelName, const string messageType, const string UUID)
	:BaseMessage(isRequest, channelName, messageType, UUID), file(file)
{
}

void OpenFileMessage::preSerialize(Writer<StringBuffer> &writer) const
{
	BaseMessage::preSerialize(writer);
	writer.String("FileName");
	writer.String(this->file.c_str());
}

OpenFileMessage::~OpenFileMessage()
{
}
