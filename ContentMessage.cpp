#include "ContentMessage.h"

using namespace rapidjson;

ContentMessage::ContentMessage(const string path, const bool isRequest, const string channelName, const string messageType, const string UUID)
	:BaseMessage(isRequest, channelName, messageType, UUID), path(path)
{
}

void ContentMessage::preSerialize(Writer<StringBuffer> &writer) const
{
	BaseMessage::preSerialize(writer);
	writer.String("Path");
	writer.String(this->path.c_str());
}

ContentMessage::~ContentMessage()
{
}
