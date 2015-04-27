#include "LogMessage.h"

using namespace rapidjson;

LogMessage::LogMessage(const string text, const bool isRequest, const string channelName, const string messageType, const string UUID)
	:BaseMessage(isRequest, channelName, messageType, UUID), text(text)
{
}

void LogMessage::preSerialize(Writer<StringBuffer> &writer) const
{
	BaseMessage::preSerialize(writer);
	writer.String("LogMsg");
	writer.String(this->text.c_str());
}

LogMessage::~LogMessage()
{
}
