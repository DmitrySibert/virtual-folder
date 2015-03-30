#include "OpenFileMessage.h"

using namespace rapidjson;

OpenFileMessage::OpenFileMessage(const string file, const bool isRequest, const string channelName, const string messageType, const string UUID)
	:BaseMessage(isRequest, channelName, messageType, UUID), file(file)
{
}

string OpenFileMessage::serialize() const
{
	StringBuffer jsonBuffer;
	Writer<StringBuffer> requestBody(jsonBuffer);
	requestBody.StartObject();
	requestBody.String("IsRequest");
	requestBody.Bool(BaseMessage::getIsRequest());
	requestBody.String("To");
	requestBody.StartObject();
	requestBody.String("Name");
	requestBody.String(BaseMessage::getChannelName().c_str());
	requestBody.EndObject();
	requestBody.String("Type");
	requestBody.String(BaseMessage::getMessageType().c_str());
	requestBody.String("ID");
	requestBody.String(BaseMessage::getUuid().c_str());
	requestBody.String("FileName");
	requestBody.String(this->file.c_str());
	requestBody.EndObject();
	string json = jsonBuffer.GetString();

	return json;
}

OpenFileMessage::~OpenFileMessage()
{
}
