#include "BaseMessage.h"

using namespace rapidjson;

BaseMessage::BaseMessage(const bool isRequest, const string channelName, const string messageType, const string UUID)
	:isRequest(isRequest), channelName(channelName), messageType(messageType), UUID(UUID)
{
}

void BaseMessage::preSerialize(Writer<StringBuffer> &writer) const
{	
	writer.String("IsRequest");
	writer.Bool(this->isRequest);
	writer.String("To");
	writer.StartObject();
	writer.String("Name");
	writer.String(this->channelName.c_str());
	writer.EndObject();
	writer.String("Type");
	writer.String(this->messageType.c_str());
	writer.String("ID");
	writer.String(this->UUID.c_str());
}

string BaseMessage::serialize() const
{	
	StringBuffer jsonBuffer;
	Writer<StringBuffer> writer(jsonBuffer);
	writer.StartObject();
	this->preSerialize(writer);
	writer.EndObject();
	string json = jsonBuffer.GetString();

	return json;
}

BaseMessage::~BaseMessage()
{
}
