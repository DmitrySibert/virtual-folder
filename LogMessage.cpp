#include "LogMessage.h"

using namespace rapidjson;

LogMessage::LogMessage(const string text, const string messageMapId)
	:BaseMessage(messageMapId), text(text)
{
}

void LogMessage::preSerialize(Writer<StringBuffer> &writer) const
{
	BaseMessage::preSerialize(writer);
	writer.String("logMsg");
	writer.String(this->text.c_str());
}

LogMessage::~LogMessage()
{
}
