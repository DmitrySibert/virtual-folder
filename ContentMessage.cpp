#include "ContentMessage.h"

using namespace rapidjson;

ContentMessage::ContentMessage(const string path, const bool isRequest, const string channelName, const string messageType, const string UUID)
	:BaseMessage(isRequest, channelName, messageType, UUID), path(path)
{
}

string ContentMessage::serialize() const
{
	/*StringBuffer jsonBuffer;
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
	requestBody.String(BaseMessage::getUuid().c_str());*/
	StringBuffer jsonBuffer = BaseMessage::preSerialize();
	Writer<StringBuffer> requestBody(jsonBuffer);
	requestBody.String("Path");
	requestBody.String(this->path.c_str());
	requestBody.EndObject();
	string json = jsonBuffer.GetString();

	return json;
}

ContentMessage::~ContentMessage()
{
}
