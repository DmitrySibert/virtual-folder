#include "ContentMessage.h"

using namespace rapidjson;

ContentMessage::ContentMessage(const string path, const string messageMapId)
	:BaseMessage(messageMapId), path(path)
{
}

void ContentMessage::preSerialize(Writer<StringBuffer> &writer) const
{
	BaseMessage::preSerialize(writer);
	writer.String("folderPath");
	writer.String(this->path.c_str());
}

ContentMessage::~ContentMessage()
{
}
