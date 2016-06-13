#include "OpenFileMessage.h"

using namespace rapidjson;

OpenFileMessage::OpenFileMessage(const string file, const string messageMapId)
	:BaseMessage(messageMapId), file(file)
{
}

void OpenFileMessage::preSerialize(Writer<StringBuffer> &writer) const
{
	BaseMessage::preSerialize(writer);
	writer.String("logicPath");
	writer.String(this->file.c_str());
}

OpenFileMessage::~OpenFileMessage()
{
}
