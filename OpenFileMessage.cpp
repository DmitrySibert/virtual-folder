#include "OpenFileMessage.h"

using namespace rapidjson;

OpenFileMessage::OpenFileMessage(const string file, const bool isRequest, const string channelName, const string messageType, const string UUID)
	:BaseMessage(isRequest, channelName, messageType, UUID), file(file)
{
}

string OpenFileMessage::serialize() const
{
	StringBuffer jsonBuffer = BaseMessage::preSerialize();
	Writer<StringBuffer> requestBody(jsonBuffer);
	requestBody.String("File");
	requestBody.String(this->file.c_str());
	requestBody.EndObject();
	string json = jsonBuffer.GetString();

	return json;
}

OpenFileMessage::~OpenFileMessage()
{
}
