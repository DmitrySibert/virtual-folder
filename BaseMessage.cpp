#include "BaseMessage.h"

using namespace rapidjson;

BaseMessage::BaseMessage(const bool isRequest, const string channelName, const string messageType, const string UUID)
	:isRequest(isRequest), channelName(channelName), messageType(messageType), UUID(UUID)
{
}

StringBuffer BaseMessage::preSerialize() const
{
	StringBuffer jsonBuffer;
	Writer<StringBuffer> requestBody(jsonBuffer);
	requestBody.StartObject();
	requestBody.String("IsRequest");
	requestBody.Bool(this->isRequest);
	requestBody.String("To");
	requestBody.StartObject();
	requestBody.String("Name");
	requestBody.String(this->channelName.c_str());
	requestBody.EndObject();
	requestBody.String("Type");
	requestBody.String(this->messageType.c_str());
	requestBody.String("ID");
	requestBody.String(this->UUID.c_str());
	requestBody.EndObject();

	return jsonBuffer;
}

string BaseMessage::serialize() const
{
	StringBuffer jsonBuffer = this->preSerialize();
	string json = jsonBuffer.GetString();

	return json;
}

BaseMessage::~BaseMessage()
{
}
