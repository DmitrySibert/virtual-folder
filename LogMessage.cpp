#include "LogMessage.h"

using namespace rapidjson;

LogMessage::LogMessage(const string text, const bool isRequest, const string channelName, const string messageType, const string UUID)
	:BaseMessage(isRequest, channelName, messageType, UUID), text(text)
{
}

string LogMessage::serialize() const
{
	StringBuffer jsonBuffer = BaseMessage::preSerialize();
	Writer<StringBuffer> requestBody(jsonBuffer);
	requestBody.String("LogMsg");
	requestBody.String(this->text.c_str());
	requestBody.EndObject();
	string json = jsonBuffer.GetString();

	return json;
}


LogMessage::~LogMessage()
{
}
